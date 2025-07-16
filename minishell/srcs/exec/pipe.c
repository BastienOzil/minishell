#include "../includes/minishell.h"

int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		puppetmaster_perror("pipe");
		return (-1);
	}
	return (0);
}

pid_t	create_child_process(void)
{
	pid_t	pid = fork();
	if (pid < 0)
		puppetmaster_perror("fork");
	return (pid);
}

int	redirect_fd(int input_fd, int output_fd)
{
	if (dup2(input_fd, output_fd) == -1)
	{
		puppetmaster_perror("dup2");
		return (-1);
	}
	return (0);
}

void	close_unused_fds(int pipefd[2])
{
	if (pipefd[0] >= 0)
		close(pipefd[0]);
	if (pipefd[1] >= 0)
		close(pipefd[1]);
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*path;

	path = find_path(cmd->args[0], envp);
	if (!path)
	{
		puppetmaster_perror(cmd->args[0]);
		exit(127);
	}
	execve(path, cmd->args, envp);
	puppetmaster_perror("execve");
	exit(EXIT_FAILURE);
}

void	run_child_process(t_cmd *cmd, int in_fd, int pipefd[2], char **envp)
{
	if (in_fd != 0)
		redirect_fd(in_fd, STDIN_FILENO);
	if (cmd && cmd->next)
	{
		redirect_fd(pipefd[1], STDOUT_FILENO);
		close_unused_fds(pipefd);
	}
	execute_command(cmd, envp);
	exit(0);
}

void	handle_parent(t_cmd *cmd, int *in_fd, int pipefd[2])
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd && cmd->next)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
	else
	{
		// dernière commande : pipe non utilisé
		close_unused_fds(pipefd);
		*in_fd = 0;
	}
}


void	execute_pipeline(t_cmd *cmd_list, char ***envp)
{
	t_cmd	*cmd = cmd_list;
	int		pipefd[2];
	int		in_fd = 0;
	pid_t	pid;

	while (cmd)
	{
		if (cmd->next && create_pipe(pipefd) == -1)
			return;
		pid = create_child_process();
		if (pid == 0)
			run_child_process(cmd, in_fd, pipefd, *envp);
		handle_parent(cmd, &in_fd, pipefd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
}

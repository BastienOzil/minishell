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


void execute_pipeline(t_cmd *cmd_list, char ***envp)
{
	int		pipefd[2];
	int		in_fd = 0;
	pid_t	pid;
	t_cmd	*cmd = cmd_list;
	char	*path;

	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);

		pid = fork();
		if (pid == 0)
		{
			if (cmd->infile)
				exec_input_redirection(cmd);
			else if (cmd->heredoc)
				exec_heredoc(cmd);

			if (cmd->append)
				exec_append_redirection(cmd);
			else if (cmd->outfile)
				exec_output_redirection(cmd);

			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (cmd->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}

			if (is_builtin(cmd->args[0]))
			{
				int code = exec_builtin(cmd, envp);
				exit(code);
			}
			else
			{
				path = find_path(cmd->args[0], *envp);
				if (!path)
				{
					puppetmaster_perror(cmd->args[0]);
					exit(127);
				}
				execve(path, cmd->args, *envp);
				puppetmaster_perror("execve");
				exit(EXIT_FAILURE);
			}
		}

		if (pid < 0)
		{
			puppetmaster_perror("fork");
			return;
		}

		if (in_fd != 0)
			close(in_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			in_fd = pipefd[0];
		}
		cmd = cmd->next;
	}

	// Attend les enfants et met à jour g_exit_status
	int status;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

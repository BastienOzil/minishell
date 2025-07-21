#include "../../includes/minishell.h"

void	execute_builtin_with_redirs(t_cmd *cmd, char ***envp)
{
	int	result;

	if (cmd->infile)
		exec_input_redirection(cmd);
	else if (cmd->heredoc)
		exec_heredoc(cmd);
	if (cmd->append)
		exec_append_redirection(cmd);
	else if (cmd->outfile)
		exec_output_redirection(cmd);
	result = exec_builtin(cmd, envp);
	g_exit_status = result;
}

void	execute_external_cmd(t_cmd *cmd, char ***envp)
{
	char	*path;

	if (cmd->infile)
		exec_input_redirection(cmd);
	else if (cmd->heredoc)
		exec_heredoc(cmd);
	if (cmd->append)
		exec_append_redirection(cmd);
	else if (cmd->outfile)
		exec_output_redirection(cmd);
	path = find_path(cmd->args[0], *envp);
	if (!path)
		print_cmd_not_found(cmd->args[0]);
	execve(path, cmd->args, *envp);
	puppetmaster_perror("execve");
	exit(EXIT_FAILURE);
}

void	execute_fork_and_wait(t_cmd *cmd, char ***envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		puppetmaster_perror("fork");
		return ;
	}
	if (pid == 0)
		execute_external_cmd(cmd, envp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

void	execute_cmd(t_cmd *cmd, char ***envp)
{
	int	stdin_copy;
	int	stdout_copy;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
	{
		stdin_copy = dup(STDIN_FILENO);
		stdout_copy = dup(STDOUT_FILENO);
		execute_builtin_with_redirs(cmd, envp);
		dup2(stdout_copy, STDOUT_FILENO);
		dup2(stdin_copy, STDIN_FILENO);
		close(stdout_copy);
		close(stdin_copy);
		return ;
	}
	execute_fork_and_wait(cmd, envp);
}

void	execute_all(t_cmd *cmd, char ***envp)
{
	t_cmd	*flat;

	if (!cmd)
		return ;
	if (cmd->type == NODE_PIPELINE)
	{
		flat = linearize_pipeline(cmd);
		execute_pipeline(flat, envp);
		return ;
	}
	execute_cmd(cmd, envp);
}

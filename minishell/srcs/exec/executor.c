/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:28 by bozil             #+#    #+#             */
/*   Updated: 2025/08/04 13:07:43 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin_with_redirs(t_cmd *cmd, char ***envp)
{
	int	result;

	if (cmd->infile)
	{
		if (exec_input_redirection(cmd) == -1)
			return ;
	}
	else if (cmd->heredoc_list)
		exec_multiple_heredocs(cmd);
	else if (cmd->heredoc)
		exec_heredoc(cmd);
	if (cmd->append)
	{
		if (exec_append_redirection(cmd) == -1)
			return ;
	}
	else if (cmd->outfile)
	{
		if (exec_output_redirection(cmd) == -1)
			return ;
	}
	result = exec_builtin(cmd, envp);
	g_exit_status = result;
}

void	execute_external_cmd(t_cmd *cmd, char ***envp)
{
	if (cmd->infile)
	{
		if (exec_input_redirection(cmd) == -1)
			return ;
	}
	else if (cmd->heredoc_list)
		exec_multiple_heredocs(cmd);
	else if (cmd->heredoc)
		exec_heredoc(cmd);
	if (cmd->append)
	{
		if (exec_append_redirection(cmd) == -1)
			return ;
	}
	else if (cmd->outfile)
	{
		if (exec_output_redirection(cmd) == -1)
			return ;
	}
	exec_path(cmd, *envp);
}

void	execute_fork_and_wait(t_cmd *cmd, char ***envp)
{
	pid_t	pid;
	int		status;

	pid = create_child_process();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		setup_signals_child();
		execute_external_cmd(cmd, envp);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
	}
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
	t_cmd	*exec_list;

	if (!cmd)
		return ;
	if (cmd->type == NODE_PIPELINE)
	{
		exec_list = linearize_pipeline(cmd);
		execute_pipeline(exec_list, envp);
		return ;
	}
	execute_cmd(cmd, envp);
}

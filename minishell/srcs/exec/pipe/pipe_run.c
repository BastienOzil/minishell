/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:15 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:58:17 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_exec(t_cmd *cmd, int in_fd, int pipefd[2], char ***envp)
{
	int	code;

	handle_redirections(cmd);
	if (in_fd != 0)
		redirect_fd(in_fd, STDIN_FILENO);
	if (cmd && cmd->next)
	{
		redirect_fd(pipefd[1], STDOUT_FILENO);
		close_unused_fds(pipefd);
	}
	if (is_builtin(cmd->args[0]))
	{
		code = exec_builtin(cmd, envp);
		exit(code);
	}
	execute_command(cmd, *envp);
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
		close_unused_fds(pipefd);
		*in_fd = 0;
	}
}

void	wait_and_set_exit_status(void)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

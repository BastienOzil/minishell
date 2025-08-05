/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:15 by bozil             #+#    #+#             */
/*   Updated: 2025/08/05 10:02:05 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_exec(t_cmd *cmd, int in_fd, int pipefd[2], char ***envp)
{
	int	code;

	setup_signals_child();
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(127);
	if (in_fd != 0)
		redirect_fd(in_fd, STDIN_FILENO);
	if (cmd->next && pipefd[1] != -1)
	{
		redirect_fd(pipefd[1], STDOUT_FILENO);
		close_unused_fds(pipefd);
	}
	if (handle_redirections(cmd) == -1)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		code = exec_builtin(cmd, envp);
		exit(code);
	}
	exec_path(cmd, *envp);
	puppetmaster_perror(cmd->args[0]);
	exit(127);
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

void	wait_and_set_exit_status(pid_t last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_exit_status = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					write(STDERR_FILENO, "Quit: 3\n", 8);
			}
		}
		pid = wait(&status);
	}
}

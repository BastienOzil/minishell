/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:54 by bozil             #+#    #+#             */
/*   Updated: 2025/08/04 09:46:04 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static pid_t	execute_single_cmd(t_cmd *cmd, int *in_fd, char ***envp)
{
	int		pipefd[2];
	pid_t	pid;

	pipefd[0] = -1;
	pipefd[1] = -1;
	if (cmd->next && create_pipe(pipefd) == -1)
		return (-1);
	pid = create_child_process();
	if (pid == 0)
	{
		setup_signals_child();
		child_exec(cmd, *in_fd, pipefd, envp);
	}
	if (pid < 0)
		return (-1);
	handle_parent(cmd, in_fd, pipefd);
	return (pid);
}

void	execute_pipeline(t_cmd *cmd_list, char ***envp)
{
	t_cmd	*cmd;
	pid_t	last_pid;
	int		in_fd;

	cmd = cmd_list;
	last_pid = -1;
	in_fd = 0;
	while (cmd)
	{
		last_pid = execute_single_cmd(cmd, &in_fd, envp);
		if (last_pid < 0)
			return ;
		cmd = cmd->next;
	}
	wait_and_set_exit_status(last_pid);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:08 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:58:10 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*path;

	path = find_path(cmd->args[0], envp);
	if (!path)
	{
		print_cmd_not_found(cmd->args[0]);
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

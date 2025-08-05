/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:18 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 18:09:24 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exec_error(char *cmd, char *path)
{
	if (path)
		free(path);
	print_cmd_not_found(cmd);
	exit(127);
}

void	exec_path(t_cmd *cmd, char **envp)
{
	char		*path;
	struct stat	st;

	if (ft_strchr(cmd->args[0], '/'))
	{
		if (stat(cmd->args[0], &st) == 0 && S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
		if (access(cmd->args[0], X_OK) == 0)
			execve(cmd->args[0], cmd->args, envp);
		exec_error(cmd->args[0], NULL);
	}
	path = find_path(cmd->args[0], envp);
	if (!path || access(path, X_OK) != 0)
		exec_error(cmd->args[0], path);
	execve(path, cmd->args, envp);
	free(path);
	exec_error(cmd->args[0], NULL);
}

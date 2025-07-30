/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:18 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 16:32:22 by aurelia          ###   ########.fr       */
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
	char	*path;

	if (ft_strchr(cmd->args[0], '/'))
	{
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

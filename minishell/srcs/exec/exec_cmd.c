/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:16:49 by bozil             #+#    #+#             */
/*   Updated: 2025/07/28 15:16:57 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_error_and_exit(char *cmd, char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(code);
}

static void	handle_path_error(char *cmd)
{
	if (access(cmd, F_OK) == -1)
		print_error_and_exit(cmd, "No such file or directory", 127);
	else
		print_error_and_exit(cmd, "Permission denied", 126);
}

static void	handle_execve_error(char *cmd, char *path)
{
	if (path && path != cmd)
		free(path);
	if (ft_strchr(cmd, '/'))
		handle_path_error(cmd);
	else
		print_error_and_exit(cmd, "command not found", 127);
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(1);
	path = find_path(cmd->args[0], envp);
	if (!path)
		handle_execve_error(cmd->args[0], NULL);
	if (execve(path, cmd->args, envp) == -1)
		handle_execve_error(cmd->args[0], path);
}

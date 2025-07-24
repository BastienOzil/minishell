/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:56:59 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:57:03 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (echo_builtin(cmd->args));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (cd_builtin(cmd->args));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (pwd_builtin());
	if (!ft_strcmp(cmd->args[0], "env"))
		return (env_builtin(envp));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (exit_builtin(cmd->args));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (export_builtin(cmd->args, envp));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (unset_builtin(cmd->args, envp));
	return (1);
}

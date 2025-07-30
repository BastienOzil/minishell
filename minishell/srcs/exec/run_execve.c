/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:18 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 09:02:35 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_path(t_cmd *cmd, char **envp)
{
	char	*path;

	path = find_path(cmd->args[0], envp);
	if (!path)
	{
		print_cmd_not_found(cmd->args[0]);
		exit(127);
	}
	execve(path, cmd->args, envp);
	free(path);
	puppetmaster_perror("execve");
	exit(EXIT_FAILURE);
}

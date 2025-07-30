/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:01:55 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 09:33:37 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_cmd_valid(t_cmd *cmd)
{
	if (!cmd)
	{
		puppetmaster_perror("cmd is NULL");
		return (0);
	}
	return (1);
}

static void	handle_dup2_error(t_cmd *cmd, int fd)
{
	close(fd);
	if (is_builtin(cmd->args[0]))
	{
		perror("dup2");
		g_exit_status = 1;
		return ;
	}
	puppetmaster_perror("dup2");
	exit(EXIT_FAILURE);
}

int	exec_append_redirection(t_cmd *cmd)
{
	int	fd;

	if (!is_cmd_valid(cmd) || !cmd->outfile)
	{
		if (is_builtin(cmd->args[0]))
		{
			g_exit_status = 1;
			return (-1);
		}
		puppetmaster_perror("invalid command or outfile for append");
		exit(EXIT_FAILURE);
	}
	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		handle_output_error(cmd, cmd->outfile);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		handle_dup2_error(cmd, fd);
		return (-1);
	}
	close(fd);
	return (0);
}

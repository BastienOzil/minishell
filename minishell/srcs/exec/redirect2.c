/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:55:58 by bozil             #+#    #+#             */
/*   Updated: 2025/07/28 11:21:02 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_input_error(t_cmd *cmd, const char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	if (is_builtin(cmd->args[0]))
	{
		g_exit_status = 1;
		return ;
	}
	exit(EXIT_FAILURE);
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

int	exec_input_redirection(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		handle_input_error(cmd, cmd->infile);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		handle_dup2_error(cmd, fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:48 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:57:49 by bozil            ###   ########.fr       */
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

void	exec_output_redirection(t_cmd *cmd)
{
	int	fd;

	if (!is_cmd_valid(cmd) || !cmd->outfile)
	{
		if (is_builtin(cmd->args[0]))
			return ;
		puppetmaster_perror("invalid command or outfile");
		exit(EXIT_FAILURE);
	}
	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		puppetmaster_perror("open outfile");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		puppetmaster_perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	exec_input_redirection(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->infile);
		if (is_builtin(cmd->args[0]))
			return ;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		if (is_builtin(cmd->args[0]))
			return ;
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	exec_append_redirection(t_cmd *cmd)
{
	int	fd;

	if (!is_cmd_valid(cmd) || !cmd->outfile)
	{
		if (is_builtin(cmd->args[0]))
			return ;
		puppetmaster_perror("invalid command or outfile for append");
		exit(EXIT_FAILURE);
	}
	fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		puppetmaster_perror("open outfile (append)");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		puppetmaster_perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

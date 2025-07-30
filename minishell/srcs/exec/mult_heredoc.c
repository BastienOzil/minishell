/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 22:28:31 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 22:52:24 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	process_single_heredoc(t_heredoc *current, char *tmp_file, int count, char *pid_str)
{
	int	fd;

	if (!current || !current->delimiter)
		return (-1);
	snprintf(tmp_file, 64, "/tmp/.heredoc_%s_%d", pid_str, count);
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		puppetmaster_perror("heredoc tmp file creation");
		return (-1);
	}
	write_heredoc_lines(fd, current->delimiter);
	close(fd);
	if (!current->next && redirect_stdin_from_tmp(tmp_file) == -1)
		return (-1);
	if (current->next)
		unlink(tmp_file);
	return (0);
}

void	exec_multiple_heredocs(t_cmd *cmd)
{
	t_heredoc	*current;
	char		tmp_file[64];
	char		*pid_str;
	int			count;

	if (!cmd || !cmd->heredoc_list)
		return ;
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return ;
	current = cmd->heredoc_list;
	count = 0;
	while (current)
	{
		if (process_single_heredoc(current, tmp_file, count++, pid_str) == -1)
			break ;
		current = current->next;
	}
	free(pid_str);
}

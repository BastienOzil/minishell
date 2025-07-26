/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:38 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:57:42 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_tmp_heredoc(char *template_path)
{
	int		fd;
	pid_t	pid;
	char	*pid_str;

	pid = getpid();
	pid_str = ft_itoa(pid);
	if (!pid_str)
		return (-1);
	ft_strlcpy(template_path, "/tmp/.heredoc_", 64);
	ft_strlcat(template_path, pid_str, 64);
	free(pid_str);
	fd = open(template_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		puppetmaster_perror("heredoc tmp file creation");
	return (fd);
}

int	write_heredoc_lines(int fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	redirect_stdin_from_tmp(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		puppetmaster_perror("heredoc reopen for reading");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		puppetmaster_perror("heredoc dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	exec_heredoc(t_cmd *cmd)
{
	char	tmp_file[64];
	char	*pid_str;
	int		fd;

	if (!cmd || !cmd->heredoc)
		return ;
	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return ;
	ft_strlcpy(tmp_file, "/tmp/.heredoc_", sizeof(tmp_file));
	ft_strlcat(tmp_file, pid_str, sizeof(tmp_file));
	free(pid_str);
	fd = open_tmp_heredoc(tmp_file);
	if (fd == -1)
		return ;
	write_heredoc_lines(fd, cmd->heredoc);
	close(fd);
	if (redirect_stdin_from_tmp(tmp_file) == -1)
		return ;
	unlink(tmp_file);
}

#include "../includes/minishell.h"

int	open_tmp_heredoc(char *template_path)
{
	int	fd;

	fd = mkstemp(template_path);
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
			break;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
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
	char	tmp_file[] = "/tmp/.heredoc_tmp_XXXXXX";
	int		fd;

	if (!cmd || !cmd->heredoc)
		return ;
	fd = open_tmp_heredoc(tmp_file);
	if (fd == -1)
		return ;
	write_heredoc_lines(fd, cmd->heredoc);
	close(fd);
	if (redirect_stdin_from_tmp(tmp_file) == -1)
		return ;
	unlink(tmp_file);
}

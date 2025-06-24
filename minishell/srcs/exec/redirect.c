#include "../includes/minishell.h"


//execution des commandes (fork, execve, redirections, pipes, dup2, close)

//overwrite > écrase le fichier s'il n'existe pas.
//ouvre un fichier pour rediriger la sortie.
void	exec_output_redirection(t_exec_cmd *exec_cmd)
{
	int	fd;

	fd = open(exec_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		puppetmaster_perror("open outfile");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		puppetmaster_perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

// input < lit dans un fichier existant et remplace l'entrée standard (stdin)
void	exec_input_redirection(t_exec_cmd *exec_cmd)
{
	int	fd;

	fd = open(exec_cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		puppetmaster_perror("open infile");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		puppetmaster_perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

// append >> ajoute à la fin d’un fichier (ou le crée si absent)
void	exec_append_redirection(t_exec_cmd *exec_cmd)
{
	int	fd;

	fd = open(exec_cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		puppetmaster_perror("open outfile (append)");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		puppetmaster_perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

// heredoc << simule un fichier temporaire contenant l’entrée jusqu’à un délimiteur
void	exec_heredoc(t_exec_cmd *exec_cmd)
{
	int		fd;
	char	*line;
	char	*delimiter = exec_cmd->infile; // contient le mot-clé de fin, comme "EOF"

	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		puppetmaster_perror("heredoc tmp file");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);

	fd = open("/tmp/.heredoc_tmp", O_RDONLY);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
	{
		puppetmaster_perror("heredoc input");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
#include "../includes/minishell.h"

// Fonction utilitaire pour vérifier la validité de cmd
static int is_cmd_valid(t_cmd *cmd)
{
    if (!cmd)
    {
        puppetmaster_perror("cmd is NULL");
        return (0);
    }
    return (1);
}

// overwrite > écrase le fichier s'il n'existe pas.
// ouvre un fichier pour rediriger la sortie.
void exec_output_redirection(t_cmd *cmd)
{
    int fd;

    if (!is_cmd_valid(cmd) || !cmd->outfile)
    {
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
        puppetmaster_perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// input < lit dans un fichier existant et remplace l'entrée standard (stdin)
void exec_input_redirection(t_cmd *cmd)
{
    int fd;

    if (!is_cmd_valid(cmd) || !cmd->infile)
    {
        puppetmaster_perror("invalid command or infile");
        exit(EXIT_FAILURE);
    }

    fd = open(cmd->infile, O_RDONLY);
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

// append >> ajoute à la fin d'un fichier (ou le crée si absent)
void exec_append_redirection(t_cmd *cmd)
{
    int fd;

    if (!is_cmd_valid(cmd) || !cmd->outfile)
    {
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
        puppetmaster_perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// heredoc << simule un fichier temporaire contenant l'entrée jusqu'à un délimiteur
void exec_heredoc(t_cmd *cmd)
{
    int fd;
    char *line;
    char *delimiter;
    char tmp_file[] = "/tmp/.heredoc_tmp_XXXXXX";

    if (!is_cmd_valid(cmd))
        exit(EXIT_FAILURE);

    // Utilise le champ heredoc au lieu d'infile pour le délimiteur
    delimiter = cmd->heredoc;
    if (!delimiter)
    {
        puppetmaster_perror("heredoc delimiter is NULL");
        exit(EXIT_FAILURE);
    }

    // Crée un fichier temporaire unique
    fd = mkstemp(tmp_file);
    if (fd == -1)
    {
        puppetmaster_perror("heredoc tmp file creation");
        exit(EXIT_FAILURE);
    }

    // Collecte l'input jusqu'au délimiteur
    while (1)
    {
        line = readline("> ");
        if (!line)  // EOF (Ctrl+D)
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
    close(fd);

    // Réouvre le fichier en lecture et redirige vers stdin
    fd = open(tmp_file, O_RDONLY);
    if (fd == -1)
    {
        puppetmaster_perror("heredoc reopen for reading");
        unlink(tmp_file);  // Nettoie le fichier temporaire
        exit(EXIT_FAILURE);
    }
    
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        puppetmaster_perror("heredoc dup2");
        close(fd);
        unlink(tmp_file);
        exit(EXIT_FAILURE);
    }
    
    close(fd);
    unlink(tmp_file);  // Supprime le fichier temporaire
}

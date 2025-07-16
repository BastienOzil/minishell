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

// Version corrigée pour éviter les exit() dans les builtins
void exec_output_redirection(t_cmd *cmd)
{
    int fd;

    if (!is_cmd_valid(cmd) || !cmd->outfile)
    {
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        puppetmaster_perror("invalid command or outfile");
        exit(EXIT_FAILURE);
    }

    fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        puppetmaster_perror("open outfile");
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        puppetmaster_perror("dup2");
        close(fd);
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Version corrigée pour éviter les exit() dans les builtins
void exec_input_redirection(t_cmd *cmd)
{
    int fd;

    if (!is_cmd_valid(cmd) || !cmd->infile)
    {
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        puppetmaster_perror("invalid command or infile");
        exit(EXIT_FAILURE);
    }

    fd = open(cmd->infile, O_RDONLY);
    if (fd == -1)
    {
        puppetmaster_perror("open infile");
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        puppetmaster_perror("dup2");
        close(fd);
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Version corrigée pour éviter les exit() dans les builtins
void exec_append_redirection(t_cmd *cmd)
{
    int fd;

    if (!is_cmd_valid(cmd) || !cmd->outfile)
    {
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        puppetmaster_perror("invalid command or outfile for append");
        exit(EXIT_FAILURE);
    }

    fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        puppetmaster_perror("open outfile (append)");
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        puppetmaster_perror("dup2");
        close(fd);
        if (is_builtin(cmd->args[0]))
            return; // Ne pas exit() pour les builtins
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// void exec_heredoc(t_cmd *cmd)
// {
//     int fd;
//     char *line;
//     char *delimiter;
//     char tmp_file[] = "/tmp/.heredoc_tmp_XXXXXX";

//     if (!is_cmd_valid(cmd))
//     {
//         if (is_builtin(cmd->args[0]))
//             return; // Ne pas exit() pour les builtins
//         exit(EXIT_FAILURE);
//     }

//     delimiter = cmd->heredoc;
//     if (!delimiter)
//     {
//         puppetmaster_perror("heredoc delimiter is NULL");
//         if (is_builtin(cmd->args[0]))
//             return; // Ne pas exit() pour les builtins
//         exit(EXIT_FAILURE);
//     }

//     fd = mkstemp(tmp_file);
//     if (fd == -1)
//     {
//         puppetmaster_perror("heredoc tmp file creation");
//         if (is_builtin(cmd->args[0]))
//             return; // Ne pas exit() pour les builtins
//         exit(EXIT_FAILURE);
//     }

//     while (1)
//     {
//         line = readline("> ");
//         if (!line)  // EOF (Ctrl+D)
//             break;
//         if (ft_strcmp(line, delimiter) == 0)
//         {
//             free(line);
//             break;
//         }
//         write(fd, line, ft_strlen(line));
//         write(fd, "\n", 1);
//         free(line);
//     }
//     close(fd);

//     fd = open(tmp_file, O_RDONLY);
//     if (fd == -1)
//     {
//         puppetmaster_perror("heredoc reopen for reading");
//         unlink(tmp_file);
//         if (is_builtin(cmd->args[0]))
//             return; // Ne pas exit() pour les builtins
//         exit(EXIT_FAILURE);
//     }
    
//     if (dup2(fd, STDIN_FILENO) == -1)
//     {
//         puppetmaster_perror("heredoc dup2");
//         close(fd);
//         unlink(tmp_file);
//         if (is_builtin(cmd->args[0]))
//             return; // Ne pas exit() pour les builtins
//         exit(EXIT_FAILURE);
//     }
    
//     close(fd);
//     unlink(tmp_file);
// }

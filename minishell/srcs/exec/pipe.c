#include "../includes/minishell.h"

void execute_pipeline(t_cmd *cmd_list, char ***envp)
{
    int     pipefd[2];
    int     in_fd = 0;
    pid_t   pid;
    t_cmd   *cmd = cmd_list;
    char    *path;

    while (cmd)
    {
        if (cmd->next)
            pipe(pipefd);

        // Gestion des builtins dans les pipelines
        if (is_builtin(cmd->args[0]))
        {
            pid = fork(); // Fork même pour les builtins dans les pipelines
            if (pid == 0)
            {
                // Processus enfant pour builtin
                if (cmd->infile)
                    exec_input_redirection(cmd);
                else if (cmd->heredoc)
                    exec_heredoc(cmd);

                if (cmd->append)
                    exec_append_redirection(cmd);
                else if (cmd->outfile)
                    exec_output_redirection(cmd);

                if (in_fd != 0)
                {
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }
                if (cmd->next)
                {
                    close(pipefd[0]);
                    dup2(pipefd[1], STDOUT_FILENO);
                    close(pipefd[1]);
                }
                
                // Exécute le builtin et exit avec son code de retour
                int builtin_result = exec_builtin(cmd, envp);
                exit(builtin_result);
            }
        }
        else
        {
            // Commande externe
            pid = fork();
            if (pid == 0)
            {
                if (cmd->infile)
                    exec_input_redirection(cmd);
                else if (cmd->heredoc)
                    exec_heredoc(cmd);

                if (cmd->append)
                    exec_append_redirection(cmd);
                else if (cmd->outfile)
                    exec_output_redirection(cmd);

                if (in_fd != 0)
                {
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }
                if (cmd->next)
                {
                    close(pipefd[0]);
                    dup2(pipefd[1], STDOUT_FILENO);
                    close(pipefd[1]);
                }
                
                path = find_path(cmd->args[0], *envp);
                if (!path)
                {
                    puppetmaster_perror(cmd->args[0]);
                    exit(127);
                }
                execve(path, cmd->args, *envp);
                puppetmaster_perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        
        // Processus parent
        if (pid < 0)
        {
            puppetmaster_perror("fork");
            return;
        }
        
        // Ferme les descripteurs dans le parent
        if (in_fd != 0)
            close(in_fd);
        if (cmd->next)
        {
            close(pipefd[1]);
            in_fd = pipefd[0];
        }
        
        cmd = cmd->next;
    }
    
    // Attendre tous les processus enfants
    while (wait(NULL) > 0);
}

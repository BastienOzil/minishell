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
        {
            if (pipe(pipefd) == -1)
            {
                puppetmaster_perror("pipe");
                return;
            }
        }
        pid = fork();
        if (pid == -1)
        {
            puppetmaster_perror("fork");
            return;
        }
        if (pid == 0)
        {
            // Processus enfant
            if (cmd->infile)
                exec_input_redirection(cmd);
            else if (cmd->heredoc)
                exec_heredoc(cmd);
            else if (in_fd != 0)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (cmd->append)
                exec_append_redirection(cmd);
            else if (cmd->outfile)
                exec_output_redirection(cmd);
            else if (cmd->next)
            {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            if (is_builtin(cmd->args[0]))
            {
                int builtin_result = exec_builtin(cmd, envp);
                exit(builtin_result);
            }
            else
            {
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
        if (in_fd != 0)
            close(in_fd);
        
        if (cmd->next)
        {
            close(pipefd[1]);
            in_fd = pipefd[0];
        }
        
        cmd = cmd->next;
    }
    while (wait(NULL) > 0);
}

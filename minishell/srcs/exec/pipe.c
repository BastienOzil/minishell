#include "../includes/minishell.h"

void	execute_pipeline(t_exec_cmd *cmd_list, char **envp)
{
	int		pipefd[2];
	int		in_fd = 0;  // au début, l'entrée standard (stdin)
	pid_t	pid;
	t_exec_cmd	*cmd = cmd_list;

	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd); // on crée un pipe seulement si une commande suit

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
			execve(cmd->argv[0], cmd->argv, envp);
			puppetmaster_perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			if (in_fd != 0)
				close(in_fd);
			if (cmd->next)
			{
				close(pipefd[1]);
				in_fd = pipefd[0]; // pour la prochaine commande
			}
		}
		cmd = cmd->next;
	}
}

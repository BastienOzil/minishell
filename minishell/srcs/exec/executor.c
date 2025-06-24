#include "../includes/minishell.h"

// Elle exécute une commande (comme ls, echo, etc.) en créant un nouveau processus 
// à l’aide de fork() et en lançant la commande avec execve()
void	execute_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		puppetmaster_perror("fork");
		return ;
	}
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

		execve(cmd->args[0], cmd->args, envp);
		puppetmaster_perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

void	execute_all(t_cmd *cmd, char **envp)
{
	if (!cmd)
		return ;
	if (cmd->next)
		execute_pipeline(cmd, envp);
	else
		execute_cmd(cmd, envp);
}

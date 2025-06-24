#include "../includes/minishell.h"

// Elle exécute une commande (comme ls, echo, etc.) en créant un nouveau processus 
// à l’aide de fork() et en lançant la commande avec execve()
void	execute_cmd(t_exec_cmd *exec_cmd, char **envp)
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
		if (exec_cmd->infile)
			exec_input_redirection(exec_cmd);
		else if (exec_cmd->heredoc)
			exec_heredoc(exec_cmd);
		
		if (exec_cmd->append)
			exec_append_redirection(exec_cmd);
		else if (exec_cmd->outfile)
			exec_output_redirection(exec_cmd);

		execve(exec_cmd->argv[0], exec_cmd->argv, envp);
		puppetmaster_perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

void	execute_all(t_exec_cmd *exec_cmd, char **envp)
{
	if (!exec_cmd)
		return ;
	if (exec_cmd->next)
		execute_pipeline(exec_cmd, envp);
	else
		execute_cmd(exec_cmd, envp);
}

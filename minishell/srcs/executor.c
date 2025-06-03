#include "../includes/minishell.h"

//execution des commandes (fork, execve, redirections, pipes, dup2, close)
// Elle exécute une commande (comme ls, echo, etc.) en créant un nouveau processus 
// à l’aide de fork() et en lançant la commande avec execve()
void	execute_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	//cree un processus enfant
	pid = fork();
	//si fork echoue
	if (pid < 0)
	{
		puppetmaster_perror("fork");
		return ;
	}
	//cree processus enfant
	if (pid == 0)
	{
		execve(cmd->argv[0], cmd->argv, envp);
		puppetmaster_perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

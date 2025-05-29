#include "../includes/minishell.h"

//execution des commandes (fork, execve, redirections, pipes, dup2, close)
void	execute_cmd(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd->argv[0], cmd->argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
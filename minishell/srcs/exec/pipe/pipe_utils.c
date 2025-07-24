#include "../includes/minishell.h"

int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		puppetmaster_perror("pipe");
		return (-1);
	}
	return (0);
}

pid_t	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		puppetmaster_perror("fork");
	return (pid);
}

int	redirect_fd(int input_fd, int output_fd)
{
	if (dup2(input_fd, output_fd) == -1)
	{
		puppetmaster_perror("dup2");
		return (-1);
	}
	return (0);
}

void	close_unused_fds(int pipefd[2])
{
	if (pipefd[0] >= 0)
		close(pipefd[0]);
	if (pipefd[1] >= 0)
		close(pipefd[1]);
}

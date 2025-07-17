#include "../includes/minishell.h"

void	execute_pipeline(t_cmd *cmd_list, char ***envp)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		in_fd;
	int		pipefd[2];

	cmd = cmd_list;
	in_fd = 0;
	while (cmd)
	{
		if (cmd->next && create_pipe(pipefd) == -1)
			return ;
		pid = create_child_process();
		if (pid == 0)
			child_exec(cmd, in_fd, pipefd, envp);
		if (pid < 0)
			return ;
		handle_parent(cmd, &in_fd, pipefd);
		cmd = cmd->next;
	}
	wait_and_set_exit_status();
}


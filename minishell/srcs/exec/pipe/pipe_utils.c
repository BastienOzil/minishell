#include "../includes/minishell.h"

int		create_pipe(int pipefd[2]);
pid_t	create_child_process(void);
int		redirect_fd(int input_fd, int output_fd);
void	close_unused_fds(int pipefd[2]);
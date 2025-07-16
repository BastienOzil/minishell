#include "../includes/minishell.h"


void	execute_pipeline(t_cmd *cmd_list, char ***envp);
void	wait_and_set_exit_status(void);

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd;

	(void)ac;
	(void)av;

	ft_line;
	cmd.argv = ft_split("/bin/ls -l", ' ');
	cmd.infile = NULL;
	cmd.outfile = NULL;
	cmd.append = 0;
	cmd.next = NULL;
	execute_cmd(&cmd, envp);
	free_array(cmd.argv);

	cmd.argv = ft_split("/bin/echo Hello world", ' ');
	execute_cmd(&cmd, envp);
	free_array(cmd.argv);

	return (0);
}

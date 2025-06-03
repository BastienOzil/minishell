#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	if (ac > 1)
		ft_run_tests(envp);
	else
		ft_run_interactive(envp);
	return (0);
}

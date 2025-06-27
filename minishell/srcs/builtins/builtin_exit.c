#include "../../includes/minishell.h"

int	exit_builtin(char **args)
{
	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!ft_is_numeric(args[1]))
	{
		fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if (args[2])
	{
		fprintf(stderr, "exit: too many arguments\n");
		return (1);
	}
	exit(atoi(args[1]) % 256);
}
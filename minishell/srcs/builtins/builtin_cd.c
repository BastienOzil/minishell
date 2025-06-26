#include "../../includes/minishell.h"

int	cd_builtin(char **args)
{
	if (!args[1])
	{
		write(2, "cd: missing argument\n", 22);
		return (1);
	}

	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
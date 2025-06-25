#include "../../includes/minishell.h"

int	echo_builtin(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;

	printf(">> echo_builtin() appelé\n");
	
	if (args[1] && strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

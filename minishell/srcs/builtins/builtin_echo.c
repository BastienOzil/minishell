#include "../../includes/minishell.h"

int	echo_builtin(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		int j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break;
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

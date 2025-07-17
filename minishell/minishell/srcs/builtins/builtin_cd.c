#include "../../includes/minishell.h"

int	cd_builtin(char **args)
{
	struct stat sb;

	if (!args[1])
	{
		write(2, "cd: missing argument\n", 22);
		return (1);
	}
	if (stat(args[1], &sb) == -1)
	{
		perror("cd");
		return (1);
	}
	if (!S_ISDIR(sb.st_mode))
	{
		write(2, "minishell: cd: ", 15);
		write(2, args[1], strlen(args[1]));
		write(2, ": Not a directory\n", 18);
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

#include "../../includes/minishell.h"

void	print_cd_error(char *path)
{
	write(2, "minishell: cd: ", 16);
	write(2, path, strlen(path));
	write(2, ": ", 2);
	perror(NULL);
}

int	is_directory(char *path)
{
	struct stat sb;

	if (stat(path, &sb) == -1)
		return (0); // n'existe pas ou inaccessible
	return (S_ISDIR(sb.st_mode));
}

int	cd_builtin(char **args)
{
	if (!args[1])
	{
		write(2, "minishell: cd: missing argument\n", 32);
		return (1);
	}
	if (!is_directory(args[1]))
	{
		if (access(args[1], F_OK) == -1)
			print_cd_error(args[1]); // fichier n'existe pas
		else
		{
			write(2, "minishell: cd: ", 16);
			write(2, args[1], strlen(args[1]));
			write(2, ": Not a directory\n", 19);
		}
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		print_cd_error(args[1]); // ex: permission denied
		return (1);
	}
	return (0);
}

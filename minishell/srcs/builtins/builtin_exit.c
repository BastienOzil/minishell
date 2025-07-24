#include "../../includes/minishell.h"

int	exit_builtin(char **args)
{
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit(0);
	if (!ft_is_numeric(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	exit(ft_atoi(args[1]) % 256);
}

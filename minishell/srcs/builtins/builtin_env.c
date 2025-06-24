#include "../../includes/minishell.h"

int	env_builtin(char **envp)
{
	int	i = 0;

	while (envp[i])
	{
		if (envp[i][0] && ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

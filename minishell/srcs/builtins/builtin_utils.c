#include "../../includes/minishell.h"

int	is_var_exist(char *var, char ***envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while ((*envp)[i])
	{
		if (ft_strncmp(var, (*envp)[i], len) == 0
			&& (*envp)[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	add_var(char ***envp, char *arg)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	free_envp(envp);
	*envp = new_env;
}

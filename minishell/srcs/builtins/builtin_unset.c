#include "../../includes/minishell.h"

//remove new variable to env 
void	remove_var(char ***envp, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	while ((*envp)[i])
		i++;

	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return ;

	i = 0;
	while ((*envp)[i])
	{
		if ((*envp)[i] != var)
		new_env[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free_envp(envp);
	*envp = new_env;
}

int	unset_builtin(char **args, char ***envp)
{
	char *var;

	if (!args[1])
		return (export_empty(envp));
	var = is_arg_export(args[1]);
	if (!var)
		return (1);		
    if (is_var_exist(var, envp))
	{
		remove_var(envp, var);
		free(var);
		return (1);
	}
    return (0);
}

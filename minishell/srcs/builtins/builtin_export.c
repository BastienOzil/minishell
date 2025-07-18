#include "../../includes/minishell.h"

int	export_empty(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		printf("declare -x %s\n", (*envp)[i]);
		i++;
	}
	return (0);
}

char	*is_arg_export(char *str)
{
	int		i;
	int		size_var;
	char	*var;

	i = 0;
	size_var = 0;
	if (!ft_strchr(str, '='))
		return (NULL);
	while (str[i] && str[i] != '=')
	{
		size_var++;
		i++;
	}
	var = malloc(size_var + 1);
	if (!var)
		return (NULL);
	ft_memcpy(var, str, size_var);
	var[size_var] = '\0';
	return (var);
}

void	free_envp(char ***envp)
{
	int	i;

	if (!envp || !(*envp))
		return ;
	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = NULL;
}

void	replace_val(char **args, char ***envp)
{
	int		i;
	int		len;
	char	*var;

	i = 0;
	var = is_arg_export(args[1]);
	if (!var)
		return ;
	len = ft_strlen(var);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var, len) == 0
			&& (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(args[1]);
			break ;
		}
		i++;
	}
	free(var);
}

int	export_builtin(char **args, char ***envp)
{
	char	*var;

	if (!args[1])
		return (export_empty(envp));
	var = is_arg_export(args[1]);
	if (!var)
		return (1);
	if (is_var_exist(var, envp))
	{
		replace_val(args, envp);
		free(var);
		return (1);
	}
	add_var(envp, args[1]);
	free(var);
	return (0);
}

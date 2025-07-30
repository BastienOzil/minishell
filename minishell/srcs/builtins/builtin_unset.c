/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:19 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 09:50:06 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	should_keep_var(char *env_var, char *var_to_remove)
{
	int	var_len;

	var_len = ft_strlen(var_to_remove);
	if (ft_strncmp(env_var, var_to_remove, var_len) == 0
		&& env_var[var_len] == '=')
		return (0);
	return (1);
}

static void	process_env_vars(char ***envp, char **new_env, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (should_keep_var((*envp)[i], var))
		{
			new_env[j] = (*envp)[i];
			j++;
		}
		else
			free((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
}

static int	count_total_vars(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
		i++;
	return (i);
}

void	remove_var(char ***envp, char *var)
{
	char	**new_env;
	int		total_vars;

	total_vars = count_total_vars(envp);
	new_env = malloc(sizeof(char *) * total_vars);
	if (!new_env)
		return ;
	process_env_vars(envp, new_env, var);
	free(*envp);
	*envp = new_env;
}

int	unset_builtin(char **args, char ***envp)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_var_exist(args[i], envp))
			remove_var(envp, args[i]);
		i++;
	}
	return (0);
}

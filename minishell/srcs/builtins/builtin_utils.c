/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:24 by bozil             #+#    #+#             */
/*   Updated: 2025/07/29 19:03:08 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_var_exist(char *var, char ***envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while ((*envp)[i])
	{
		if (ft_strncmp(var, (*envp)[i], len) == 0 && (*envp)[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}

static char	**create_new_env_array(int size)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (NULL);
	return (new_env);
}

static void	transfer_env_vars(char **new_env, char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = (*envp)[i];
		i++;
	}
}

static int	count_env_vars(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
		i++;
	return (i);
}

void	add_var(char ***envp, char *arg)
{
	int		i;
	char	**new_env;
	char	*new_var;

	new_var = ft_strdup(arg);
	if (!new_var)
		return ;
	i = count_env_vars(envp);
	new_env = create_new_env_array(i);
	if (!new_env)
	{
		free(new_var);
		return ;
	}
	transfer_env_vars(new_env, envp);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	free(*envp);
	*envp = new_env;
}

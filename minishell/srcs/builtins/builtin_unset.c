/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:19 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:59:20 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_var(char ***envp, char *var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		if (!(ft_strncmp((*envp)[i], var, ft_strlen(var)) == 0
				&& (*envp)[i][ft_strlen(var)] == '='))
		{
			new_env[j] = ft_strdup((*envp)[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_envp(envp);
	*envp = new_env;
}

int	unset_builtin(char **args, char ***envp)
{
	char	*var;

	if (!args[1])
		return (export_empty(envp));
	var = ft_strdup(args[1]);
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

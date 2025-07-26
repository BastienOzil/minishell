/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:19 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 16:12:27 by aurelia          ###   ########.fr       */
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


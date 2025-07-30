/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:08:02 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 10:24:18 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_strings(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static void	cleanup_partial_env(char **new_env, int up_to)
{
	while (--up_to >= 0)
		free(new_env[up_to]);
	free(new_env);
}

static char	**allocate_env_array(int count)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	return (new_env);
}

char	**safe_dup_env(char **envp)
{
	int		i;
	int		count;
	char	**new_env;

	if (!envp)
		return (NULL);
	count = count_env_strings(envp);
	new_env = allocate_env_array(count);
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			cleanup_partial_env(new_env, i);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

void	safe_free_envp(char ***envp)
{
	if (!envp || !(*envp))
		return ;
	free_array(*envp);
	*envp = NULL;
}

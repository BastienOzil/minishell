/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:03 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 10:18:27 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_var_name_from_export(char *str)
{
	int		i;
	int		size_var;
	char	*var;

	i = 0;
	size_var = 0;
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

static int	is_env_match(char *env, char *var, int len)
{
	return (ft_strncmp(env, var, len) == 0 && env[len] == '=');
}

void	replace_val(char *arg, char ***envp)
{
	int		i;
	int		len;
	char	*var;
	char	*new_val;

	var = get_var_name_from_export(arg);
	if (!var)
		return ;
	new_val = ft_strdup(arg);
	if (!new_val)
		return (free(var));
	len = ft_strlen(var);
	i = 0;
	while ((*envp)[i])
	{
		if (is_env_match((*envp)[i], var, len))
		{
			free((*envp)[i]);
			(*envp)[i] = new_val;
			break ;
		}
		i++;
	}
	free(var);
}

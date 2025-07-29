/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:03 by bozil             #+#    #+#             */
/*   Updated: 2025/07/28 16:37:45 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_dup_split(char **tab)
{
	char	**copy;
	int		i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		if (!copy[i])
			return (ft_free_split(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**ft_sort_env(char **env)
{
	char	**copy;
	char	*tmp;
	int		i;
	int		j;

	copy = ft_dup_split(env);
	if (!copy)
		return (NULL);
	i = 0;
	while (copy[i])
	{
		j = i + 1;
		while (copy[j])
		{
			if (ft_strcmp(copy[i], copy[j]) > 0)
			{
				tmp = copy[i];
				copy[i] = copy[j];
				copy[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (copy);
}

int export_empty(char ***envp)
{
	char	**sorted;
	int		i;
	char	*equal;

	sorted = ft_sort_env(*envp);
	if (!sorted)
		return (1);
	i = 0;
	while (sorted[i])
	{
		equal = ft_strchr(sorted[i], '=');
		if (equal)
		{
			*equal = '\0';
			printf("declare -x %s=\"%s\"\n", sorted[i], equal + 1);
			*equal = '=';
		}
		else
			printf("declare -x %s\n", sorted[i]);
		i++;
	}
	ft_free_split(sorted);
	return (0);
}

// Vérifie si un nom de variable est valide (lettres, chiffres, _)
int is_valid_identifier(char *str)
{
	int i;

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

char *get_var_name_from_export(char *str)
{
	int i;
	int size_var;
	char *var;

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

void free_envp(char ***envp)
{
	int i;

	if (!envp || !(*envp))
		return;
	i = 0;
	while ((*envp)[i])
	{
		free((*envp)[i]);
		i++;
	}
	free(*envp);
	*envp = NULL;
}

void replace_val(char *arg, char ***envp)
{
	int i;
	int len;
	char *var;

	var = get_var_name_from_export(arg);
	if (!var)
		return;
	len = ft_strlen(var);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(arg);
			break;
		}
		i++;
	}
	free(var);
}

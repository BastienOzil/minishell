/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:12 by bozil             #+#    #+#             */
/*   Updated: 2025/08/05 14:18:07 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_var_expansion(char *str, int *i, char **envp)
{
	char	*name;
	char	*value;

	name = get_expansion_name(str, i);
	if (!name)
		return (ft_strdup(""));
	if (name[0] == '\0')
	{
		free(name);
		return (ft_strdup("$"));
	}
	if (name[0] == '?' && name[1] == '\0')
	{
		free(name);
		return (ft_itoa(g_exit_status));
	}
	value = get_env_value(name, envp);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

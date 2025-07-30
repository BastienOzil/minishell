/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:46:06 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 13:03:53 y aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_and_free(char *old_str, char *to_add)
{
	char	*new_str;

	if (!old_str || !to_add)
		return (NULL);
	new_str = ft_strjoin(old_str, to_add);
	free(old_str);
	free(to_add);
	return (new_str);
}

static char	*process_variable(char *str, int *i, char *result)
{
	char	*temp;
	int		local_i;

	local_i = 0;
	temp = handle_var_expansion(&str[*i], &local_i);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	*i += local_i;
	result = join_and_free(result, temp);
	return (result);
}

static char	*process_character(char *str, int *i, char *result)
{
	char	*temp;

	temp = ft_substr(str, *i, 1);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	result = join_and_free(result, temp);
	(*i)++;
	return (result);
}

char	*expand_string(char *str)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i
				+ 1] == '_' || str[i + 1] == '?'))
			result = process_variable(str, &i, result);
		else
			result = process_character(str, &i, result);
		if (!result)
			return (NULL);
	}
	return (result);
}

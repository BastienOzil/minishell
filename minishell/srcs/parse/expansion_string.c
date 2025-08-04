/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:05:04 by bozil             #+#    #+#             */
/*   Updated: 2025/08/04 13:50:26 by bozil            ###   ########.fr       */
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

char	*process_variable(char *str, int *i, char *result)
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

char	*process_character(char *str, int *i, char *result)
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

int	is_expandable_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	*expand_string(char *str)
{
	char	*result;

	if (!str)
		return (NULL);
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '"')
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (expand_loop(str, result, 0, 0));
	return (result);
}

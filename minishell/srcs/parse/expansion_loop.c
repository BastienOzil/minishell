/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:41:35 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 18:39:15 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_quotes_loop(char c, int quote)
{
	if (c == '"' && quote != 1)
	{
		if (quote == 0)
			return (2);
		else
			return (0);
	}
	else if (c == '\'' && quote != 2)
	{
		if (quote == 0)
			return (1);
		else
			return (0);
	}
	return (quote);
}

char	*expand_loop(char *str, char *result, int i, int quote)
{
	while (str[i])
	{
		if ((str[i] == '"' && quote != 1) || (str[i] == '\'' && quote != 2))
		{
			quote = handle_quotes_loop(str[i], quote);
			i++;
		}
		else if (str[i] == '$' && str[i + 1] && is_expandable_char(str[i + 1])
			&& quote != 1)
		{
			result = process_variable(str, &i, result);
			if (!result)
				return (NULL);
		}
		else
		{
			result = process_character(str, &i, result);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

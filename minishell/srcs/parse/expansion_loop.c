/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:41:35 by bozil             #+#    #+#             */
/*   Updated: 2025/08/05 17:16:11 by bozil            ###   ########.fr       */
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

char	*expand_loop(char *str, char *result, t_expand_loop *ctx)
{
	while (str[ctx->i])
	{
		if ((str[ctx->i] == '"' && ctx->quote != 1) || (str[ctx->i] == '\''
				&& ctx->quote != 2))
		{
			ctx->quote = handle_quotes_loop(str[ctx->i], ctx->quote);
			ctx->i++;
		}
		else if (str[ctx->i] == '$' && str[ctx->i + 1]
			&& is_expandable_char(str[ctx->i + 1]) && ctx->quote != 1)
		{
			result = process_variable(str, &(ctx->i), result, ctx->envp);
			if (!result)
				return (NULL);
		}
		else
		{
			result = process_character(str, &(ctx->i), result);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

t_expand_loop	init_expand_loop(int i, int quote, char **envp)
{
	t_expand_loop	xloop;

	xloop.i = i;
	xloop.quote = quote;
	xloop.envp = envp;
	return (xloop);
}

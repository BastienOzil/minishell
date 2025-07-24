/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:11:33 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 12:12:00 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// pour &&
t_token	*handle_and(t_lexer *lexer)
{
	if (!lexer || !lexer->input)
		return (NULL);
	if (lexer->i + 1 < (int)ft_strlen(lexer->input) && lexer->input[lexer->i
		+ 1] == '&')
	{
		lexer->i += 2;
		return (new_token(TOKEN_AND, ft_strdup("&&")));
	}
	lexer->i++;
	return (new_token(TOKEN_WORD, ft_strdup("&")));
}

// pour ||
t_token	*handle_or(t_lexer *lexer)
{
	if (!lexer || !lexer->input)
		return (NULL);
	if (lexer->i + 1 < (int)ft_strlen(lexer->input) && lexer->input[lexer->i
		+ 1] == '|')
	{
		lexer->i += 2;
		return (new_token(TOKEN_OR, ft_strdup("||")));
	}
	return (handle_pipe(lexer));
}

// pour ()
t_token	*handle_parentheses(t_lexer *lexer)
{
	if (!lexer || !lexer->input)
		return (NULL);
	if (lexer->input[lexer->i] == '(')
	{
		lexer->i++;
		return (new_token(TOKEN_LPAREN, ft_strdup("(")));
	}
	else if (lexer->input[lexer->i] == ')')
	{
		lexer->i++;
		return (new_token(TOKEN_RPAREN, ft_strdup(")")));
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:10:41 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:10:42 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Lit une chaîne entre guillemets doubles
char	*get_double_quoted_string(t_lexer *lexer)
{
	int		start;
	char	*result;

	lexer->i++;
	start = lexer->i;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '"')
	{
		if (lexer->input[lexer->i] == '\\' && lexer->input[lexer->i + 1])
			lexer->i++;
		lexer->i++;
	}
	if (lexer->input[lexer->i] != '"')
		return (NULL);
	result = ft_substr(lexer->input, start, lexer->i - start);
	lexer->i++;
	return (result);
}

// Lit une chaîne entre guillemets simples
char	*get_single_quoted_string(t_lexer *lexer)
{
	int		start;
	char	*result;

	lexer->i++;
	start = lexer->i;
	while (lexer->input[lexer->i] && lexer->input[lexer->i] != '\'')
		lexer->i++;
	if (lexer->input[lexer->i] != '\'')
		return (NULL);
	result = ft_substr(lexer->input, start, lexer->i - start);
	lexer->i++;
	return (result);
}

// Gère les guillemets dans le lexer
t_token	*handle_quotes(t_lexer *lexer)
{
	char	*value;

	if (lexer->input[lexer->i] == '"')
	{
		value = get_double_quoted_string(lexer);
		if (!value)
			return (NULL);
		return (new_token(TOKEN_DQUOTE, value));
	}
	else if (lexer->input[lexer->i] == '\'')
	{
		value = get_single_quoted_string(lexer);
		if (!value)
			return (NULL);
		return (new_token(TOKEN_SQUOTE, value));
	}
	return (NULL);
}

// Vérifie si c'est un caractère de guillemet
int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:10:41 by bozil             #+#    #+#             */
/*   Updated: 2025/08/05 17:11:01 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_double_quoted_string(t_lexer *lexer, char **envp)
{
	int		start;
	char	*raw_content;
	char	*expanded_content;

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
	raw_content = ft_substr(lexer->input, start, lexer->i - start);
	lexer->i++;
	if (!raw_content)
		return (NULL);
	expanded_content = expand_string(raw_content, envp);
	free(raw_content);
	if (expanded_content)
		return (expanded_content);
	else
		return (ft_strdup(""));
}

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

t_token	*handle_quotes(t_lexer *lexer, char **envp)
{
	char	*value;

	if (lexer->input[lexer->i] == '"')
	{
		value = get_double_quoted_string(lexer, envp);
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

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

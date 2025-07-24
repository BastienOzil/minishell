/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:52:56 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 12:58:43 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*handle_char(t_lexer *lexer, char *result)
{
	if (lexer->input[lexer->i] == '"')
		result = handle_double_quote(lexer, result);
	else if (lexer->input[lexer->i] == '\'')
		result = handle_single_quote(lexer, result);
	else if (lexer->input[lexer->i] == '$')
		result = handle_variable2(lexer, result);
	else
		result = handle_regular_char(lexer, result);
	return (result);
}

static int	is_end_of_word(char c)
{
	return (is_space(c) || is_special_except_quotes_and_dollar(c));
}

t_token	*get_complex_word(t_lexer *lexer)
{
	char	*result;
	int		has_content;

	result = ft_strdup("");
	has_content = 0;
	while (lexer->input[lexer->i] && !is_end_of_word(lexer->input[lexer->i]))
	{
		result = handle_char(lexer, result);
		if (!result)
			return (NULL);
		has_content = 1;
	}
	if (!has_content)
		return (free(result), NULL);
	return (new_token(TOKEN_WORD, result));
}


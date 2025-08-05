/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_complexe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurgeorg <aurgeorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:52:56 by bozil             #+#    #+#             */
/*   Updated: 2025/08/05 12:51:30 by aurgeorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*handle_char(t_lexer *lexer, char *result, char **envp)
{
	if (lexer->input[lexer->i] == '"')
		result = handle_double_quote(lexer, result, envp);
	else if (lexer->input[lexer->i] == '\'')
		result = handle_single_quote(lexer, result);
	else if (lexer->input[lexer->i] == '$')
		result = handle_variable_utils(lexer, result, envp);
	else
		result = handle_regular_char(lexer, result);
	return (result);
}

static int	is_end_of_word(char c)
{
	return (is_space(c) || is_special_except_quotes_and_dollar(c));
}

t_token	*get_complex_word(t_lexer *lexer, char **envp)
{
	char	*result;
	int		has_content;

	result = ft_strdup("");
	has_content = 0;
	while (lexer->input[lexer->i] && !is_end_of_word(lexer->input[lexer->i]))
	{
		result = handle_char(lexer, result, envp);
		if (!result)
			return (NULL);
		has_content = 1;
	}
	if (!has_content)
		return (free(result), NULL);
	return (new_token(TOKEN_WORD, result));
}

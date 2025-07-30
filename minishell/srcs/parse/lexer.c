/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:12:47 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 16:31:33 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_spaces(t_lexer *lexer)
{
	while (lexer->input[lexer->i] && is_space(lexer->input[lexer->i]))
		lexer->i++;
}

char	*get_word(t_lexer *lexer)
{
	int	start;

	start = lexer->i;
	while (lexer->input[lexer->i] && !is_space(lexer->input[lexer->i])
		&& !is_special(lexer->input[lexer->i]))
		lexer->i++;
	return (ft_substr(lexer->input, start, lexer->i - start));
}

int	is_special_except_quotes_and_dollar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '('
		|| c == ')');
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*get_next_token(t_lexer *lexer)
{
	skip_spaces(lexer);
	if (!lexer->input[lexer->i])
		return (new_token(TOKEN_EOF, NULL));
	if (lexer->input[lexer->i] == '|')
		return (handle_pipe(lexer));
	if (lexer->input[lexer->i] == '<')
		return (handle_input_redirection(lexer));
	if (lexer->input[lexer->i] == '>')
		return (handle_output_redirection(lexer));
	if (lexer->input[lexer->i] == '&')
		return (handle_and(lexer));
	if (lexer->input[lexer->i] == '(' || lexer->input[lexer->i] == ')')
		return (handle_parentheses(lexer));
	return (get_complex_word(lexer));
}

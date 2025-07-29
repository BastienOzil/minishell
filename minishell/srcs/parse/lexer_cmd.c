/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:11:01 by bozil             #+#    #+#             */
/*   Updated: 2025/07/29 11:37:55 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *handle_pipe(t_lexer *lexer)
{
	lexer->i++;
	return (new_token(TOKEN_PIPE, ft_strdup("|")));
}

t_token *handle_input_redirection(t_lexer *lexer)
{
	if (lexer->input[lexer->i + 1] == '<')
	{
		lexer->i += 2;
		return (new_token(TOKEN_HEREDOC, ft_strdup("<<")));
	}
	lexer->i++;
	return (new_token(TOKEN_INFILE, ft_strdup("<")));
}

static int check_double_output_error(t_lexer *lexer)
{
	int save_pos;

	save_pos = lexer->i;
	lexer->i++;
	skip_spaces(lexer);
	if (lexer->input[lexer->i] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	lexer->i = save_pos;
	return (0);
}

t_token *handle_output_redirection(t_lexer *lexer)
{
	if (lexer->input[lexer->i + 1] == '>')
	{
		lexer->i += 2;
		return (new_token(TOKEN_APPEND, ft_strdup(">>")));
	}
	if (check_double_output_error(lexer))
		return (NULL);
	lexer->i++;
	return (new_token(TOKEN_OUTFILE, ft_strdup(">")));
}

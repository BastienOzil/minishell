/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:13:09 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 16:52:24 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_newline(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
		2);
}

void	error_tokken(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
}

void	error_pipe(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
}

void	parse_redir(t_parser *parser, t_cmd *node)
{
	t_token_type	redir_type;

	if (!parser || !parser->current || !node || parser->error)
		return ;
	redir_type = parser->current->type;
	advance_token(parser);
	if (!parser->current || parser->current->type != TOKEN_WORD)
	{
		if (!parser->current || parser->current->type == TOKEN_EOF)
			error_newline();
		else if (is_redir_token(parser->current->type))
			error_tokken();
		else if (parser->current->type == TOKEN_PIPE)
			error_pipe();
		parser->error = 1;
		return ;
	}
	if (!validate_redir_syntax(parser, node, redir_type))
	{
		parser->error = 1;
		return ;
	}
	apply_redirection(parser, node, redir_type);
	advance_token(parser);
}

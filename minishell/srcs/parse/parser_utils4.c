/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:13:09 by bozil             #+#    #+#             */
/*   Updated: 2025/07/29 11:39:13 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		else if (is_redir_token(parser->current->type))
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		else if (parser->current->type == TOKEN_PIPE)
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
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

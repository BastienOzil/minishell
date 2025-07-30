/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:21:59 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 09:59:42 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int validate_redir_syntax(t_parser *parser, t_cmd *node,
						  t_token_type redir_type)
{
	if (!validate_redir_token(parser))
		return (0);
	if (!check_multiple_input(node, redir_type))
		return (0);
	if (!check_multiple_output(node, redir_type))
		return (0);
	return (1);
}

static void handle_input_redir(t_parser *parser, t_cmd *node)
{
	if (!parser || !parser->current || !node)
		return;
	if (node->infile)
		free(node->infile);
	node->infile = ft_strdup(parser->current->value);
}

static void handle_output_redir(t_parser *parser, t_cmd *node, int append)
{
	if (!parser || !parser->current || !parser->current->value)
	{
		ft_putstr_fd("minishell: redirection error\n", 2);
		return;
	}
	if (node->outfile)
		free(node->outfile);
	node->outfile = ft_strdup(parser->current->value);
	node->append = append;
}

static void handle_heredoc_redir(t_parser *parser, t_cmd *node)
{
	if (!parser || !parser->current || !node)
		return;
	if (node->heredoc)
		free(node->heredoc);
	node->heredoc = ft_strdup(parser->current->value);
}

void apply_redirection(t_parser *parser, t_cmd *node,
					   t_token_type redir_type)
{
	if (!parser || !node)
		return;
	if (redir_type == TOKEN_INFILE)
		handle_input_redir(parser, node);
	else if (redir_type == TOKEN_OUTFILE)
		handle_output_redir(parser, node, 0);
	else if (redir_type == TOKEN_APPEND)
		handle_output_redir(parser, node, 1);
	else if (redir_type == TOKEN_HEREDOC)
		handle_heredoc_redir(parser, node);
}

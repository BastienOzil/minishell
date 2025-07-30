/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:03:58 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 09:58:27 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd *create_logical_node(t_cmd *left, t_token_type op_type,
								  t_parser *parser)
{
	t_cmd *logical;

	logical = new_node(op_type == TOKEN_AND ? NODE_AND : NODE_OR);
	if (!logical)
	{
		free_ast(left);
		return (NULL);
	}
	logical->left = left;
	logical->right = parse_pipeline(parser);
	if (!logical->right)
	{
		free_ast(logical);
		return (NULL);
	}
	return (logical);
}

t_cmd *parse_logical(t_parser *parser)
{
	t_cmd *left;
	t_token_type op_type;

	if (!parser || !parser->current)
		return (NULL);
	left = parse_pipeline(parser);
	if (!left)
		return (NULL);
	while (parser->current && (parser->current->type == TOKEN_AND || parser->current->type == TOKEN_OR))
	{
		op_type = parser->current->type;
		advance_token(parser);
		left = create_logical_node(left, op_type, parser);
		if (!left)
			return (NULL);
	}
	return (left);
}

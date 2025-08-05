/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:03:58 by bozil             #+#    #+#             */
/*   Updated: 2025/08/05 13:39:46 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*create_logical_node(t_cmd *left, t_token_type op_type,
		t_parser *parser, char **envp)
{
	t_cmd	*logical;

	if (op_type == TOKEN_AND)
		logical = new_node(NODE_AND);
	else
		logical = new_node(NODE_OR);
	if (!logical)
	{
		free_ast(left);
		return (NULL);
	}
	logical->left = left;
	logical->right = parse_pipeline(parser, envp);
	if (!logical->right)
	{
		free_ast(logical);
		return (NULL);
	}
	return (logical);
}

t_cmd	*parse_logical(t_parser *parser, char **envp)
{
	t_cmd			*left;
	t_token_type	op_type;

	if (!parser || !parser->current)
		return (NULL);
	left = parse_pipeline(parser, envp);
	if (!left)
		return (NULL);
	while (parser->current && (parser->current->type == TOKEN_AND
			|| parser->current->type == TOKEN_OR))
	{
		op_type = parser->current->type;
		advance_token(parser);
		left = create_logical_node(left, op_type, parser, envp);
		if (!left)
			return (NULL);
	}
	return (left);
}

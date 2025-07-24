/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:54:43 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 13:58:24 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Parse une séquence de commandes reliées par des pipes
t_cmd	*parse_pipeline(t_parser *parser)
{
	t_cmd	*left;
	t_cmd	*pipeline;

	if (!parser || !parser->current)
		return (NULL);
	left = parse_command(parser);
	if (!left)
		return (NULL);
	while (match_token(parser, TOKEN_PIPE))
	{
		advance_token(parser);
		pipeline = new_node(NODE_PIPELINE);
		if (!pipeline)
		{
			free_ast(left);
			return (NULL);
		}
		pipeline->left = left;
		pipeline->right = parse_command(parser);
		if (!pipeline->right)
		{
			free_ast(pipeline);
			return (NULL);
		}
		left = pipeline;
	}
	return (left);
}

// Point d'entrée principal du parser
t_cmd	*parse(t_token *tokens)
{
	t_parser	parser;

	if (!tokens)
		return (NULL);
	parser.tokens = tokens;
	parser.current = tokens;
	parser.error = 0;
	return (parse_logical(&parser));
}

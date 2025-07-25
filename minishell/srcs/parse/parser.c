/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:54:43 by bozil             #+#    #+#             */
/*   Updated: 2025/07/25 10:32:27 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Vérifie la validité du pipe
static int validate_pipe_syntax(t_parser *parser)
{
	if (!parser->current || parser->current->type == TOKEN_EOF || parser->current->type == TOKEN_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		parser->error = 1;
		return (0);
	}
	return (1);
}

// Crée un nœud pipeline
static t_cmd *create_pipeline_node(t_cmd *left, t_cmd *right)
{
	t_cmd *pipeline;

	pipeline = new_node(NODE_PIPELINE);
	if (!pipeline)
		return (NULL);
	pipeline->left = left;
	pipeline->right = right;
	return (pipeline);
}

// Parse une séquence de commandes reliées par des pipes
t_cmd *parse_pipeline(t_parser *parser)
{
	t_cmd *left;
	t_cmd *pipeline;

	if (!parser || !parser->current)
		return (NULL);
	left = parse_command(parser);
	if (!left)
		return (NULL);
	while (match_token(parser, TOKEN_PIPE))
	{
		advance_token(parser);
		if (!validate_pipe_syntax(parser))
		{
			free_ast(left);
			return (NULL);
		}
		pipeline = create_pipeline_node(left, parse_command(parser));
		if (!pipeline || !pipeline->right)
		{
			free_ast(pipeline);
			return (NULL);
		}
		left = pipeline;
	}
	return (left);
}

// Point d'entrée principal du parser
t_cmd *parse(t_token *tokens)
{
	t_parser parser;

	if (!tokens)
		return (NULL);
	parser.tokens = tokens;
	parser.current = tokens;
	parser.error = 0;
	return (parse_logical(&parser));
}
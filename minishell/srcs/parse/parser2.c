/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:57:21 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 10:00:47 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void handle_quoted_token(t_parser *parser, t_cmd *node)
{
	char *value;
	char *arg;

	if (!parser || !parser->current || !node)
		return;
	if (parser->current->type == TOKEN_DQUOTE)
	{
		value = expand_string(parser->current->value);
		if (value)
		{
			node->args = add_arg(node->args, value);
			free(value);
		}
	}
	else if (parser->current->type == TOKEN_SQUOTE)
	{
		arg = ft_strdup(parser->current->value);
		if (!arg)
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
		node->args = add_arg(node->args, arg);
	}
	advance_token(parser);
}

static void handle_word_token(t_parser *parser, t_cmd *node)
{
	char *arg;

	arg = ft_strdup(parser->current->value);
	if (!arg)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	node->args = add_arg(node->args, arg);
	free(arg);
	advance_token(parser);
}

static void handle_quote_or_redir(t_parser *parser, t_cmd *node)
{
	if (parser->current->type == TOKEN_DQUOTE || parser->current->type == TOKEN_SQUOTE)
		handle_quoted_token(parser, node);
	else if (is_redir_token(parser->current->type))
		parse_redir(parser, node);
	else
		advance_token(parser);
}

static int is_end_of_command(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_EOF || type == TOKEN_AND || type == TOKEN_OR);
}

t_cmd *parse_command(t_parser *parser)
{
	t_cmd *node;

	if (!parser || !parser->current)
		return (NULL);
	node = new_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	while (parser->current && !is_end_of_command(parser->current->type))
	{
		if (parser->error)
			break;
		if (parser->current->type == TOKEN_WORD)
			handle_word_token(parser, node);
		else
			handle_quote_or_redir(parser, node);
	}
	return (node);
}

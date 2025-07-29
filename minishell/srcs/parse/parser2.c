/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:57:21 by bozil             #+#    #+#             */
/*   Updated: 2025/07/28 17:07:01 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Traite les tokens quotés et les ajoute comme arguments
static void	handle_quoted_token(t_parser *parser, t_cmd *node)
{
	char	*value;
	char	*arg;

	if (!parser || !parser->current || !node)
		return ;
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

// Traite les tokens simples
static void	handle_word_token(t_parser *parser, t_cmd *node)
{
	char	*arg;

	arg = ft_strdup(parser->current->value);
	if (!arg)
	{
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	node->args = add_arg(node->args, arg);
	advance_token(parser);
}

// Gère les quotes et redirections
static void	handle_quote_or_redir(t_parser *parser, t_cmd *node)
{
	if (parser->current->type == TOKEN_DQUOTE
		|| parser->current->type == TOKEN_SQUOTE)
		handle_quoted_token(parser, node);
	else if (is_redir_token(parser->current->type))
		parse_redir(parser, node);
	else
		advance_token(parser);
}

// Vérifie fin de commande
static int	is_end_of_command(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_EOF
		|| type == TOKEN_AND || type == TOKEN_OR);
}

static int	count_non_empty(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (*args[i])
			count++;
		i++;
	}
	return (count);
}

char	**remove_empty_args(char **args)
{
	char	**new;
	int		i;
	int		j;

	new = malloc(sizeof(char *) * (count_non_empty(args) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (*args[i])
			new[j++] = ft_strdup(args[i]);
		i++;
	}
	new[j] = NULL;
	ft_free_split(args);
	return (new);
}

// Parse une commande simple avec ses arguments et redirections
t_cmd	*parse_command(t_parser *parser)
{
	t_cmd	*node;

	if (!parser || !parser->current)
		return (NULL);
	node = new_node(NODE_COMMAND);
	if (!node)
		return (NULL);
	while (parser->current && !is_end_of_command(parser->current->type))
	{
		if (parser->error)
			break ;
		if (parser->current->type == TOKEN_WORD)
			handle_word_token(parser, node);
		else
			handle_quote_or_redir(parser, node);
	}
	node->args = remove_empty_args(node->args);
	return (node);
}

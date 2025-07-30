/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:21:23 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 16:18:02 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*new_node(t_node_type type)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->heredoc = NULL;
	node->freed = 0;
	return (node);
}

void	advance_token(t_parser *parser)
{
	if (parser && parser->current)
		parser->current = parser->current->next;
}

int	match_token(t_parser *parser, t_token_type type)
{
	if (!parser || !parser->current)
		return (0);
	return (parser->current->type == type);
}

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_INFILE || type == TOKEN_OUTFILE
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

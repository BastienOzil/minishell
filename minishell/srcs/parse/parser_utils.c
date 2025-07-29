/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:21:23 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 18:54:58 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Crée une nouvelle boucle AST du type spécifié
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

// Avance au token suivant dans le parser
void	advance_token(t_parser *parser)
{
	if (parser && parser->current)
		parser->current = parser->current->next;
}

// Vérifie si le token courant correspond au type donné
int	match_token(t_parser *parser, t_token_type type)
{
	if (!parser || !parser->current)
		return (0);
	return (parser->current->type == type);
}

// Vérifie si le token est un opérateur de redirection
int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_INFILE || type == TOKEN_OUTFILE
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}


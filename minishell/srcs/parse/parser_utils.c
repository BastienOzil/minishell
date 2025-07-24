/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:21:23 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 13:25:48 by bozil            ###   ########.fr       */
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

// Parse la redirection et l'applique à la boucle - VERSION CORRIGÉE
void	parse_redir(t_parser *parser, t_cmd *node)
{
	t_token_type	redir_type;

	if (!parser || !parser->current || !node || parser->error)
		return ;
	redir_type = parser->current->type;
	advance_token(parser);
	if (!validate_redir_syntax(parser, node, redir_type))
	{
		parser->error = 1;
		if (parser->current)
			advance_token(parser);
		return ;
	}
	apply_redirection(parser, node, redir_type);
	if (parser->current)
		advance_token(parser);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:21:59 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 13:43:14 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Valide la syntaxe de redirection ET vérifie les redirections multiples
int	validate_redir_syntax(t_parser *parser, t_cmd *node,
		t_token_type redir_type)
{
	if (!parser || !parser->current || parser->current->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return (0);
	}
	if (redir_type == TOKEN_INFILE && node->infile)
	{
		ft_putstr_fd("minishell: multiple input redirections\n", 2);
		return (0);
	}
	if (redir_type == TOKEN_HEREDOC && node->heredoc)
	{
		ft_putstr_fd("minishell: multiple heredoc redirections\n", 2);
		return (0);
	}
	if ((redir_type == TOKEN_OUTFILE || redir_type == TOKEN_APPEND)
		&& node->outfile)
	{
		ft_putstr_fd("minishell: multiple output redirections\n", 2);
		return (0);
	}
	return (1);
}

// Redirige l'entrée et met a jour la boucle
static void	handle_input_redir(t_parser *parser, t_cmd *node)
{
	if (!parser || !parser->current || !node)
		return ;
	if (node->infile)
		free(node->infile);
	node->infile = ft_strdup(parser->current->value);
}

// Gère les redirections de sortie et met a jour la boucle
static void	handle_output_redir(t_parser *parser, t_cmd *node, int append)
{
	if (!parser || !parser->current || !parser->current->value)
	{
		ft_putstr_fd("minishell: redirection error\n", 2);
		return ;
	}
	if (node->outfile)
		free(node->outfile);
	node->outfile = ft_strdup(parser->current->value);
	node->append = append;
}

// Gère un heredoc et met a jour la boucle
static void	handle_heredoc_redir(t_parser *parser, t_cmd *node)
{
	if (!parser || !parser->current || !node)
		return ;
	if (node->heredoc)
		free(node->heredoc);
	node->heredoc = ft_strdup(parser->current->value);
}

// Applique la redirection selon son type
void	apply_redirection(t_parser *parser, t_cmd *node,
		t_token_type redir_type)
{
	if (!parser || !node)
		return ;
	if (redir_type == TOKEN_INFILE)
		handle_input_redir(parser, node);
	else if (redir_type == TOKEN_OUTFILE)
		handle_output_redir(parser, node, 0);
	else if (redir_type == TOKEN_APPEND)
		handle_output_redir(parser, node, 1);
	else if (redir_type == TOKEN_HEREDOC)
		handle_heredoc_redir(parser, node);
}

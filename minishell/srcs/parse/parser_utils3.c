/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:21:59 by bozil             #+#    #+#             */
/*   Updated: 2025/07/25 11:21:15 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Valide la syntaxe de redirection
int	validate_redir_syntax(t_parser *parser, t_cmd *node,
		t_token_type redir_type)
{
	if (!validate_redir_token(parser))
		return (0);
	if (!check_multiple_input(node, redir_type))
		return (0);
	if (!check_multiple_output(node, redir_type))
		return (0);
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

// Parse la redirection et l'applique à la boucle
void	parse_redir(t_parser *parser, t_cmd *node)
{
	t_token_type	redir_type;

	if (!parser || !parser->current || !node || parser->error)
		return ;
	redir_type = parser->current->type;
	advance_token(parser);
	if (!parser->current || parser->current->type != TOKEN_WORD)
	{
		if (!parser->current || parser->current->type == TOKEN_EOF)
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		else if (is_redir_token(parser->current->type))
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		else if (parser->current->type == TOKEN_PIPE)
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		parser->error = 1;
		return ;
	}
	if (!validate_redir_syntax(parser, node, redir_type))
	{
		parser->error = 1;
		return ;
	}
	apply_redirection(parser, node, redir_type);
	advance_token(parser);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:00:00 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 19:45:26 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Affiche l'erreur selon le type de token
static void print_token_error(t_token_type type)
{
    if (type == TOKEN_EOF)
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
    else if (type == TOKEN_PIPE)
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
    else if (type == TOKEN_OUTFILE)
        ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
    else if (type == TOKEN_INFILE)
        ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
    else if (type == TOKEN_APPEND)
        ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
    else if (type == TOKEN_HEREDOC)
        ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
    else
        ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
}

// Vérifie la validité du token après redirection
int validate_redir_token(t_parser *parser)
{
    if (!parser->current || parser->current->type != TOKEN_WORD)
    {
        if (!parser->current)
            print_token_error(TOKEN_EOF);
        else
            print_token_error(parser->current->type);
        return (0);
    }
    return (1);
}

// Bash utilise la dernière redirection d'entrée spécifiée
int check_multiple_input(t_cmd *node, t_token_type type)
{
    (void)node;
    (void)type;
    return (1);
}
 
// Bash utilise la dernière redirection de sortie spécifiée
int check_multiple_output(t_cmd *node, t_token_type type)
{
    (void)node;
    (void)type;
    return (1);
}

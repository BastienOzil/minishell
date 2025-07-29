/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:38:21 by bozil             #+#    #+#             */
/*   Updated: 2025/07/29 11:38:01 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *handle_and(t_lexer *lexer)
{
    if (lexer->input[lexer->i + 1] == '&')
    {
        lexer->i += 2;
        return (new_token(TOKEN_AND, ft_strdup("&&")));
    }
    lexer->i++;
    return (new_token(TOKEN_WORD, ft_strdup("&")));
}

t_token *handle_or(t_lexer *lexer)
{
    if (lexer->input[lexer->i + 1] == '|')
    {
        lexer->i += 2;
        return (new_token(TOKEN_OR, ft_strdup("||")));
    }
    return (handle_pipe(lexer));
}

t_token *handle_parentheses(t_lexer *lexer)
{
    if (lexer->input[lexer->i] == '(')
    {
        lexer->i++;
        return (new_token(TOKEN_LPAREN, ft_strdup("(")));
    }
    else
    {
        lexer->i++;
        return (new_token(TOKEN_RPAREN, ft_strdup(")")));
    }
}

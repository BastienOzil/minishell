#include "../includes/minishell.h"

// pour pipe |
t_token *handle_pipe(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    
    lexer->i++;
    return (new_token(TOKEN_PIPE, ft_strdup("|")));
}

// pour < et <<  
t_token *handle_input_redirection(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    if (lexer->i + 1 < (int)ft_strlen(lexer->input) && 
        lexer->input[lexer->i + 1] == '<')
    {
        lexer->i += 2;
        return (new_token(TOKEN_HEREDOC, ft_strdup("<<")));
    }
    lexer->i++;
    return (new_token(TOKEN_INFILE, ft_strdup("<")));
}

// pour > et >>
t_token *handle_output_redirection(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    if (lexer->i + 1 < (int)ft_strlen(lexer->input) && 
        lexer->input[lexer->i + 1] == '>')
    {
        lexer->i += 2;
        return (new_token(TOKEN_APPEND, ft_strdup(">>")));
    }
    lexer->i++;
    return (new_token(TOKEN_OUTFILE, ft_strdup(">")));
}

// pour &&
t_token *handle_and(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    if (lexer->i + 1 < (int)ft_strlen(lexer->input) && 
        lexer->input[lexer->i + 1] == '&')
    {
        lexer->i += 2;
        return (new_token(TOKEN_AND, ft_strdup("&&")));
    }
    lexer->i++;
    return (new_token(TOKEN_WORD, ft_strdup("&")));
}

// pour ||
t_token *handle_or(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    if (lexer->i + 1 < (int)ft_strlen(lexer->input) && 
        lexer->input[lexer->i + 1] == '|')
    {
        lexer->i += 2;
        return (new_token(TOKEN_OR, ft_strdup("||")));
    }
    return (handle_pipe(lexer));
}

// pour ()
t_token *handle_parentheses(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    
    if (lexer->input[lexer->i] == '(')
    {
        lexer->i++;
        return (new_token(TOKEN_LPAREN, ft_strdup("(")));
    }
    else if (lexer->input[lexer->i] == ')')
    {
        lexer->i++;
        return (new_token(TOKEN_RPAREN, ft_strdup(")")));
    }
    return (NULL);
}

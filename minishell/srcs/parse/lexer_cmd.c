#include "../includes/minishell.h"

// pour pipe |
t_token *handle_pipe(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    
    lexer->i++;
    return (new_token(TOKEN_PIPE, ft_substr("|", 0, 1)));
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
        return (new_token(TOKEN_HEREDOC, ft_substr("<<", 0, 2)));
    }
    lexer->i++;
    return (new_token(TOKEN_INFILE, ft_substr("<", 0, 1)));
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
        return (new_token(TOKEN_APPEND, ft_substr(">>", 0, 2)));
    }
    lexer->i++;
    return (new_token(TOKEN_OUTFILE, ft_substr(">", 0, 1)));
}

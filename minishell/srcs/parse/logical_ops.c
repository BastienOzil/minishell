#include "../includes/minishell.h"

// Gère l'opérateur AND (&&)
t_token *handle_and(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    if (lexer->i + 1 < (int)ft_strlen(lexer->input) && 
        lexer->input[lexer->i + 1] == '&')
    {
        lexer->i += 2;
        return (new_token(TOKEN_AND, ft_substr("&&", 0, 2)));
    }
    return (NULL);
}

// Gère l'opérateur OR (||)
t_token *handle_or(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    if (lexer->i + 1 < (int)ft_strlen(lexer->input) && 
        lexer->input[lexer->i + 1] == '|')
    {
        lexer->i += 2;
        return (new_token(TOKEN_OR, ft_substr("||", 0, 2)));
    }
    return (handle_pipe(lexer));
}

// Gère les parenthèses
t_token *handle_parentheses(t_lexer *lexer)
{
    if (!lexer || !lexer->input)
        return (NULL);
    
    if (lexer->input[lexer->i] == '(')
    {
        lexer->i++;
        return (new_token(TOKEN_LPAREN, ft_substr("(", 0, 1)));
    }
    else if (lexer->input[lexer->i] == ')')
    {
        lexer->i++;
        return (new_token(TOKEN_RPAREN, ft_substr(")", 0, 1)));
    }
    return (NULL);
}

// Parse les expressions logiques (AND/OR)
t_cmd *parse_logical(t_parser *parser)
{
    t_cmd *left;
    t_cmd *logical;
    t_token_type op_type;

    if (!parser || !parser->current)
        return (NULL);

    left = parse_pipeline(parser);
    if (!left)
        return (NULL);
    
    while (parser->current && 
           (parser->current->type == TOKEN_AND || parser->current->type == TOKEN_OR))
    {
        op_type = parser->current->type;
        advance_token(parser);
        
        logical = new_node(op_type == TOKEN_AND ? NODE_AND : NODE_OR);
        if (!logical)
        {
            free_ast(left);
            return (NULL);
        }
        
        logical->left = left;
        logical->right = parse_pipeline(parser);
        if (!logical->right)
        {
            free_ast(logical);
            return (NULL);
        }
        
        left = logical;
    }
    return (left);
}

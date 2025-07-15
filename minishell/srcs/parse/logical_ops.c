#include "../includes/minishell.h"

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

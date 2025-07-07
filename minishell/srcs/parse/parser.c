#include "../includes/minishell.h"

// Traite les tokens quotés et les ajoute comme arguments
static void handle_quoted_token(t_parser *parser, t_cmd *node)
{
    char *value;

    if (!parser || !parser->current || !node)
        return;

    if (parser->current->type == TOKEN_DQUOTE)
    {
        value = expand_string(parser->current->value);
        if (value)
        {
            node->args = add_arg(node->args, value);
            free(value);  // Libère value APRÈS l'avoir ajouté
        }
    }
    else if (parser->current->type == TOKEN_SQUOTE)
    {
        node->args = add_arg(node->args, parser->current->value);
    }
    advance_token(parser);
}

// Parse une commande simple avec ses arguments et redirections
t_cmd *parse_command(t_parser *parser)
{
    t_cmd *node;

    if (!parser || !parser->current)
        return (NULL);

    node = new_node(NODE_COMMAND);
    if (!node)
        return (NULL);

    while (parser->current && 
           parser->current->type != TOKEN_PIPE && 
           parser->current->type != TOKEN_EOF && 
           parser->current->type != TOKEN_AND && 
           parser->current->type != TOKEN_OR)
    {
        if (parser->current->type == TOKEN_WORD)
        {
            node->args = add_arg(node->args, parser->current->value);
            advance_token(parser);
        }
        else if (parser->current->type == TOKEN_DQUOTE || 
                 parser->current->type == TOKEN_SQUOTE)
        {
            handle_quoted_token(parser, node);
        }
        else if (is_redir_token(parser->current->type))
        {
            parse_redir(parser, node);
        }
        else
        {
            advance_token(parser);
        }
    }
    return (node);
}

// Parse une séquence de commandes reliées par des pipes
t_cmd *parse_pipeline(t_parser *parser)
{
    t_cmd *left;
    t_cmd *pipeline;

    if (!parser || !parser->current)
        return (NULL);

    left = parse_command(parser);
    if (!left)
        return (NULL);

    while (match_token(parser, TOKEN_PIPE))
    {
        advance_token(parser);
        pipeline = new_node(NODE_PIPELINE);
        if (!pipeline)
        {
            free_ast(left);
            return (NULL);
        }
        pipeline->left = left;
        pipeline->right = parse_command(parser);
        if (!pipeline->right)
        {
            free_ast(pipeline);
            return (NULL);
        }
        left = pipeline;
    }
    return (left);
}

// Point d'entrée principal du parser
t_cmd *parse(t_token *tokens)
{
    t_parser parser;

    if (!tokens)
        return (NULL);

    parser.tokens = tokens;
    parser.current = tokens;
    return (parse_logical(&parser));
}

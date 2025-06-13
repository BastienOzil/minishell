#include "../includes/minishell.h"

// Parse une commande simple avec ses arguments et redirections
t_cmd *parse_command(t_parser *parser)
{
    t_cmd *node;

    node = new_node(NODE_COMMAND);
    if (!node)
        return (NULL);
    while (parser->current && parser->current->type != TOKEN_PIPE && parser->current->type != TOKEN_EOF)
    {
        if (parser->current->type == TOKEN_WORD)
        {
            node->args = add_arg(node->args, parser->current->value);
            advance_token(parser);
        }
        else if (is_redir_token(parser->current->type))
            parse_redir(parser, node);
        else
            advance_token(parser);
    }
    return (node);
}

// Parse une séquence de commandes reliées par des pipes
t_cmd *parse_pipeline(t_parser *parser)
{
    t_cmd *left;
    t_cmd *pipeline;

    left = parse_command(parser);
    if (!left)
        return (NULL);
    while (match_token(parser, TOKEN_PIPE))
    {
        advance_token(parser);
        pipeline = new_node(NODE_PIPELINE);
        if (!pipeline)
            return (NULL);
        pipeline->left = left;
        pipeline->right = parse_command(parser);
        left = pipeline;
    }
    return (left);
}

// Point d'entrée principal du parser
t_cmd *parse(t_token *tokens)
{
    t_parser parser;

    parser.tokens = tokens;
    parser.current = tokens;
    return (parse_pipeline(&parser));
}

#include "../includes/minishell.h"

// Crée une nouvelle boucle AST du type spécifié
t_cmd *new_node(t_node_type type)
{
    t_cmd *node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->type = type;
    node->args = NULL;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;  // Ajout de l'initialisation manquante
    node->infile = NULL;
    node->outfile = NULL;
    node->append = 0;
    node->heredoc = NULL;
    return (node);
}

// Avance au token suivant dans le parser
void advance_token(t_parser *parser)
{
    if (parser && parser->current)
        parser->current = parser->current->next;
}

// Vérifie si le token courant correspond au type donné
int match_token(t_parser *parser, t_token_type type)
{
    if (!parser || !parser->current)
        return (0);
    return (parser->current->type == type);
}

// Vérifie si le token est un opérateur de redirection
int is_redir_token(t_token_type type)
{
    return (type == TOKEN_INFILE || type == TOKEN_OUTFILE
        || type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

// compte le nombre d'arguments dans le tableau
static int count_args(char **args)
{
    int count;

    count = 0;
    if (args)
    {
        while (args[count])
            count++;
    }
    return (count);
}

// Libère un tableau d'arguments
static void free_arg_array(char **args)
{
    int i;

    if (!args)
        return;
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

// VERSION CORRIGÉE: Ajoute un nouvel argument à un tableau existant
char **add_arg(char **args, char *new_arg)
{
    int count;
    char **new_args;
    int i;

    if (!new_arg)
        return (args);

    count = count_args(args);
    new_args = malloc(sizeof(char *) * (count + 2));
    if (!new_args)
        return (args);

    // Copie les anciens arguments
    i = 0;
    while (i < count)
    {
        new_args[i] = ft_strdup(args[i]);
        if (!new_args[i])
        {
            // Nettoie en cas d'erreur
            while (--i >= 0)
                free(new_args[i]);
            free(new_args);
            return (args);
        }
        i++;
    }

    // Ajoute le nouvel argument
    new_args[count] = ft_strdup(new_arg);
    if (!new_args[count])
    {
        free_arg_array(new_args);
        return (args);
    }
    new_args[count + 1] = NULL;

    // Libère l'ancien tableau SEULEMENT si tout s'est bien passé
    if (args)
        free_arg_array(args);

    return (new_args);
}

// Valide la syntaxe de redirection
static int validate_redir_syntax(t_parser *parser)
{
    if (!parser || !parser->current || parser->current->type != TOKEN_WORD)
    {
        ft_putstr_fd("minishell: syntax error near redirection\n", 2);
        return (0);
    }
    return (1);
}

// Redirige l'entrée et met a jour la boucle
static void handle_input_redir(t_parser *parser, t_cmd *node)
{
    if (!parser || !parser->current || !node)
        return;
    
    if (node->infile)
        free(node->infile);
    node->infile = ft_strdup(parser->current->value);
}

// Gère les redirections de sortie et met a jour la boucle
static void handle_output_redir(t_parser *parser, t_cmd *node, int append)
{
    if (!parser || !parser->current || !node)
        return;
    
    if (node->outfile)
        free(node->outfile);
    node->outfile = ft_strdup(parser->current->value);
    node->append = append;
}

// Gère un heredoc et met a jour la boucle
static void handle_heredoc_redir(t_parser *parser, t_cmd *node)
{
    if (!parser || !parser->current || !node)
        return;
    
    if (node->heredoc)
        free(node->heredoc);
    node->heredoc = ft_strdup(parser->current->value);
}

// Applique la redirection selon son type
static void apply_redirection(t_parser *parser, t_cmd *node, 
    t_token_type redir_type)
{
    if (!parser || !node)
        return;
    
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
void parse_redir(t_parser *parser, t_cmd *node)
{
    t_token_type redir_type;

    if (!parser || !parser->current || !node)
        return;

    redir_type = parser->current->type;
    advance_token(parser);
    
    if (!validate_redir_syntax(parser))
        return;
    
    apply_redirection(parser, node, redir_type);
    advance_token(parser);
}

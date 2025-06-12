#include "../includes/minishell.h"

// Crée une nouvelle boucle AST du type spécifié
t_cmd	*new_node(t_node_type type)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->append = 0;
	node->heredoc = NULL;
	return (node);
}

// Avance au token suivant dans le parser
void	advance_token(t_parser *parser)
{
	if (parser->current)
		parser->current = parser->current->next;
}

// Vérifie si le token courant correspond au type donné
int	match_token(t_parser *parser, t_token_type type)
{
	if (!parser->current)
		return (0);
	return (parser->current->type == type);
}

// Vérifie si le token est un opérateur de redirection
int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_INFILE || type == TOKEN_OUTFILE
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

// compte le nombre d'arguments dans le tableau
static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (args)
	{
		while (args[count])
			count++;
	}
	return (count);
}

// Copie un tableau d'arguments existant dans un nouveau tableau plus grand
static char	**copy_args(char **args, int count)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			free_args(new_args);
			return (NULL);
		}
		i++;
	}
	return (new_args);
}

//Ajoute un nouvel argument a un tableau existant
char	**add_arg(char **args, char *new_arg)
{
	int		count;
	char	**new_args;

	count = count_args(args);
	new_args = copy_args(args, count);
	if (!new_args)
		return (NULL);
	new_args[count] = ft_strdup(new_arg);
	if (!new_args[count])
	{
		free_args(new_args);
		return (NULL);
	}
	new_args[count + 1] = NULL;
	if (args)
		free_args(args);
	return (new_args);
}

//Redirige l'entrée et met a jour la boucle
static void	handle_input_redir(t_parser *parser, t_cmd *node)
{
	if (node->infile)
		free(node->infile);
	node->infile = ft_strdup(parser->current->value);
}

// Gère les redirections de sortie et met a jour la boucle
static void	handle_output_redir(t_parser *parser, t_cmd *node, int append)
{
	if (node->outfile)
		free(node->outfile);
	node->outfile = ft_strdup(parser->current->value);
	node->append = append;
}

// Gère un heredoc et met a jour la boucle
static void	handle_heredoc_redir(t_parser *parser, t_cmd *node)
{
	if (node->heredoc)
		free(node->heredoc);
	node->heredoc = ft_strdup(parser->current->value);
}

// Parse la redirection et l'applique a la boucle
void	parse_redir(t_parser *parser, t_cmd *node)
{
	t_token_type	redir_type;

	redir_type = parser->current->type;
	advance_token(parser);
	if (!parser->current || parser->current->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return ;
	}
	if (redir_type == TOKEN_INFILE)
		handle_input_redir(parser, node);
	else if (redir_type == TOKEN_OUTFILE)
		handle_output_redir(parser, node, 0);
	else if (redir_type == TOKEN_APPEND)
		handle_output_redir(parser, node, 1);
	else if (redir_type == TOKEN_HEREDOC)
		handle_heredoc_redir(parser, node);
	advance_token(parser);
}


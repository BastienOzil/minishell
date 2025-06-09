#include "../includes/minishell.h"

t_ast_node	*new_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->input_file = NULL;
	node->output_file = NULL;
	node->append = 0;
	node->heredoc_delimiter = NULL;
	return (node);
}

void	advance_token(t_parser *parser)
{
	if (parser->current)
		parser->current = parser->current->next;
}

int	match_token(t_parser *parser, t_token_type type)
{
	if (!parser->current)
		return (0);
	return (parser->current->type == type);
}

int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_INFILE || type == TOKEN_OUTFILE
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

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

static void	handle_input_redir(t_parser *parser, t_ast_node *node)
{
	if (node->input_file)
		free(node->input_file);
	node->input_file = ft_strdup(parser->current->value);
}

static void	handle_output_redir(t_parser *parser, t_ast_node *node, int append)
{
	if (node->output_file)
		free(node->output_file);
	node->output_file = ft_strdup(parser->current->value);
	node->append = append;
}

static void	handle_heredoc_redir(t_parser *parser, t_ast_node *node)
{
	if (node->heredoc_delimiter)
		free(node->heredoc_delimiter);
	node->heredoc_delimiter = ft_strdup(parser->current->value);
}

void	parse_redir(t_parser *parser, t_ast_node *node)
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


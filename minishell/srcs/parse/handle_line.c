#include "../includes/minishell.h"

// initialise lexer
void	init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->i = 0;
}

// Transforme une ligne de commande en liste de tokens
t_token	*tokenize(char *input)
{
	t_lexer	lexer;
	t_token	*tokens;
	t_token	*current;
	t_token	*new_tok;

	init_lexer(&lexer, input);
	tokens = NULL;
	current = NULL;
	while (1)
	{
		new_tok = get_next_token(&lexer);
		if (!new_tok)
			break ;
		if (!tokens)
		{
			tokens = new_tok;
			current = tokens;
		}
		else
		{
			current->next = new_tok;
			current = new_tok;
		}
		if (new_tok->type == TOKEN_EOF)
			break ;
	}
	return (tokens);
}

// Affiche une commande avec ses arguments
static void	print_command_node(t_cmd *node, int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		ft_putstr_fd("  ", 1);
		i++;
	}
	ft_putstr_fd("COMMAND: ", 1);
	if (node->args && node->args[0])
	{
		i = 0;
		while (node->args[i])
		{
			ft_putstr_fd("'", 1);
			ft_putstr_fd(node->args[i], 1);
			ft_putstr_fd("' ", 1);
			i++;
		}
	}
	ft_putstr_fd("\n", 1);
}

// Affiche les redirection d'une boucle
static void	print_redirections(t_cmd *node, int depth)
{
	int	i;

	if (node->infile)
	{
		i = 0;
		while (i < depth)
		{
			ft_putstr_fd("  ", 1);
			i++;
		}
		ft_putstr_fd("INPUT: ", 1);
		ft_putstr_fd(node->infile, 1);
		ft_putstr_fd("\n", 1);
	}
	if (node->outfile)
	{
		i = 0;
		while (i < depth)
		{
			ft_putstr_fd("  ", 1);
			i++;
		}
		ft_putstr_fd("OUTPUT: ", 1);
		ft_putstr_fd(node->outfile, 1);
		if (node->append)
			ft_putstr_fd(" (append)", 1);
		ft_putstr_fd("\n", 1);
	}
	if (node->heredoc)
	{
		i = 0;
		while (i < depth)
		{
			ft_putstr_fd("  ", 1);
			i++;
		}
		ft_putstr_fd("HEREDOC: ", 1);
		ft_putstr_fd(node->heredoc, 1);
		ft_putstr_fd("\n", 1);
	}
}

// Affiche de facon recursive les synthaxes
void	print_ast(t_cmd *node, int depth)
{
	int	i;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		print_command_node(node, depth);
		print_redirections(node, depth);
	}
	else if (node->type == NODE_PIPELINE)
	{
		i = 0;
		while (i < depth)
		{
			ft_putstr_fd("  ", 1);
			i++;
		}
		ft_putstr_fd("PIPELINE:\n", 1);
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
}

// Traite la ligne de commande complète
void	handle_line(char *line, char ***envp)
{
	t_token		*tokens;
	t_cmd	*ast;

	if (!line || !*line)
		return ;
	tokens = tokenize(line);
	if (!tokens)
	{
		ft_putstr_fd("Erreur lors de la tokenisation\n", 2);
		return ;
	}
	ast = parse(tokens);
	if (!ast)
	{
		ft_putstr_fd("Erreur lors du parsing\n", 2);
		free_tokens(tokens);
		return ;
	}

	execute_all(ast, envp);

	free_tokens(tokens);
}
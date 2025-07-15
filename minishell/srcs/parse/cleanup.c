#include "../includes/minishell.h"

// Libère les ordres de redirections - VERSION CORRIGÉE
void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		// Libérer le champ file de la structure t_redir
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

// Libère la mémoire allouée par les tokens
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

// Libère les arguments
void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

// Libère l'AST de manière récursive
void	free_ast(t_cmd *node)
{
	if (!node)
		return ;
	if (node->args)
		free_args(node->args);
	if (node->infile)
		free(node->infile);
	if (node->outfile)
		free(node->outfile);
	if (node->heredoc)
		free(node->heredoc);
	free_ast(node->left);
	free_ast(node->right);
	free_ast(node->next);
	free(node);
}

// Libère un tableau de chaînes (déjà correcte)
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// Nettoyage complet en cas d'erreur
void	cleanup_all(t_token *tokens, t_cmd *ast, char **env_copy)
{
	if (tokens)
		free_tokens(tokens);
	if (ast)
		free_ast(ast);
	if (env_copy)
		free_array(env_copy);
}

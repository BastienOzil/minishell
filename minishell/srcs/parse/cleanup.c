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

// Fonction pour libérer les tokens
void free_tokens(t_token *tokens)
{
    t_token *current = tokens;
    t_token *next;
    
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

// Libérer l'AST
void free_ast(t_cmd *ast)
{
    if (!ast)
        return;
    if (ast->args)
    {
        int i = 0;
        while (ast->args[i])
        {
            free(ast->args[i]);
            i++;
        }
        free(ast->args);
    }
    if (ast->infile)
        free(ast->infile);
    if (ast->outfile)
        free(ast->outfile);
    if (ast->heredoc)
        free(ast->heredoc);
    if (ast->left)
        free_ast(ast->left);
    if (ast->right)
        free_ast(ast->right);
    if (ast->next)
        free_ast(ast->next);
    free(ast);
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

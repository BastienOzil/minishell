#include "../includes/minishell.h"

// libère les ordres de redirections
void free_redir(t_redir *redir)
{
	t_redir *tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp);
	}
}

// libère la memoire alloué par les tokens
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

// libère les arguments
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

// libère les redirections
void	free_ast(t_cmd *node)
{
	if (!node)
		return ;
	if (node->args)
		free_args(node->args);
	if (node->input_file)
		free(node->input_file);
	if (node->output_file)
		free(node->output_file);
	if (node->heredoc_delimiter)
		free(node->heredoc_delimiter);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

// libère un tableau de chaînes 
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

#include "../includes/minishell.h"

// permet de voir dans le terminal quel type des token est l'argument passé en paramètre
void	print_token(t_token *token)
{
	char	*types[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND",
			"HEREDOC", "EOF"};

	printf("Type: %s", types[token->type]);
	if (token->value)
		printf(", Value: '%s'", token->value);
	printf("\n");
}

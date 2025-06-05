#include "../includes/minishell.h"

// boucle de token
void	handle_tokens(t_lexer *lexer)
{
	t_token	*token;

	while (1)
	{
		token = get_next_token(lexer);
		print_token(token);
		if (token->type == TOKEN_EOF)
		{
			free_tokens(token);
			break ;
		}
		free_tokens(token);
	}
}

// traitement de la ligne
void	handle_line(char *line)
{
	t_lexer	lexer;

	lexer.input = line;
	lexer.i = 0;
	handle_tokens(&lexer);
}


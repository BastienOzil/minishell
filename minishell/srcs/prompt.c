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

// l'ancien main sous forme de fonction
void	ft_line(void)
{
	char *line;

	while (1)
	{
		line = readline("\001\033[1;36m\002Ghost_in_the_minishell$ \001\033[0m\002");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		handle_line(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}

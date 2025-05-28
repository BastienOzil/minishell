#include "../includes/minishell.h"

void	print_token(t_token *token)
{
	char	*types[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND",
			"HEREDOC", "EOF"};

	printf("Type: %s", types[token->type]);
	if (token->value)
		printf(", Value: '%s'", token->value);
	printf("\n");
}

int	main(void)
{
	char	*line;
	t_lexer	lexer;
	t_token	*token;

	while (1)
	{
		line = readline("\001\033[1;36m\002Ghost_in_the_minishell$ \001\033[0m\002");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		lexer.input = line;
		lexer.i = 0;
		while (1)
		{
			token = get_next_token(&lexer);
			print_token(token);
			if (token->type == TOKEN_EOF)
			{
				free_tokens(token);
				break ;
			}
			free_tokens(token);
		}
		free(line);
	}
	printf("exit\n");
	return (0);
}

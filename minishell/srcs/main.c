#include "../includes/minishell.h"

void	print_token(t_token *token)
{
	char	*types[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC", "EOF"};

	printf("Type: %s", types[token->type]);
	if (token->value)
		printf(", Value: '%s'", token->value);
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	t_lexer	lexer;
	t_token	*token;
	char	input[] = "ls -la | grep test > output.txt << EOF";

	(void)ac;
	(void)av;
	(void)env;
	printf("Input: %s\n\n", input);
	lexer.input = input;
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
	return (0);
}

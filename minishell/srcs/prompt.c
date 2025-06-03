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

// ancien main de bastien
void	ft_run_interactive(char **envp)
{
	char	*line;

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
}

// ancien main d'aurelia
void	ft_run_tests(char **envp)
{
	t_cmd	cmd;

	cmd.argv = ft_split("/bin/ls -l", ' ');
	cmd.infile = NULL;
	cmd.outfile = NULL;
	cmd.append = 0;
	cmd.next = NULL;
	execute_cmd(&cmd, envp);
	free_array(cmd.argv);
	cmd.argv = ft_split("/bin/echo Hello world", ' ');
	execute_cmd(&cmd, envp);
	free_array(cmd.argv);
}

#include "includes/minishell.h"

int g_exit_status = 0;

void init_readline(void)
{
   rl_bind_key('\t', rl_insert);
}

int main(int argc, char **argv, char **envp)
{
	char *line;
	(void)argc;
	(void)argv;

	init_readline();

	while (1)
	{
		char *prompt = "\001\033[1;32m\002[Puppet~master]> \001\033[0m\002";

		line = readline(prompt);

		if (!line)
			break;
		if (*line)
			add_history(line);
		handle_line(line, envp);
		free(line);
	}
	printf("exit\n");
	return (0);
}

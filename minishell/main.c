/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:14:44 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 13:22:33 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			g_exit_status = 0;

void	init_readline(void)
{
	rl_bind_key('\t', rl_insert);
}

static void	run_minishell(char **my_env)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = "\001\033[1;32m\002[Puppet~master]> \001\033[0m\002";
		setup_signals_interactive();
		line = readline(prompt);
		if (!line)
		{
			write(1, "exit\n", 5);
			free_array(my_env);
			exit(g_exit_status);
		}
		if (*line)
			add_history(line);
		handle_line(line, &my_env);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**my_env;

	(void)argc;
	(void)argv;
	my_env = dup_env(envp);
	if (!my_env)
	{
		perror("minishell: dup_env failed");
		exit(EXIT_FAILURE);
	}
	run_minishell(my_env);
	free_array(my_env);
	printf("exit\n");
	return (0);
}

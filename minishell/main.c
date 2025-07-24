/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:14:44 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:14:46 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		g_exit_status = 0;

void	init_readline(void)
{
	rl_bind_key('\t', rl_insert);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**my_env;
	char	*prompt;

	(void)argc;
	(void)argv;
	// launch_animation(); // effet initial
	my_env = dup_env(envp); // Copie sécurisée de l'environnement
	if (!my_env)
	{
		perror("minishell: dup_env failed");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		// crée une string colorée pour readline
		prompt = "\001\033[1;32m\002[Puppet~master]> \001\033[0m\002";
		// slow_type_prompt(prompt);
		setup_signals_interactive();
		line = readline(prompt);
		// int fd = open("fichier_qui_nexiste_pas.txt", O_RDONLY);
		// if (fd < 0)
		// 	puppetmaster_perror("open");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		handle_line(line, &my_env);
		free(line);
	}
	printf("exit\n");
	return (0);
}

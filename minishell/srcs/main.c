#include "../includes/minishell.h"

int	main(void)
{
	char	*line;

	launch_animation();

	while (1)
	{
		write(1, "\033[1;32m", 7);
		slow_type_prompt("[Puppet~master]> ");
		write(1, "\033[0m", 4);

		line = readline(""); 

        int fd = open("fichier_qui_nexiste_pas.txt", O_RDONLY);
    	if (fd < 0)
    	    puppetmaster_perror("open");

		if (!line)
			break;
		if (*line)
			add_history(line);
		handle_line(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}





// int    main(void)
// {
//     char    *line;

//     launch_animation(); 

//     while (1)
//     {
//         line = readline("\001\033[1;36m\002Ghost_in_the_minishell$ \001\033[0m\002");

//         if (!line)
//             break ;
//         if (*line)
//             add_history(line);
//         handle_line(line);
//         free(line);
//     }
//     printf("exit\n");
//     return (0);
// }

// aurelia's main
// int	main(int ac, char **av, char **envp)
// {
// 	t_cmd	cmd;

// 	(void)ac;
// 	(void)av;

// 	cmd.argv = ft_split("/bin/ls -l", ' ');
// 	cmd.infile = NULL;
// 	cmd.outfile = NULL;
// 	cmd.append = 0;
// 	cmd.next = NULL;
// 	execute_cmd(&cmd, envp);
// 	free_array(cmd.argv); // à écrire si tu ne l’as pas

// 	cmd.argv = ft_split("/bin/echo Hello world", ' ');
// 	execute_cmd(&cmd, envp);
// 	free_array(cmd.argv);

// 	return (0);
// }


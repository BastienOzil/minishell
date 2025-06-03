#include "../includes/minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	if (ac > 1)
// 		ft_run_tests(envp);
// 	else
// 		ft_run_interactive(envp);
// 	return (0);
// }

int    main(void)
{
    char    *line;

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
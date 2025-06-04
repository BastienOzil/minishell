#include "../includes/minishell.h"

//_________________________________________________________________________________
//main qui lance l'animation
// int	main(void)
// {
// 	char	*line;

// 	launch_animation();

// 	while (1)
// 	{
// 		write(1, "\033[1;32m", 7);
// 		slow_type_prompt("[Puppet~master]> ");
// 		write(1, "\033[0m", 4);

// 		line = readline(""); 

//         int fd = open("fichier_qui_nexiste_pas.txt", O_RDONLY);
//     	if (fd < 0)
//     	    puppetmaster_perror("open");

// 		if (!line)
// 			break;
// 		if (*line)
// 			add_history(line);
// 		handle_line(line);
// 		free(line);
// 	}
// 	printf("exit\n");
// 	return (0);
// }
//_________________________________________________________________________________


// Commande équivalente : echo "hello" > test_output.txt
void	test_output_redirection(char **envp)
{
	t_cmd	cmd;
	char	*args[] = {"/bin/echo", "hello", NULL};

	cmd.argv = args;
	cmd.outfile = "test_output.txt";
	cmd.infile = NULL;
	cmd.append = 0;
	cmd.next = NULL;

	execute_cmd(&cmd, envp);
}

// Commande équivalente : cat < test_input.txt
void	test_input_redirection(char **envp)
{
	t_cmd	cmd;
	char	*args[] = {"/bin/cat", NULL};

	cmd.argv = args;
	cmd.infile = "test_input.txt";
	cmd.outfile = NULL;
	cmd.append = 0;
	cmd.next = NULL;

	execute_cmd(&cmd, envp);
}

// Commande équivalente : echo "append" >> test_output.txt
void	test_append_redirection(char **envp)
{
	t_cmd	cmd;
	char	*args[] = {"/bin/echo", "append", NULL};

	cmd.argv = args;
	cmd.outfile = "test.txt";
	cmd.infile = NULL;
	cmd.append = 1;
	cmd.next = NULL;

	execute_cmd(&cmd, envp);
}

// Commande équivalente : cat << EOF
void	test_heredoc_redirection(char **envp)
{
	t_cmd	cmd;
	char	*args[] = {"/bin/cat", NULL};

	cmd.argv = args;
	cmd.infile = NULL;
	cmd.outfile = NULL;
	cmd.append = 0;
	cmd.heredoc = strdup("EOF"); // ou autre délimiteur
	cmd.next = NULL;

	execute_cmd(&cmd, envp);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	// test_output_redirection(envp);
	// test_input_redirection(envp);
	 test_append_redirection(envp);
	// test_heredoc_redirection(envp);

	return (0);
}
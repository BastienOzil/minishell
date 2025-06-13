#include "../includes/minishell.h"
#include "../animation/includes/animation.h"

int	main(void)
{
	char	*line;

	launch_animation(); // effet initial

	while (1)
	{
		// crée une string colorée pour readline
		char *prompt = "\001\033[1;32m\002[Puppet~master]> \001\033[0m\002";

		slow_type_prompt(prompt);

		line = readline(prompt);

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

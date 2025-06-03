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

#include <sys/time.h>
#include <sys/ioctl.h>




#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 300

static int	ft_random_digit(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_usec % 10);
}

static void	move_cursor(int row, int col)
{
	char	buf[32];
	int		len = snprintf(buf, sizeof(buf), "\033[%d;%dH", row, col);
	write(1, buf, len);
}

static void	clear_screen(void)
{
	write(1, "\033[2J", 4);
	move_cursor(1, 1);
}

void	launch_animation(void)
{
	struct winsize w;
	int	i, j, frame;
	char c;
	int intensity[MAX_ROWS][MAX_COLS] = {{0}};
	const char *colors[] = {
		"\033[1;32m", // vert clair
		"\033[0;32m", // vert normal
		"\033[2;32m"  // vert foncé
	};

	char *title = " GHOST IN THE MINISHELL ";
	int title_len = strlen(title);
	int last_letter_index = -1; // pour synchroniser le son

	ioctl(1, TIOCGWINSZ, &w);
	int rows = (w.ws_row < MAX_ROWS) ? w.ws_row : MAX_ROWS;
	int cols = (w.ws_col < MAX_COLS) ? w.ws_col : MAX_COLS;
	int center_row = rows / 2;
	int center_col = (cols - title_len) / 2;

	clear_screen();

	for (frame = 0; frame < 100; frame++)
	{
		int current_index = (frame / 3);
		for (i = 0; i < rows - 1; i++)
		{
			move_cursor(i + 1, 1);
			for (j = 0; j < cols; j++)
			{
				// Titre qui s’écrit progressivement
				if (i == center_row && j >= center_col &&
					j < center_col + current_index && j - center_col < title_len)
				{
					write(1, "\033[0;32m", 7);
					write(1, &title[j - center_col], 1);
					if (j - center_col > last_letter_index)
					{
						write(1, "\a", 1); // bip une seule fois par lettre
						last_letter_index = j - center_col;
					}
					continue;
				}
				// Réserve l’espace du titre à venir
				if (i == center_row && j >= center_col &&
					j < center_col + title_len)
				{
					write(1, " ", 1);
					continue;
				}
				// Dégradé de vert
				if (intensity[i][j] < 2)
					intensity[i][j]++;
				write(1, colors[intensity[i][j]], strlen(colors[intensity[i][j]]));
				c = ft_random_digit() + '0';
				write(1, &c, 1);
			}
		}
		write(1, "\033[0m", 4);
		usleep(50000);
	}
	move_cursor(rows, 1);
	write(1, "\n", 1);
}



int    main(void)
{
    char    *line;

    launch_animation(); 

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
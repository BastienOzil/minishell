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

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 300

// Retourne un chiffre pseudo-aléatoire entre 0 et 9
static int	ft_random_digit(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_usec % 10);
}

// Convertit un entier en chaîne et retourne la longueur écrite
static int	int_to_str(int n, char *str)
{
	int		len = 0;
	int		temp = n;
	char	reverse[10];

	if (n == 0)
	{
		str[0] = '0';
		return (1);
	}
	while (temp > 0)
	{
		reverse[len++] = (temp % 10) + '0';
		temp /= 10;
	}
	for (int i = 0; i < len; i++)
		str[i] = reverse[len - i - 1];
	return (len);
}

// Affiche le curseur à la position (row, col) sans snprintf
static void	move_cursor(int row, int col)
{
	char	buf[32];
	int		i = 0;

	buf[i++] = 27; // \033
	buf[i++] = '[';
	i += int_to_str(row, &buf[i]);
	buf[i++] = ';';
	i += int_to_str(col, &buf[i]);
	buf[i++] = 'H';

	write(1, buf, i);
}

// Vide l'écran
static void	clear_screen(void)
{
	write(1, "\033[2J", 4);
	move_cursor(1, 1);
}

void	slow_type_line_at(int row, int col, const char *str)
{
	move_cursor(row, col);
	while (*str)
	{
		write(1, str, 1);
		usleep(20000); // 20ms par lettre
		str++;
	}
}




//Affiche l'animation
void	launch_animation(void)
{
	struct winsize w;
	int	i, j, frame;
	char c;
	int intensity[MAX_ROWS][MAX_COLS] = {{0}};
	const char *colors[] = {
		"\033[1;32m", // vert clair
		"\033[0;32m", // vert normal
		"\033[2;32m"  // vert foncé (optionnel)
	};

	char *title = " GHOST IN THE MINISHELL ";
	int title_len = strlen(title);
	int last_letter_index = -1;

	ioctl(1, TIOCGWINSZ, &w);
	int rows = (w.ws_row < MAX_ROWS) ? w.ws_row : MAX_ROWS;
	int cols = (w.ws_col < MAX_COLS) ? w.ws_col : MAX_COLS;
	int center_row = rows / 2;
	int center_col = (cols - title_len) / 2;

	clear_screen();

	for (frame = 0; frame < 100; frame++)
	{
		int current_index = frame / 3;
		for (i = 0; i < rows - 1; i++)
		{
			move_cursor(i + 1, 1);
			for (j = 0; j < cols; j++)
			{
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
				if (i == center_row && j >= center_col &&
					j < center_col + title_len)
				{
					write(1, " ", 1);
					continue;
				}
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



// void	show_intro_prompt_effect(void)
// {
// 	move_cursor(1, 1);
// 	write(1, "\033[2J", 4);
// 	usleep(80000);
// 	write(1, "\033[1;30m#\033[0m", 9);
// 	usleep(80000);
// 	write(1, "\033[1;37m.\033[0m", 9);
// 	usleep(80000);
// 	write(1, "\033[0;32m_\033[0m", 9);
// 	usleep(100000);
// 	write(1, "\n", 1); // aller à la ligne pour readline
// }

void	slow_type_prompt(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
        write(1, "\a", 1);
		//fflush(stdout);
		usleep(60000); // ajuster la vitesse ici (en microsecondes)
		str++;
	}
}

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

       
#include "../includes/minishell.h"

#define MAX_ROWS 100
#define MAX_COLS 300

/* Retourne un chiffre pseudo-aléatoire entre 0 et 9 */
int	ft_random_digit(void)
{
	struct timeval	 tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec % 10);
}

/* Convertit un entier en chaîne de caractères et retourne la longueur écrite */
int	int_to_str(int n, char *str)
{
	int		len;
	int		temp;
	char	reverse[10];
	int		i;

	len = 0;
	temp = n;
	if (n == 0)
	{
		str[0] = '0';
		return (1);
	}
	while (temp > 0)
	{
		reverse[len] = (temp % 10) + '0';
		temp /= 10;
		len++;
	}
	i = 0;
	while (i < len)
	{
		str[i] = reverse[len - i - 1];
		i++;
	}
	return (len);
}

/* Déplace le curseur à la position (row, col) dans le terminal */
void	move_cursor(int row, int col)
{
	char	buf[32];
	int		i;

	i = 0;
	buf[i++] = 27;
	buf[i++] = '[';
	i += int_to_str(row, &buf[i]);
	buf[i++] = ';';
	i += int_to_str(col, &buf[i]);
	buf[i++] = 'H';
	write(1, buf, i);
}

/* Efface l'écran du terminal */
void	clear_screen(void)
{
	write(1, "\033[2J", 4);
	move_cursor(1, 1);
}

/* Affiche une ligne avec un effet de frappe lente à la position spécifiée */
void	slow_type_line_at(int row, int col, const char *str)
{
	move_cursor(row, col);
	while (*str)
	{
		write(1, str, 1);
		usleep(20000);
		str++;
	}
}

/* Lance l'animation principale avec des chiffres en cascade et le titre central */
void	launch_animation(void)
{
	struct winsize	w;
	int			rows;
	int			cols;
	int			center_row;
	int			center_col;
	int			frame;
	int			i;
	int			j;
	char		c;
	int			intensity[MAX_ROWS][MAX_COLS] = {{0}};
	const char	*colors[] = {
		"\033[1;32m",
		"\033[0;32m",
		"\033[2;32m"
	};
	char		*title = " GHOST IN THE MINISHELL ";
	int			title_len = strlen(title);
	int			last_letter_index = -1;

	ioctl(1, TIOCGWINSZ, &w);
	rows = (w.ws_row < MAX_ROWS) ? w.ws_row : MAX_ROWS;
	cols = (w.ws_col < MAX_COLS) ? w.ws_col : MAX_COLS;
	center_row = rows / 2;
	center_col = (cols - title_len) / 2;
	clear_screen();
	frame = 0;
	while (frame < 100)
	{
		int current_index = frame / 3;
		i = 0;
		while (i < rows - 1)
		{
			move_cursor(i + 1, 1);
			j = 0;
			while (j < cols)
			{
				if (i == center_row && j >= center_col &&
					j < center_col + current_index && j - center_col < title_len)
				{
					write(1, "\033[0;32m", 7);
					write(1, &title[j - center_col], 1);
					if (j - center_col > last_letter_index)
					{
						write(1, "\a", 1);
						last_letter_index = j - center_col;
					}
				}
				else if (i == center_row && j >= center_col &&
					j < center_col + title_len)
					write(1, " ", 1);
				else
				{
					if (intensity[i][j] < 2)
						intensity[i][j]++;
					write(1, colors[intensity[i][j]], strlen(colors[intensity[i][j]]));
					c = ft_random_digit() + '0';
					write(1, &c, 1);
				}
				j++;
			}
			i++;
		}
		write(1, "\033[0m", 4);
		usleep(20000);
		frame++;
	}
	move_cursor(rows, 1);
	write(1, "\n", 1);
	write(1, "\033[2J\033[H", 7);
}

/* Affiche le prompt avec effet de frappe lente */
void	slow_type_prompt(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		write(1, "\a", 1);
		usleep(30000);
		str++;
	}
}

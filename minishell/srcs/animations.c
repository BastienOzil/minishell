#include "../includes/minishell.h"

#define MAX_ROWS 100
#define MAX_COLS 300

int	ft_random_digit(void)
{
	struct timeval	 tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec % 10);
}

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

void	clear_screen(void)
{
	write(1, "\033[2J", 4);
	move_cursor(1, 1);
}

void	launch_animation(void)
{
	struct winsize	w;
	char			screen[MAX_ROWS][MAX_COLS];
	int			rows;
	int			cols;
	const char	*title = "GHOST IN THE MINISHELL";
	int			title_len;
	int			frame;
	int			max_frames;
	int			fast_forward_frame;
	int			title_done_frame;
	int			post_title_wait;
	int			last_sound_index;
	int			i;
	int			j;

	title_len = strlen(title);
	srand(time(NULL));
	ioctl(1, TIOCGWINSZ, &w);
	rows = (w.ws_row < MAX_ROWS) ? w.ws_row : MAX_ROWS;
	cols = (w.ws_col < MAX_COLS) ? w.ws_col : MAX_COLS;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			screen[i][j] = '0' + ft_random_digit();
	frame = 0;
	max_frames = 200;
	fast_forward_frame = 160;
	title_done_frame = (int)(title_len * 3.2);
	post_title_wait = 0;
	last_sound_index = -1;
	while (frame < max_frames)
	{
		clear_screen();
		if (frame > title_done_frame)
			post_title_wait++;
		if (post_title_wait > 10)
			break;
		for (i = 0; i < rows; i++)
		{
			move_cursor(i + 1, 1);
			for (j = 0; j < cols; j++)
			{
				if ((rand() % 1000) < ((float)frame / max_frames * 1000))
					screen[i][j] = ' ';
				if (i == rows / 2 && j >= (cols - title_len) / 2
					&& j < (cols + title_len) / 2)
				{
					int ti = j - (cols - title_len) / 2;
					if (frame > (ti * 3))
					{
						write(1, "\033[1;92m", 7);
						write(1, &title[ti], 1);
						write(1, "\033[0m", 4);
						if (ti > last_sound_index)
						{
							write(1, "\a", 1);
							usleep(5000);
							last_sound_index = ti;
						}
						continue ;
					}
				}
				write(1, "\033[1;92m", 7);
				write(1, &screen[i][j], 1);
				write(1, "\033[0m", 4);
				if (screen[i][j] != ' ')
					screen[i][j] = '0' + ft_random_digit();
			}
		}
		usleep((frame > fast_forward_frame) ? 10000 : 30000);
		frame++;
	}
	clear_screen();
	move_cursor(rows / 2, (cols - title_len) / 2);
	write(1, "\033[1;92m", 7);
	write(1, title, title_len);
	write(1, "\033[0m\n", 5);
	clear_screen();
}

void	slow_type_prompt(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		write(1, "\a", 1);
		usleep(20000);
		str++;
	}
}

#include "../includes/animation.h"

int	display_title_char(const char *title, int frame, int i, int j, int *last_sound_index)
{
	int	title_len;
	int	rows;
	int	cols;
	int	ti;

	title_len = strlen(title);
	get_terminal_size(&rows, &cols);
	if (i == rows / 2 && j >= (cols - title_len) / 2 
		&& j < (cols + title_len) / 2)
	{
		ti = j - (cols - title_len) / 2;
		if (should_display_title_char(frame, ti))
		{
			write(1, "\033[1;92m", 7);
			write(1, &title[ti], 1);
			write(1, "\033[0m", 4);
			check_title_sound(ti, last_sound_index);
			return (1);
		}
	}
	return (0);
}

int	should_display_title_char(int frame, int ti)
{
	return (frame > (ti * 3));
}

void	check_title_sound(int ti, int *last_sound_index)
{
	if (ti > *last_sound_index)
	{
		write(1, "\a", 1);
		usleep(5000);
		*last_sound_index = ti;
	}
}

void	display_final_title(const char *title)
{
	int	rows;
	int	cols;
	int	title_len;

	title_len = strlen(title);
	get_terminal_size(&rows, &cols);
	clear_screen();
	move_cursor(rows / 2, (cols - title_len) / 2);
	write(1, "\033[1;92m", 7);
	write(1, title, title_len);
	write(1, "\033[0m\n", 5);
	clear_screen();
}

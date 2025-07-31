/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:45:09 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 12:32:53 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/animation.h"

size_t	anim_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	display_title_char(t_animation animation)
{
	animation.title_len = anim_strlen(animation.title);
	get_terminal_size(&animation.rows, &animation.cols);
	if (animation.i == animation.rows / 2 && animation.j >= (animation.cols
			- animation.title_len) / 2 && animation.j < (animation.cols
			+ animation.title_len) / 2)
	{
		animation.ti = animation.j - (animation.cols - animation.title_len) / 2;
		if (should_display_title_char(animation.frame, animation.ti))
		{
			write(1, "\033[1;92m", 7);
			write(1, &animation.title[animation.ti], 1);
			write(1, "\033[0m", 4);
			check_title_sound(animation.ti, &animation.last_sound_index);
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

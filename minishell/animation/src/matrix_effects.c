/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:00:49 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 15:00:51 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/animation.h"

int	ft_random_digit(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec % 10);
}

void	init_screen_matrix(char screen[MAX_ROWS][MAX_COLS], int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			screen[i][j] = '0' + ft_random_digit();
			j++;
		}
		i++;
	}
}

void	update_matrix_char(char *c)
{
	if (*c != ' ')
		*c = '0' + ft_random_digit();
}

void	draw_matrix_char(char c, int should_fade, int frame, int max_frames)
{
	if (should_fade && (rand() % 300) < ((float)frame / max_frames * 1000))
		c = ' ';
	write(1, "\033[1;92m", 7);
	write(1, &c, 1);
	write(1, "\033[0m", 4);
}

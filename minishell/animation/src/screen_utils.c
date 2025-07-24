/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:01:00 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 15:01:02 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/animation.h"

void	clear_screen(void)
{
	write(1, "\033[2J", 4);
	move_cursor(1, 1);
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

void	get_terminal_size(int *rows, int *cols)
{
	struct winsize	w;

	ioctl(1, TIOCGWINSZ, &w);
	*rows = (w.ws_row < MAX_ROWS) ? w.ws_row : MAX_ROWS;
	*cols = (w.ws_col < MAX_COLS) ? w.ws_col : MAX_COLS;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vanish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:11:00 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 10:01:44 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void vanish_effect(char *temp, const char *ref)
{
	int step;
	int len;
	int total;
	int prefix_len;
	int l;
	int r;

	len = strlen(ref);
	total = strlen(temp);
	prefix_len = strlen("\033[38;5;208m[?] ");
	step = 0;
	while (step <= len / 2)
	{
		l = prefix_len + step;
		r = prefix_len + len - step - 1;
		vanish_blank(temp, l, r);
		vanish_write(temp, total);
		step++;
	}
	vanish_write("", 0);
}

void vanish_blank(char *temp, int l, int r)
{
	if (l < r)
	{
		temp[l] = ' ';
		temp[r] = ' ';
	}
	else if (l == r)
		temp[l] = ' ';
}

void vanish_write(const char *str, int len)
{
	const char *clear = "\033[K";
	const char *carriage = "\r";

	write(2, clear, strlen(clear));
	if (len > 0)
		write(2, str, len);
	write(2, carriage, strlen(carriage));
	usleep(10000);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vanish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:11:00 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 17:02:31 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	vanish_effect(char *temp, const char *ref)
{
	t_vanish	vanish;

	vanish.len = ft_strlen(ref);
	vanish.total = ft_strlen(temp);
	vanish.prefix_len = ft_strlen("\033[38;5;208m[?] ");
	vanish.step = 0;
	while (vanish.step <= vanish.len / 2)
	{
		vanish.l = vanish.prefix_len + vanish.step;
		vanish.r = vanish.prefix_len + vanish.len - vanish.step - 1;
		vanish_blank(temp, vanish.l, vanish.r);
		vanish_write(temp, vanish.total);
		vanish.step++;
	}
	vanish_write("", 0);
}

void	vanish_blank(char *temp, int l, int r)
{
	if (l < r)
	{
		temp[l] = ' ';
		temp[r] = ' ';
	}
	else if (l == r)
		temp[l] = ' ';
}

void	vanish_write(const char *str, int len)
{
	const char	*clear = "\033[K";
	const char	*carriage = "\r";

	write(2, clear, strlen(clear));
	if (len > 0)
		write(2, str, len);
	write(2, carriage, strlen(carriage));
	usleep(10000);
}

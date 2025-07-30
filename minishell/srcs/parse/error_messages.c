/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:44:31 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 16:31:52 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_random_index(int max)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec % max);
}

static void	display_blinking_message(const char *quote)
{
	const char	*prefix = "\033[38;5;208m[?] ";
	const char	*reset = "\033[0m";
	const char	*clear = "\033[K";
	const char	*carriage = "\r";
	int			j;
	int			len;

	j = 0;
	len = strlen(quote);
	while (j < 100)
	{
		write(2, clear, strlen(clear));
		usleep(200);
		write(2, prefix, strlen(prefix));
		write(2, quote, len);
		write(2, reset, strlen(reset));
		write(2, carriage, strlen(carriage));
		usleep(10000);
		j++;
	}
}

void	print_loop(const char *quote)
{
	display_blinking_message(quote);
}

void	puppetmaster_perror(const char *context)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("[Puppet~master]> ", 2);
		ft_putstr_fd((char *)context, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		perror(context);
}

void	format_line(char *dst, const char *quote)
{
	const char	*prefix = "\033[38;5;208m[?] ";
	const char	*reset = "\033[0m";

	snprintf(dst, 512, "%s%s%s", prefix, quote, reset);
}

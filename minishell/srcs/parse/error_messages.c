/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:44:31 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 17:48:51 by bozil            ###   ########.fr       */
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
	t_error	error;
	int		i;
	int		len;

	error.prefix = "\033[38;5;208m[?] ";
	error.reset = "\033[0m";
	error.clear = "\033[K";
	error.carriage = "\r";
	len = 0;
	i = 0;
	len = ft_strlen(quote);
	while (i < 100)
	{
		write(2, error.clear, ft_strlen(error.clear));
		usleep(200);
		write(2, error.prefix, ft_strlen(error.prefix));
		write(2, quote, len);
		write(2, error.reset, ft_strlen(error.reset));
		write(2, error.carriage, ft_strlen(error.carriage));
		usleep(10000);
		i++;
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

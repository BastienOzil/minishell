/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:44:31 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 12:24:24 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// valeur numérique aleatoire
int	get_random_index(int max)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec % max);
}

// Affiche le message avec effet de clignotement
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

// fait clignoter l'erreur
void	print_loop(const char *quote)
{
	display_blinking_message(quote);
}

// void	puppetmaster_perror(const char *context)
// {
// 	int		i;
// 	char	temp[512];
// 	char	line[512];

// 	const char *quotes[] = {
// 		"\"Your effort to remain what you are is what limits you.\"",
// 		"\"Who can gaze into the mirror without becoming evil?\"",
// 		"\"All things change in a dynamic environment.\"",
// 	};
// 	i = get_random_index(sizeof(quotes) / sizeof(quotes[0]));
// 	if (errno == ENOENT)
// 	{
// 		ft_putstr_fd("\033[38;5;208m[Puppet~master]> ", 2);
// 		ft_putstr_fd((char *)context, 2);
// 		ft_putstr_fd(": command not found\n\033[0m", 2);
// 	}
// 	else
// 	{
// 		perror(context);
// 	}
// 	print_loop(quotes[i]);
// 	format_line(line, quotes[i]);
// 	ft_strlcpy(temp, line, sizeof(temp));
// 	vanish_effect(temp, line);
// }


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

// les caractères devienent orange
void	format_line(char *dst, const char *quote)
{
	const char	*prefix = "\033[38;5;208m[?] ";
	const char	*reset = "\033[0m";

	snprintf(dst, 512, "%s%s%s", prefix, quote, reset);
}

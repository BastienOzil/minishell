/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:44:31 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 18:09:48 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_random_index(int max)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec % max);
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

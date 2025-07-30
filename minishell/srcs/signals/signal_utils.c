/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:12:41 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 15:11:18 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal_exit_status(int sig)
{
	if (sig == SIGINT)
		g_exit_status = SIGINT_CODE;
	else if (sig == SIGQUIT)
		g_exit_status = SIGQUIT_CODE;
}

int	signal_to_exit_code(int sig)
{
	if (sig)
	{
		if (sig == SIGINT)
			return (SIGINT_CODE);
		else if (sig == SIGQUIT)
			return (SIGQUIT_CODE);
		else
			return (sig + 128);
	}
	return (0);
}

void	reset_signal_state(void)
{
	g_exit_status = 0;
}

int	signal_pending(void)
{
	return (g_exit_status != 0);
}

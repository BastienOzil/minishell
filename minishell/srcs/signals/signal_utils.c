/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:12:41 by bozil             #+#    #+#             */
/*   Updated: 2025/07/29 11:36:14 by bozil            ###   ########.fr       */
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
	switch (sig)
	{
	case SIGINT:
		return (SIGINT_CODE);
	case SIGQUIT:
		return (SIGQUIT_CODE);
	default:
		return (sig + 128);
	}
}

void	reset_signal_state(void)
{
	g_exit_status = 0;
}

int	signal_pending(void)
{
	return (g_exit_status != 0);
}

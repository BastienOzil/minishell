/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:12:41 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 10:14:23 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Gère le statut de sortie en fonction du signal reçu
void	handle_signal_exit_status(int sig)
{
	if (sig == SIGINT)
		g_exit_status = SIGINT_CODE;
	else if (sig == SIGQUIT)
		g_exit_status = SIGQUIT_CODE;
}

// Convertit un signal en code de sortie
int	signal_to_exit_code(int sig)
{
	switch (sig)
	{
	case SIGINT:
		return (SIGINT_CODE);
	case SIGQUIT:
		return (SIGQUIT_CODE);
	default:
		return (sig + 128); // 128 pour la convention Unix
	}
}

// Remet à zéro l'état des signaux
void	reset_signal_state(void)
{
	g_exit_status = 0;
}

// Vérifie si un signal a été reçu
int	signal_pending(void)
{
	return (g_exit_status != 0);
}

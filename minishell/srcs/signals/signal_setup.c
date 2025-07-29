/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:11:41 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:12:35 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Configure les signaux
void	setup_signals_interactive(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// Configure les signaux pour le mode non-interactif
void	setup_signals_non_interactive(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// Configure les signaux pour le heredoc
void	setup_signals_heredoc(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

// Configure les signaux pour les processus enfants
void	setup_signals_child(void)
{
	signal(SIGINT, sigint_child_handler);
	signal(SIGQUIT, sigquit_child_handler);
}


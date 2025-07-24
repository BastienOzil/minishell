/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:11:26 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:11:29 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

// SIGINT (Ctrl+C) en mode interactif
void	sigint_handler(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	g_exit_status = SIGINT_CODE;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// SIGQUIT (Ctrl+\) en mode interactif
void	sigquit_handler(int sig)
{
	(void)sig;
}

// SIGINT pendant un heredoc
void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	g_exit_status = SIGINT_CODE;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

// SIGINT enfant
void	sigint_child_handler(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	exit(SIGINT_CODE);
}

// Handler pour SIGQUIT enfant
void	sigquit_child_handler(int sig)
{
	(void)sig;
	g_signal_received = SIGQUIT;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	exit(SIGQUIT_CODE);
}

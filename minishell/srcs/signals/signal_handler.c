/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:11:26 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 22:22:35 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = SIGINT_CODE;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_exit_status = SIGINT_CODE;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

void	sigint_child_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(SIGINT_CODE);
}

void	sigquit_child_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	exit(SIGQUIT_CODE);
}

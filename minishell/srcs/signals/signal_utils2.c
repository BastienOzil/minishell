/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:13:16 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:13:46 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Attend qu'un processus enfant se termine et gère les signaux
int	wait_for_child(pid_t pid)
{
	int	status;
	int	result;
	int	sig;

	result = waitpid(pid, &status, 0);
	if (result == -1)
		return (-1);
	// Si le processus s'est terminé normalement
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	// Si le processus s'est terminé par un signal
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		// Afficher newline pour SIGINT seulement
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		// Afficher message pour SIGQUIT
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		return (signal_to_exit_code(sig));
	}
	return (EXIT_FAILURE);
}

// Vérifie si le processus actuel doit être interrompu
int	should_interrupt(void)
{
	return (g_signal_received == SIGINT);
}

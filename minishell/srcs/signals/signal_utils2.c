/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:13:16 by bozil             #+#    #+#             */
/*   Updated: 2025/07/29 11:36:30 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_for_child(pid_t pid)
{
	int	status;
	int	result;
	int	sig;

	result = waitpid(pid, &status, 0);
	if (result == -1)
		return (-1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		return (signal_to_exit_code(sig));
	}
	return (EXIT_FAILURE);
}

int	should_interrupt(void)
{
	return (g_exit_status == SIGINT_CODE);
}

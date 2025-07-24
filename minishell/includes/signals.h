/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:59:53 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:59:54 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "shared.h"
# include <signal.h>

extern volatile sig_atomic_t	g_signal_received;

// Codes de signaux
# define SIGINT_CODE 130
# define SIGQUIT_CODE 131

// signal_handlers.c
void							sigint_handler(int sig);
void							sigquit_handler(int sig);
void							sigint_heredoc_handler(int sig);
void							sigint_child_handler(int sig);
void							sigquit_child_handler(int sig);

// signal_setup.c
void							setup_signals_interactive(void);
void							setup_signals_non_interactive(void);
void							setup_signals_heredoc(void);
void							setup_signals_child(void);
void							ignore_signals(void);
void							restore_signals(void);

// signal_utils.c
void							handle_signal_exit_status(int sig);
int								signal_to_exit_code(int sig);
void							reset_signal_state(void);

#endif

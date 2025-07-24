#include "../includes/minishell.h"

// Configure les signaux
void setup_signals_interactive(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

// Configure les signaux pour le mode non-interactif
void setup_signals_non_interactive(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

// Configure les signaux pour le heredoc
void setup_signals_heredoc(void)
{
    signal(SIGINT, sigint_heredoc_handler);
    signal(SIGQUIT, SIG_IGN);
}

// Configure les signaux pour les processus enfants
void setup_signals_child(void)
{
    signal(SIGINT, sigint_child_handler);
    signal(SIGQUIT, sigquit_child_handler);
}

// Ignore tous les signaux
void ignore_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}

// Restaure le comportement par défaut des signaux
void restore_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

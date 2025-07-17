#include "../includes/signals.h"
#include <signal.h>

// Gère le statut de sortie en fonction du signal reçu
void handle_signal_exit_status(int sig)
{
    if (sig == SIGINT)
        g_exit_status = SIGINT_CODE;
    else if (sig == SIGQUIT)
        g_exit_status = SIGQUIT_CODE;
}

// Convertit un signal en code de sortie
int signal_to_exit_code(int sig)
{
    switch (sig)
    {
        case SIGINT:
            return SIGINT_CODE;
        case SIGQUIT:
            return SIGQUIT_CODE;
        default:
            return sig + 128; // 128 pour la convention Unix
    }
}

// Remet à zéro l'état des signaux
void reset_signal_state(void)
{
    g_signal_received = 0;
}

// Vérifie si un signal a été reçu
int signal_pending(void)
{
    return (g_signal_received != 0);
}

// Attend qu'un processus enfant se termine et gère les signaux
int wait_for_child(pid_t pid)
{
    int status;
    int result;
    
    result = waitpid(pid, &status, 0);
    
    if (result == -1)
        return -1;
    
    // Si le processus s'est terminé normalement
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    
    // Si le processus s'est terminé par un signal
    if (WIFSIGNALED(status))
    {
        int sig = WTERMSIG(status);
        
        // Afficher newline pour SIGINT seulement
        if (sig == SIGINT)
            write(STDOUT_FILENO, "\n", 1);
        // Afficher message pour SIGQUIT
        else if (sig == SIGQUIT)
            write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
        
        return signal_to_exit_code(sig);
    }
    
    return EXIT_FAILURE;
}

// Vérifie si le processus actuel doit être interrompu
int should_interrupt(void)
{
    return (g_signal_received == SIGINT);
}
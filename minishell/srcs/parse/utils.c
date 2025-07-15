#include "../includes/minishell.h"

// Vérifie si c'est un caractère d'espacement
int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

// Vérifie si c'est un caractère spécial
int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&' || 
            c == '(' || c == ')' || c == '"' || c == '\'' || c == '$');
}



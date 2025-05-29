#include "../includes/minishell.h"

// voie si c'est un espace
int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// voie si c'est un charactère spéciale
int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

#include "../includes/minishell.h"

int	get_random_index(int max)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_usec % max);
}

void	puppetmaster_perror(const char *context)
{
	const char *quotes[] = {
		"\"Your effort to remain what you are is what limits you.\"",
		"\"Who can gaze into the mirror without becoming evil?\"",
		"\"All things change in a dynamic environment.\"",
		"\"I am connected to all parts of the Net.\"",
		"\"There is no individuality without memory.\""
	};
	int i = get_random_index(sizeof(quotes) / sizeof(quotes[0]));

	// Affiche le message système
	perror(context);

	// Affiche une citation stylisée
	write(2, "\033[38;5;208m[?] ", 14); 
	write(2, quotes[i], strlen(quotes[i]));
	write(2, "\033[0m\n", 5);
}
#include "../includes/minishell.h"

// int	get_random_index(int max)
// {
// 	struct timeval	tv;
// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_usec % max);
// }

// void	puppetmaster_perror(const char *context)
// {
// 	const char *quotes[] = {
// 		"\"Your effort to remain what you are is what limits you.\"",
// 		"\"Who can gaze into the mirror without becoming evil?\"",
// 		"\"All things change in a dynamic environment.\"",
// 		"\"I am connected to all parts of the Net.\"",
// 		"\"There is no individuality without memory.\""
// 	};
// 	int i = get_random_index(sizeof(quotes) / sizeof(quotes[0]));

// 	// Affiche le message système
// 	perror(context);

// 	// Affiche une citation stylisée
// 	write(2, "\033[38;5;208m[?] ", 14); 
// 	write(2, quotes[i], strlen(quotes[i]));
// 	write(2, "\033[0m\n", 5);
// }


int get_random_index(int max)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_usec % max);
}


void	puppetmaster_perror(const char *context)
{
	const char	*quotes[] = {
		"\"Your effort to remain what you are is what limits you.\"",
		"\"Who can gaze into the mirror without becoming evil?\"",
		"\"All things change in a dynamic environment.\"",
		"\"I am connected to all parts of the Net.\"",
		"\"There is no individuality without memory.\""
	};
	int			i;
	const char	*prefix;
	const char	*reset;
	const char	*clear;
	const char	*carriage;
	int			len;
	char		quote_line[512];
	char		temp[512];
	int			total_len;
	int			j;
	int			step;
	int			l;
	int			r;

	i = get_random_index(sizeof(quotes) / sizeof(quotes[0]));
	prefix = "\033[38;5;208m[?] ";
	reset = "\033[0m";
	clear = "\033[K";
	carriage = "\r";
	len = strlen(quotes[i]);
	perror(context);

	j = 0;
	while (j < 100)
	{
		write(2, clear, strlen(clear));
		usleep(200);
		write(2, prefix, strlen(prefix));
		write(2, quotes[i], len);
		write(2, reset, strlen(reset));
		write(2, carriage, strlen(carriage));
		usleep(500);
		j++;
	}

	snprintf(quote_line, sizeof(quote_line), "%s%s%s", prefix, quotes[i], reset);
	total_len = strlen(quote_line);
	strcpy(temp, quote_line);
	step = 0;
	while (step <= len / 2)
	{
		l = strlen(prefix) + step;
		r = strlen(prefix) + len - step - 1;
		if (l < r)
		{
			temp[l] = ' ';
			temp[r] = ' ';
		}
		else if (l == r)
			temp[l] = ' ';
		write(2, clear, strlen(clear));
		write(2, temp, total_len);
		write(2, carriage, strlen(carriage));
		usleep(1000);
		step++;
	}
	write(2, clear, strlen(clear));
	write(2, carriage, strlen(carriage));
}

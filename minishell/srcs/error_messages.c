#include "../includes/minishell.h"

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
	char		temp[512];
	char		line[512];

	i = get_random_index(sizeof(quotes) / sizeof(quotes[0]));
	perror(context);
	print_loop(quotes[i]);
	format_line(line, quotes[i]);
	strcpy(temp, line);
	vanish_effect(temp, line);
}

void	print_loop(const char *quote)
{
	const char	*prefix = "\033[38;5;208m[?] ";
	const char	*reset = "\033[0m";
	const char	*clear = "\033[K";
	const char	*carriage = "\r";
	int			j = 0;
	int			len = strlen(quote);

	while (j < 100)
	{
		write(2, clear, strlen(clear));
		usleep(200);
		write(2, prefix, strlen(prefix));void	format_line(char *dst, const char *quote);
		write(2, quote, len);
		write(2, reset, strlen(reset));
		write(2, carriage, strlen(carriage));
		usleep(10000);
		j++;
	}
}

void	format_line(char *dst, const char *quote)
{
	const char	*prefix = "\033[38;5;208m[?] ";
	const char	*reset = "\033[0m";

	snprintf(dst, 512, "%s%s%s", prefix, quote, reset);
}


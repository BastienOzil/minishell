#include "../includes/animation.h"

void	slow_type_prompt(const char *str)
{
	while (*str)
	{
		write(1, str, 1);
		write(1, "\a", 1);
		usleep(10000);
		str++;
	}

	write(1, "\r\033[K", 5);
}

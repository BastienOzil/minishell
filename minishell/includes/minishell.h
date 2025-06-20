#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include "../utils/libft/libft.h"
#include "shared.h"
#include "parse.h"
#include "exec.h"

// utils
int is_special(char c);
int is_space(char c);

//error_messages.c
void	    puppetmaster_perror(const char *context);
int	        get_random_index(int max);

//animations.c
void	slow_type_prompt(const char *str);
void	launch_animation(void);
void	slow_type_line_at(int row, int col, const char *str);
void	clear_screen(void);
void	move_cursor(int row, int col);
int	    int_to_str(int n, char *str);
int	    ft_random_digit(void);


#endif

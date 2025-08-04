/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:39 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 18:51:37 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	parse_options(char **args, int *newline, int *interpret_escapes)
{
	int	i;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		if (ft_strcmp(args[i], "-e") == 0)
		{
			*interpret_escapes = 1;
			i++;
		}
		else if (is_valid_n_option(args[i]))
		{
			*newline = 0;
			i++;
		}
		else
			break ;
	}
	return (i);
}

static void	print_with_escapes(char *arg)
{
	char	*temp;

	temp = ft_strdup(arg);
	if (temp)
	{
		process_escape_sequences(temp);
		write(1, temp, ft_strlen(temp));
		free(temp);
	}
	else
		write(1, arg, ft_strlen(arg));
}

static int	print_echo_arg(char *arg, int interpret)
{
	char	*expanded;

	expanded = expand_string(arg);
	if (!expanded)
		return (0);
	if (interpret)
		print_with_escapes(expanded);
	else
		write(1, expanded, ft_strlen(expanded));
	free(expanded);
	return (1);
}

int	echo_builtin(char **args)
{
	int	i;
	int	newline;
	int	interpret_escapes;

	newline = 1;
	interpret_escapes = 0;
	i = parse_options(args, &newline, &interpret_escapes);
	while (args[i])
	{
		if (!print_echo_arg(args[i], interpret_escapes))
			return (1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

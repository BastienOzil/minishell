/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:39 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:58:40 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo_builtin(char **args)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j])
			break ;
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i++ + 1])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

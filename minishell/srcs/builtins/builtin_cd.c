/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:31 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:58:33 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cd_error(char *path)
{
	write(2, "minishell: cd: ", 16);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	perror(NULL);
}

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	return (S_ISDIR(sb.st_mode));
}

int	cd_builtin(char **args)
{
	if (!args[1])
	{
		write(2, "minishell: cd: missing argument\n", 32);
		return (1);
	}
	if (!is_directory(args[1]))
	{
		if (access(args[1], F_OK) == -1)
			print_cd_error(args[1]);
		else
		{
			write(2, "minishell: cd: ", 16);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": Not a directory\n", 19);
		}
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		print_cd_error(args[1]);
		return (1);
	}
	return (0);
}

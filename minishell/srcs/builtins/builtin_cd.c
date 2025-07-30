/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:47:12 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 09:53:52 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_to_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	if (chdir(home) != 0)
	{
		print_cd_error(home);
		return (1);
	}
	return (0);
}

static int	cd_to_path(char *path)
{
	if (!is_directory(path))
	{
		if (access(path, F_OK) == -1)
			print_cd_error(path);
		else
		{
			write(2, "minishell: cd: ", 16);
			write(2, path, ft_strlen(path));
			write(2, ": Not a directory\n", 19);
		}
		return (1);
	}
	if (chdir(path) != 0)
	{
		print_cd_error(path);
		return (1);
	}
	return (0);
}

int	cd_builtin(char **args)
{
	int	arg_count;

	arg_count = count_args_cd(args);
	if (arg_count > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (!args[1])
		return (cd_to_home());
	return (cd_to_path(args[1]));
}

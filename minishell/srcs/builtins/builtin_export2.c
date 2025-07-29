/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:38:57 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 15:39:24 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Gère un seul argument d'export
int handle_single_export_arg(char *arg, char ***envp)
{
	char *var_name;

	if (!is_valid_identifier(arg))
	{
		write(STDERR_FILENO, "minishell: export: `", 20);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		return (1);
	}
	var_name = get_var_name_from_export(arg);
	if (!var_name)
		return (1);
	if (ft_strchr(arg, '='))
	{
		if (is_var_exist(var_name, envp))
			replace_val(arg, envp);
		else
			add_var(envp, arg);
	}
	else
	{
	}
	free(var_name);
	return (0);
}

int export_builtin(char **args, char ***envp)
{
	int i;
	int exit_code;

	if (!args[1])
		return (export_empty(envp));

	exit_code = 0;
	i = 1;
	while (args[i])
	{
		if (handle_single_export_arg(args[i], envp) != 0)
			exit_code = 1;
		i++;
	}

	return (exit_code);
}

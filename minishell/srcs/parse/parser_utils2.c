/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:22:48 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 09:59:11 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int count_args(char **args)
{
	int count;

	count = 0;
	if (args)
	{
		while (args[count])
			count++;
	}
	return (count);
}

static void free_arg_array(char **args)
{
	int i;

	if (!args)
		return;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static char **alloc_new_args(int count)
{
	char **new_args;

	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	return (new_args);
}

static char **copy_existing_args(char **args, char **new_args, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			while (--i >= 0)
				free(new_args[i]);
			free(new_args);
			return (NULL);
		}
		i++;
	}
	return (new_args);
}

char **add_arg(char **args, char *new_arg)
{
	int count;
	char **new_args;

	if (!new_arg)
		return (args);
	count = count_args(args);
	new_args = alloc_new_args(count);
	if (!new_args)
		return (args);
	if (!copy_existing_args(args, new_args, count))
		return (args);
	new_args[count] = ft_strdup(new_arg);
	if (!new_args[count])
	{
		free_arg_array(new_args);
		return (args);
	}
	new_args[count + 1] = NULL;
	if (args)
		free_arg_array(args);
	return (new_args);
}

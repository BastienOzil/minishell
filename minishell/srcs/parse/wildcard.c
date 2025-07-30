/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:11:10 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 15:14:03 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	match_pattern(char *pattern, char *str)
{
	if (!*pattern && !*str)
		return (1);
	if (*pattern == '*')
	{
		if (match_pattern(pattern + 1, str))
			return (1);
		if (*str && match_pattern(pattern, str + 1))
			return (1);
		return (0);
	}
	if (*pattern == *str && *pattern)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

int	count_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

char	**fill_matches(char *pattern, int count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				i;

	matches = malloc(sizeof(char *) * (count + 1));
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (matches);
	i = 0;
	entry = readdir(dir);
	while (entry && i < count)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
			matches[i++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	matches[i] = NULL;
	closedir(dir);
	return (matches);
}

char	**expand_wildcard(char *pattern)
{
	int		count;
	char	**matches;

	if (!ft_strchr(pattern, '*'))
		return (NULL);
	count = count_matches(pattern);
	if (count == 0)
		return (NULL);
	matches = fill_matches(pattern, count);
	return (matches);
}

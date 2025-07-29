/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:18 by bozil             #+#    #+#             */
/*   Updated: 2025/07/29 19:39:07 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*handle_absolute_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full;
	int		i;

	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full);
		}
		free(full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

static char	*search_in_path_dirs(char *cmd, char **envp)
{
	char	**paths;
	char	*path_var;
	char	*result;

	path_var = get_path_var(envp);
	if (!path_var)
		return (ft_strdup(cmd));
	paths = ft_split(path_var, ':');
	if (!paths)
		return (ft_strdup(cmd));
	result = search_in_paths(paths, cmd);
	if (result)
		return (result);
	return (ft_strdup(cmd));
}

char	*find_path(char *cmd, char **envp)
{
	char	*result;

	if (!cmd)
		return (NULL);
	result = handle_absolute_path(cmd);
	if (result)
		return (result);
	return (search_in_path_dirs(cmd, envp));
}

void	execute_command(t_cmd *cmd, char **envp)
{
	char	*path;

	path = find_path(cmd->args[0], envp);
	if (!path)
	{
		print_cmd_not_found(cmd->args[0]);
		exit(127);
	}
	execve(path, cmd->args, envp);
	free(path);
	puppetmaster_perror("execve");
	exit(EXIT_FAILURE);
}

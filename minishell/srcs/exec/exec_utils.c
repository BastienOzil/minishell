/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:57:18 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 16:26:21 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path_var(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
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

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_var;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_var = get_path_var(envp);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
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
	puppetmaster_perror("execve");
	exit(EXIT_FAILURE);
}

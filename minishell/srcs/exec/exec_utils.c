#include "../includes/minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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

// char	*find_path(char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*path_var;
// 	char	*full;
// 	int		i;

// 	if (!cmd || ft_strchr(cmd, '/'))
// 		return (ft_strdup(cmd));
// 	path_var = get_path_var(envp);
// 	if (!path_var)
// 		return (NULL);
// 	paths = ft_split(path_var, ':');
// 	if (!paths)
// 		return (NULL);
// 	i = 0;
// 	while (paths[i])
// 	{
// 		full = join_path(paths[i], cmd);
// 		if (full && access(full, X_OK) == 0)
// 		{
// 			ft_free_split(paths);
// 			return (full);
// 		}
// 		free(full);
// 		i++;
// 	}
// 	ft_free_split(paths);
// 	return (NULL);
// }

#include "../includes/minishell.h"

// Libère un tableau de chaînes
void	ft_free_split(char **split)
{
	int	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

// Récupère la valeur de la variable PATH
char	*get_path_var(char **envp)
{
	int	i = 0;

	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5); // saute "PATH="
		i++;
	}
	return (NULL);
}

// Construit le chemin vers la commande
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_var;
	char	*tmp;
	char	*full_path;
	int		i = 0;

	if (!cmd || strchr(cmd, '/')) // si déjà un chemin
		return (strdup(cmd));

	path_var = get_path_var(envp);
	if (!path_var)
		return (NULL);

	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);

	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

// Elle exécute une commande (comme ls, echo, etc.) en créant un nouveau processus 
// à l’aide de fork() et en lançant la commande avec execve()
void	execute_cmd(t_cmd *cmd, char ***envp)
{
	pid_t	pid;

	if (is_builtin(cmd->args[0]))
	{
		if (cmd->infile)
			exec_input_redirection(cmd);
		else if (cmd->heredoc)
			exec_heredoc(cmd);

		if (cmd->append)
			exec_append_redirection(cmd);
		else if (cmd->outfile)
			exec_output_redirection(cmd);

		exec_builtin(cmd, envp);
		return ;
	}


	pid = fork();
	if (pid < 0)
	{
		puppetmaster_perror("fork");
		return ;
	}
	if (pid == 0)
	{
		if (cmd->infile)
			exec_input_redirection(cmd);
		else if (cmd->heredoc)
			exec_heredoc(cmd);
		
		if (cmd->append)
			exec_append_redirection(cmd);
		else if (cmd->outfile)
			exec_output_redirection(cmd);

		char *path = find_path(cmd->args[0], *envp);
		if (!path)
		{
			puppetmaster_perror(cmd->args[0]);
			exit(127);
		}
		execve(path, cmd->args, *envp);

		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}

void	execute_all(t_cmd *cmd, char ***envp)
{
	if (!cmd)
		return ;
	
	if (cmd->next)
		execute_pipeline(cmd, envp);
	else
		execute_cmd(cmd, envp);
}

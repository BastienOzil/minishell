#include "../includes/minishell.h"

void	ft_free_split(char **split)
{
	int	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

char	*get_path_var(char **envp)
{
	int	i = 0;

	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path_var;
	char	*tmp;
	char	*full_path;
	int		i = 0;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));

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

void	execute_cmd(t_cmd *cmd, char ***envp)
{
	pid_t	pid;
	char	*path;
	int		builtin_result;

	if (!cmd)
		return ;
	if (!cmd->args || !cmd->args[0])
		return ;
	
	if (is_builtin(cmd->args[0]))
	{
		int saved_stdout = dup(STDOUT_FILENO);
		int saved_stdin = dup(STDIN_FILENO);
		
		if (cmd->infile)
			exec_input_redirection(cmd);
		else if (cmd->heredoc)
			exec_heredoc(cmd);

		if (cmd->append)
			exec_append_redirection(cmd);
		else if (cmd->outfile)
			exec_output_redirection(cmd);

		builtin_result = exec_builtin(cmd, envp);
		
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		
		g_exit_status = builtin_result;
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

		path = find_path(cmd->args[0], *envp);
		if (!path)
		{
			puppetmaster_perror(cmd->args[0]);
			exit(127);
		}
		execve(path, cmd->args, *envp);
		puppetmaster_perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	execute_all(t_cmd *cmd, char ***envp)
{
	if (!cmd)
		return ;

	if (cmd->type == NODE_PIPELINE)
	{
		t_cmd *flat = linearize_pipeline(cmd);
		execute_pipeline(flat, envp);
		return;
	}
	else
	{
		execute_cmd(cmd, envp);
		return;
	}
}

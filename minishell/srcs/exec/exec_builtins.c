#include "../includes/minishell.h"

//detections des appels de fonctions interne (echo, cd, pwd, env, export, unset, exit)

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd")
		|| !strcmp(cmd, "pwd") || !strcmp(cmd, "export")
		|| !strcmp(cmd, "unset") || !strcmp(cmd, "env")
		|| !strcmp(cmd, "exit"));
}

int	exec_builtin(char **args, char ***envp)
{
	if (!args || !args[0])
		return (1);
	if (!strcmp(args[0], "echo"))
		return (echo_builtin(args));
	// if (!strcmp(args[0], "cd"))
	// 	return (cd_builtin(args));
	// if (!strcmp(args[0], "pwd"))
	// 	return (pwd_builtin());
	if (!strcmp(args[0], "env"))
		return (env_builtin(*envp));
	// if (!strcmp(args[0], "exit"))
	// 	return (exit_builtin(args));
	// if (!strcmp(args[0], "export"))
	// 	return (export_builtin(args, envp));
	// if (!strcmp(args[0], "unset"))
	// 	return (unset_builtin(args, envp));
	return (1);
}

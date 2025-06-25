#include "../includes/minishell.h"

//detections des appels de fonctions interne (echo, cd, pwd, env, export, unset, exit)

int	is_builtin(const char *cmd)
{
	printf(">> vérif is_builtin avec : [%s]\n", cmd);
	if (!cmd)
		return (0);
	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd")
		|| !strcmp(cmd, "pwd") || !strcmp(cmd, "export")
		|| !strcmp(cmd, "unset") || !strcmp(cmd, "env")
		|| !strcmp(cmd, "exit"));
}

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (!strcmp(cmd->args[0], "echo"))
	printf("echo");
		return (echo_builtin(cmd->args));
	// if (!strcmp(args[0], "cd"))
	// 	return (cd_builtin(args));
	// if (!strcmp(args[0], "pwd"))
	// 	return (pwd_builtin());
	if (!strcmp(cmd->args[0], "env"))
		return (env_builtin(*envp));
	// if (!strcmp(args[0], "exit"))
	// 	return (exit_builtin(args));
	// if (!strcmp(args[0], "export"))
	// 	return (export_builtin(args, envp));
	// if (!strcmp(args[0], "unset"))
	// 	return (unset_builtin(args, envp));
	return (1);
}

#include "../includes/minishell.h"

//detections des appels de fonctions interne (echo, cd, pwd, env, export, unset, exit)

// int	is_builtin(const char *cmd)
// {
// 	printf(">> vérif is_builtin avec : [%s]\n", cmd);
// 	if (!cmd)
// 		return (0);
// 	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd")
// 		|| !strcmp(cmd, "pwd") || !strcmp(cmd, "export")
// 		|| !strcmp(cmd, "unset") || !strcmp(cmd, "env")
// 		|| !strcmp(cmd, "exit"));
// }

int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);

	// Affichage de debug (à commenter plus tard)
	if (!strcmp(cmd, "echo"))
		return (1);
	if (!strcmp(cmd, "cd"))
		return (1);
	if (!strcmp(cmd, "pwd"))
		return (1);
	if (!strcmp(cmd, "env"))
		return (1);
	if (!strcmp(cmd, "exit"))
		return (1);
	if (!strcmp(cmd, "export"))
		return (1);
	if (!strcmp(cmd, "unset"))
		return (1);

	return (0);
}


int	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (!strcmp(cmd->args[0], "echo"))
		return (echo_builtin(cmd->args));
	if (!strcmp(cmd->args[0], "cd"))
		return (cd_builtin(cmd->args));
	if (!strcmp(cmd->args[0], "pwd"))
		return (pwd_builtin());
	if (!strcmp(cmd->args[0], "env"))
		return (env_builtin(envp));
	if (!strcmp(cmd->args[0], "exit"))
		return (exit_builtin(cmd->args));
	if (!strcmp(cmd->args[0], "export"))
		return (export_builtin(cmd->args, envp));
	if (!strcmp(cmd->args[0], "unset"))
		return (unset_builtin(cmd->args, envp));
	return (1);
}

#ifndef EXEC_H
#define EXEC_H

#include "shared.h"

// executor
typedef struct s_exec_cmd
{
    char **argv;
    char *infile;
    char *outfile;
    char *heredoc;
    int append;
    struct s_exec_cmd *next;
} t_exec_cmd;


// executor.c
void    execute_cmd(t_exec_cmd *exec_cmd, char **envp);
void	execute_all(t_exec_cmd *exec_cmd, char **envp);

//redirect.c
void	exec_output_redirection(t_exec_cmd *exec_cmd);
void	exec_input_redirection(t_exec_cmd *exec_cmd);
void	exec_append_redirection(t_exec_cmd *exec_cmd);
void    exec_heredoc(t_exec_cmd *cmd);

//pipe.c
void	execute_pipeline(t_exec_cmd *cmd_list, char **envp);

//builtins.c
int	echo_builtin(char **args);
int	cd_builtin(char **args);
int	pwd_builtin(void);
int	env_builtin(char **envp);
int	exit_builtin(char **args);
int	export_builtin(char **args, char ***envp);
int	unset_builtin(char **args, char ***envp);

#endif

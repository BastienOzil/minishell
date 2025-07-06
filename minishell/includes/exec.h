#ifndef EXEC_H
#define EXEC_H

#include "shared.h"

// executor
// typedef struct s_cmd
// {
//     char **argv;
//     char *infile;
//     char *outfile;
//     char *heredoc;
//     int append;
//     struct s_cmd *next;
// } t_cmd;


// executor.c
void	ft_free_split(char **split);
char	*get_path_var(char **envp);
char	*find_path(char *cmd, char **envp);
void    execute_cmd(t_cmd *cmd, char ***envp);
void	execute_all(t_cmd *cmd, char ***envp);

//redirect.c
void	exec_output_redirection(t_cmd *cmd);
void	exec_input_redirection(t_cmd *cmd);
void	exec_append_redirection(t_cmd *cmd);
void    exec_heredoc(t_cmd *cmd);

//pipe.c
void	execute_pipeline(t_cmd *cmd_list, char ***envp);

//builtins
int	    echo_builtin(char **args);
int	    cd_builtin(char **args);
int	    pwd_builtin(void);
char    **dup_env(char **envp);
int	    export_empty(char ***envp);
int	    env_builtin(char ***envp);
int 	exit_builtin(char **args);
int	    export_builtin(char **args, char ***envp);
char	*is_arg_export(char *str);
int		is_var_exist(char *var, char ***envp);
void	add_var(char ***envp, char *arg);
void	replace_val(char **args, char ***envp);
void	free_envp(char ***envp);
int	    unset_builtin(char **args, char ***envp);
void	remove_var(char ***envp, char *var);

//exec_builtin.c
int	is_builtin(const char *cmd);
int	exec_builtin(t_cmd *cmd, char ***envp);


#endif

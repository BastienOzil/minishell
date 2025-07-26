/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:00:22 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 15:44:54 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include "shared.h"

// exec_utils.c
void ft_free_split(char **split);
char *get_path_var(char **envp);
char *join_path(char *dir, char *cmd);
char *find_path(char *cmd, char **envp);

// executor.c
void execute_builtin_with_redirs(t_cmd *cmd, char ***envp);
void execute_external_cmd(t_cmd *cmd, char ***envp);
void execute_cmd(t_cmd *cmd, char ***envp);
void execute_all(t_cmd *cmd, char ***envp);

// redirect.c
void exec_output_redirection(t_cmd *cmd);
void exec_input_redirection(t_cmd *cmd);
void exec_append_redirection(t_cmd *cmd);

//______pipe_____
// pipe_utils.c
int create_pipe(int pipefd[2]);
pid_t create_child_process(void);
int redirect_fd(int input_fd, int output_fd);
void close_unused_fds(int pipefd[2]);

// pipe_exec.c
void execute_command(t_cmd *cmd, char **envp);
void run_child_process(t_cmd *cmd, int in_fd, int pipefd[2], char **envp);

// pipe_redir.c
void handle_redirections(t_cmd *cmd);

// pipe_run.c
void child_exec(t_cmd *cmd, int in_fd, int pipefd[2], char ***envp);
void handle_parent(t_cmd *cmd, int *in_fd, int pipefd[2]);
void wait_and_set_exit_status(pid_t last_pid);

// pipe.c
void execute_pipeline(t_cmd *cmd_list, char ***envp);

// builtins
int echo_builtin(char **args);
void print_cd_error(char *path);
int is_directory(char *path);
int cd_builtin(char **args);
int pwd_builtin(void);
char **dup_env(char **envp);
int export_empty(char ***envp);
int env_builtin(char ***envp);
int exit_builtin(char **args);
int export_builtin(char **args, char ***envp);
char *is_arg_export(char *str);
int is_var_exist(char *var, char ***envp);
void add_var(char ***envp, char *arg);
void replace_val(char *args, char ***envp);
void free_envp(char ***envp);
int unset_builtin(char **args, char ***envp);
void remove_var(char ***envp, char *var);
int handle_single_export_arg(char *arg, char ***envp);
int export_builtin(char **args, char ***envp);
int is_valid_identifier(char *str);
char *get_var_name_from_export(char *str);
int is_directory(char *path);
void print_cd_error(char *path);
int count_args_cd(char **args);

// exec_builtin.c
int is_builtin(const char *cmd);
int exec_builtin(t_cmd *cmd, char ***envp);

// heredoc.c
int open_tmp_heredoc(char *template_path);
int write_heredoc_lines(int fd, const char *delimiter);
int redirect_stdin_from_tmp(const char *path);
void exec_heredoc(t_cmd *cmd);

#endif

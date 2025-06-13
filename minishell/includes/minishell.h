#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../utils/libft/libft.h"
#include <sys/time.h>
#include <sys/ioctl.h>

// token type
typedef enum
{
    TOKEN_WORD,    // mots/commandes/arguments
    TOKEN_PIPE,    // | connecter la sortie standard d'une commande à l'entrée standard d'une autre
    TOKEN_INFILE,  // < redirection depuis un fichier
    TOKEN_OUTFILE, // > efface le contenu puis le remplace
    TOKEN_APPEND,  // >> ajoute le countenu a la fin du fichier
    TOKEN_HEREDOC, // << écrire directement du texte dans le terminal
    TOKEN_EOF,     // retour d'erreur et sert de marqueur de fin (EOF = End Of File)
} t_token_type;

// commande type
typedef enum e_node_type
{
    NODE_COMMAND,
    NODE_PIPELINE,
    NODE_REDIR
} t_node_type;

// redirection
typedef struct s_redir
{
    t_token_type type;
    char *file;
    struct s_redir *next;
} t_redir;

// token
typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

// lexer
typedef struct s_lexer
{
    char *input;
    int i;
} t_lexer;

// executor
typedef struct s_cmd
{
    char **argv;
    char *infile;
    char *outfile;
    char *heredoc;
    int append;
    struct s_cmd *next;
} t_cmd;

// parser
typedef struct s_parser
{
    t_token *tokens;
    t_token *current;
} t_parser;

// redirection order
typedef struct s_ast_node
{
    t_node_type type;
    char **args;
    t_redir *redirs;
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_ast_node;

// executor.c
void    execute_cmd(t_cmd *cmd, char **envp);
void	execute_all(t_cmd *cmd, char **envp);

//redirect.c
void	exec_output_redirection(t_cmd *cmd);
void	exec_input_redirection(t_cmd *cmd);
void	exec_append_redirection(t_cmd *cmd);
void    exec_heredoc(t_cmd *cmd);

// parser
t_ast_node *parse_command(t_parser *parser);
t_ast_node *parse_pipeline(t_parser *parser);
t_ast_node *parse(t_token *tokens);

// token & lexer
t_token *new_token(t_token_type type, char *value);
t_token *get_next_token(t_lexer *lexer);
int is_space(char c);
int is_special(char c);
char *get_word(t_lexer *lexer);
void skip_spaces(t_lexer *lexer);

// lexer_cmd
t_token *handle_pipe(t_lexer *lexer);
t_token *handle_input_redirection(t_lexer *lexer);
t_token *handle_output_redirection(t_lexer *lexer);

// utils
int is_special(char c);
int is_space(char c);

// cleanup
void free_redir(t_redir *redir);
void free_tokens(t_token *tokens);
void free_array(char **arr);

// prompt
void	ft_run_tests(char **envp);
void	ft_run_interactive(char **envp);
void	handle_line(char *line);
void	handle_tokens(t_lexer *lexer);

// print_tokken
void print_token(t_token *token);

//error_messages.c
void	    puppetmaster_perror(const char *context);
int	        get_random_index(int max);

//animations.c
void	slow_type_prompt(const char *str);
void	launch_animation(void);
void	slow_type_line_at(int row, int col, const char *str);
void	clear_screen(void);
void	move_cursor(int row, int col);
int	    int_to_str(int n, char *str);
int	    ft_random_digit(void);

//pipe.c
void	execute_pipeline(t_cmd *cmd_list, char **envp);

//builtins 


#endif

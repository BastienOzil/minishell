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

// Structure unifiée pour les commandes et l'AST
typedef struct s_cmd
{
    t_node_type type;    // Type de boucle (COMMAND, PIPELINE, REDIR)
    char **args;         // Arguments de la commande
    char *infile;        // Fichier d'entrée
    char *outfile;       // Fichier de sortie
    int append;          // Flag pour >>
    char *heredoc;       // Délimiteur pour heredoc
    struct s_cmd *left;  // boucle gauche (pour pipelines)
    struct s_cmd *right; // boucle droit (pour pipelines)
    struct s_cmd *next;  // boucle suivant (si besoin pour une liste)
} t_cmd;

// parser
typedef struct s_parser
{
    t_token *tokens;
    t_token *current;
} t_parser;

// aurelia's part

// builtins
int	exec_builtin(char **args, char ***envp);
int	is_builtin(char *cmd);

// executor.c
void    execute_cmd(t_cmd *cmd, char **envp);
void    execute_all(t_cmd *cmd, char **envp);

//redirect.c
void    exec_output_redirection(t_cmd *cmd);
void    exec_input_redirection(t_cmd *cmd);
void    exec_append_redirection(t_cmd *cmd);
void    exec_heredoc(t_cmd *cmd);

// prompt
void    ft_run_tests(char **envp);
void    ft_run_interactive(char **envp);
void    handle_line(char *line);
void    handle_tokens(t_lexer *lexer);

//pipe.c
void    execute_pipeline(t_cmd *cmd_list, char **envp);

/*--------------------------------------------------------------------------*/

// bastien's part

// parser
t_cmd *parse_command(t_parser *parser);
t_cmd *parse_pipeline(t_parser *parser);
t_cmd *parse(t_token *tokens);

// parser_utils
t_cmd *new_node(t_node_type type);
void advance_token(t_parser *parser);
int match_token(t_parser *parser, t_token_type type);
int is_redir_token(t_token_type type);
char **add_arg(char **args, char *new_arg);
void parse_redir(t_parser *parser, t_cmd *node);

// handle_line
void init_lexer(t_lexer *lexer, char *input);
t_token *tokenize(char *input);
void print_ast(t_cmd *node, int depth);
void handle_line(char *line);

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
void free_args(char **args);
void free_ast(t_cmd *node);

// print_tokken
void print_token(t_token *token);

// error_msg
int get_random_index(int max);
void puppetmaster_perror(const char *context);
void print_loop(const char *quote);
void format_line(char *dst, const char *quote);

// vanish
void vanish_blank(char *temp, int l, int r);
void vanish_write(const char *str, int len);
void vanish_effect(char *temp, const char *ref);

// animation
void slow_type_prompt(const char *str);
void launch_animation(void);
void slow_type_line_at(int row, int col, const char *str);
void clear_screen(void);
void move_cursor(int row, int col);
int int_to_str(int n, char *str);
int ft_random_digit(void);
void puppetmaster_perror(const char *context);

#endif

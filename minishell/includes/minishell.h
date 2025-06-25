/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:25:55 by bozil             #+#    #+#             */
/*   Updated: 2025/06/25 09:12:11 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define PROMPT_COLOR "\001\033[1;32m\002"
#define RESET_COLOR "\001\033[0m\002"
#define ERROR_COLOR "\033[1;31m"
#define WARNING_COLOR "\033[1;33m"

#define MAX_PATH 4096
#define MAX_ARGS 1024
#define BUFFER_SIZE 1024

// Codes de sortie
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define EXIT_MISUSE 2
#define EXIT_CANNOT_EXECUTE 126
#define EXIT_COMMAND_NOT_FOUND 127

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/time.h>
#include "../utils/libft/libft.h"

extern int	g_exit_status;

// Types de tokens
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INFILE,
	TOKEN_OUTFILE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_DQUOTE,
	TOKEN_SQUOTE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF
}	t_token_type;

// Types de noeuds AST
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPELINE,
	NODE_AND,
	NODE_OR,
	NODE_PARENTHESES
}	t_node_type;

// Structure pour les tokens
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

// Structure pour le lexer
typedef struct s_lexer
{
	char	*input;
	int		i;
}	t_lexer;

// Structure pour les redirections
typedef struct s_redir
{
	t_token_type		type;
	char				*filename;
	struct s_redir		*next;
}	t_redir;

// Structure pour l'AST
typedef struct s_cmd
{
	t_node_type		type;
	char			**args;
	struct s_cmd	*left;
	struct s_cmd	*right;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	int				append;
}	t_cmd;

// Structure pour le parser
typedef struct s_parser
{
	t_token		*tokens;
	t_token		*current;
}	t_parser;

// === PROTOTYPES ===

// cleanup.c
void		free_redir(t_redir *redir);
void		free_tokens(t_token *tokens);
void		free_args(char **args);
void		free_ast(t_cmd *node);
void		free_array(char **arr);

// error_messages.c
int			get_random_index(int max);
void		puppetmaster_perror(const char *context);
void		print_loop(const char *quote);
void		format_line(char *dst, const char *quote);

// expansion.c
char		*get_env_value(char *var_name);
char		*get_var_name(t_lexer *lexer);
t_token		*handle_variable(t_lexer *lexer);
char		*handle_var_expansion(char *str, int *i);
char		*expand_string(char *str);

// handle_line.c
void		init_lexer(t_lexer *lexer, char *input);
t_token		*tokenize(char *input);
void		print_ast(t_cmd *node, int depth);
void		handle_line(char *line);

// lexer.c
void		skip_spaces(t_lexer *lexer);
char		*get_word(t_lexer *lexer);
t_token		*new_token(t_token_type type, char *value);
t_token		*get_next_token(t_lexer *lexer);

// lexer_cmd.c
t_token		*handle_pipe(t_lexer *lexer);
t_token		*handle_input_redirection(t_lexer *lexer);
t_token		*handle_output_redirection(t_lexer *lexer);

// logical_ops.c
t_token		*handle_and(t_lexer *lexer);
t_token		*handle_or(t_lexer *lexer);
t_token		*handle_parentheses(t_lexer *lexer);
t_cmd		*parse_logical(t_parser *parser);

// parser.c
t_cmd		*parse_command(t_parser *parser);
t_cmd		*parse_pipeline(t_parser *parser);
t_cmd		*parse(t_token *tokens);

// parser_utils.c
t_cmd		*new_node(t_node_type type);
void		advance_token(t_parser *parser);
int			match_token(t_parser *parser, t_token_type type);
int			is_redir_token(t_token_type type);
char		**add_arg(char **args, char *new_arg);
void		parse_redir(t_parser *parser, t_cmd *node);

// print_token.c
void		print_token(t_token *token);

// quote_parser.c
char		*get_double_quoted_string(t_lexer *lexer);
char		*get_single_quoted_string(t_lexer *lexer);
t_token		*handle_quotes(t_lexer *lexer);
int			is_quote(char c);

// utils.c
int			is_space(char c);
int			is_special(char c);

// vanish.c
void		vanish_effect(char *temp, const char *ref);
void		vanish_blank(char *temp, int l, int r);
void		vanish_write(const char *str, int len);

// wildcard.c
int			match_pattern(char *pattern, char *str);
int			count_matches(char *pattern);
char		**fill_matches(char *pattern, int count);
char		**expand_wildcard(char *pattern);

// dir animation
void slow_type_prompt(const char *str);
void launch_animation(void);
void slow_type_line_at(int row, int col, const char *str);
void clear_screen(void);
void move_cursor(int row, int col);
int int_to_str(int n, char *str);
int ft_random_digit(void);

#endif
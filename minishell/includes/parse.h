/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:00:10 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 17:01:01 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "shared.h"

// Structure pour les tokens
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

// Structure pour le lexer
typedef struct s_lexer
{
	char			*input;
	int				i;
}					t_lexer;

// Structure pour le parser
typedef struct s_parser
{
	t_token			*tokens;
	t_token			*current;
	int				error;
}					t_parser;

typedef struct s_error
{
	const char		*prefix;
	const char		*reset;
	const char		*clear;
	const char		*carriage;
	int				j;
	int				len;
}					t_error;

// ============================================================================
// FONCTIONS DE LEXING/TOKENISATION
// ============================================================================

// handle_line.c
void				init_lexer(t_lexer *lexer, char *input);
t_token				*tokenize(char *input);
void				print_ast(t_cmd *node, int depth);
void				handle_line(char *line, char ***envp);

// lexer.c
t_token				*new_token(t_token_type type, char *value);
void				skip_spaces(t_lexer *lexer);
char				*get_word(t_lexer *lexer);
int					is_special_except_quotes_and_dollar(char c);
int					is_space(char c);
int					is_special(char c);
int					is_special_except_quotes_and_dollar(char c);
t_token				*get_complex_word(t_lexer *lexer);
t_token				*get_next_token(t_lexer *lexer);

// lexer_cmd.c
t_token				*handle_pipe(t_lexer *lexer);
t_token				*handle_input_redirection(t_lexer *lexer);
t_token				*handle_output_redirection(t_lexer *lexer);
t_token				*handle_and(t_lexer *lexer);
t_token				*handle_or(t_lexer *lexer);
t_token				*handle_parentheses(t_lexer *lexer);
char				*handle_variable2(t_lexer *lexer, char *result);
char				*handle_double_quote(t_lexer *lexer, char *result);
char				*handle_single_quote(t_lexer *lexer, char *result);
char				*handle_regular_char(t_lexer *lexer, char *result);
t_token				*handle_or(t_lexer *lexer);

// quote_parser.c
t_token				*handle_quotes(t_lexer *lexer);
char				*get_double_quoted_string(t_lexer *lexer);
char				*get_single_quoted_string(t_lexer *lexer);
int					is_quote(char c);

// expansion.c
t_token				*handle_variable(t_lexer *lexer);
char				*expand_string(char *str);
char				*get_env_value(char *var_name);
char				*get_var_name(t_lexer *lexer);
char				*handle_var_expansion(char *str, int *i);

// logical_ops.c
t_cmd				*parse_logical(t_parser *parser);

// wildcards.c
char				**expand_wildcard(char *pattern);
int					match_pattern(char *pattern, char *str);
int					count_matches(char *pattern);
char				**fill_matches(char *pattern, int count);

// ============================================================================
// FONCTIONS DE PARSING
// ============================================================================

// parser.c
t_cmd				*parse_command(t_parser *parser);
t_cmd				*parse_pipeline(t_parser *parser);
t_cmd				*parse(t_token *tokens);

// parser_utils.c
t_cmd				*new_node(t_node_type type);
void				advance_token(t_parser *parser);
int					match_token(t_parser *parser, t_token_type type);
int					is_redir_token(t_token_type type);
char				**add_arg(char **args, char *new_arg);
void				parse_redir(t_parser *parser, t_cmd *node);
void				apply_redirection(t_parser *parser, t_cmd *node,
						t_token_type redir_type);
int					validate_redir_syntax(t_parser *parser, t_cmd *node,
						t_token_type redir_type);
void				error_newline(void);
void				error_tokken(void);
void				error_pipe(void);

// parser_error.c
int					validate_redir_token(t_parser *parser);
int					check_multiple_input(t_cmd *node, t_token_type type);
int					check_multiple_output(t_cmd *node, t_token_type type);

// ============================================================================
// FONCTIONS UTILITAIRES
// ============================================================================

// cleanup.c
void				free_redir(t_redir *redir);
void				free_array(char **arr);
void				free_args(char **args);
void				free_tokens(t_token *tokens);
void				free_ast(t_cmd *ast);

// print_token.c
void				print_token(t_token *token);

// error_msg.c
int					get_random_index(int max);
void				puppetmaster_perror(const char *context);
void				print_loop(const char *quote);
void				format_line(char *dst, const char *quote);

// ============================================================================
// ANIMATION
// ============================================================================

// vanish.c
void				vanish_blank(char *temp, int l, int r);
void				vanish_write(const char *str, int len);
void				vanish_effect(char *temp, const char *ref);

// dir animation
void				slow_type_prompt(const char *str);
void				launch_animation(void);
void				slow_type_line_at(int row, int col, const char *str);
void				clear_screen(void);
void				move_cursor(int row, int col);
int					int_to_str(int n, char *str);
int					ft_random_digit(void);

// utils.c
t_cmd				*linearize_pipeline(t_cmd *ast);
void				print_cmd_not_found(const char *cmd);

#endif
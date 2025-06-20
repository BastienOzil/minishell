#ifndef PARSE_H
#define PARSE_H

#include "shared.h"

// Structure pour les tokens
typedef struct s_token
{
	t_token_type type;
	char *value;
	struct s_token *next;
} t_token;

// Structure pour le lexer
typedef struct s_lexer
{
	char *input;
	int i;
} t_lexer;

// Structure pour le parser
typedef struct s_parser
{
	t_token *tokens;
	t_token *current;
} t_parser;

// parser.c
t_ast_node	*parse_command(t_parser *parser);
t_ast_node	*parse_pipeline(t_parser *parser);
t_ast_node	*parse(t_token *tokens);

// lexer.c
t_token		*get_next_token(t_lexer *lexer);
void		skip_spaces(t_lexer *lexer);
char		*get_word(t_lexer *lexer);
int			is_space(char c);
int			is_special(char c);

// lexer_cmd.c
t_token		*handle_pipe(t_lexer *lexer);
t_token		*handle_input_redirection(t_lexer *lexer);
t_token		*handle_output_redirection(t_lexer *lexer);

// token_utils.c
t_token		*new_token(t_token_type type, char *value);

// print_token.c
void		print_token(t_token *token);

// cleanup.c
void		free_tokens(t_token *tokens);
void		free_redir(t_redir *redir);
void		free_array(char **arr);

#endif

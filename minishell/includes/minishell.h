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

typedef enum
{
    TOKEN_WORD,         // mots/commandes/arguments
    TOKEN_PIPE,         // |
    TOKEN_REDIR_IN,     // <
    TOKEN_REDIR_OUT,    // >
    TOKEN_APPEND,       // >>
    TOKEN_HEREDOC,      // <<
    TOKEN_EOF,          // error
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_lexer
{
    char *input;
    int i;
} t_lexer;

// token & lexer
t_token *new_token(t_token_type type, char *value);
t_token *get_next_token(t_lexer *lexer);
int is_space(char c);
int is_special(char c);
//char *ft_substr(char *s, int start, int len);
char *get_word(t_lexer *lexer);
void skip_spaces(t_lexer *lexer);
void free_tokens(t_token *tokens);

// utils
int	is_special(char c);
int	is_space(char c);

#endif

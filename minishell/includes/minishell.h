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
    TOKEN_PIPE,         // | connecter la sortie standard d'une commande à l'entrée standard d'une autre
    TOKEN_INFILE,       // < redirection depuis un fichier
    TOKEN_OUTFILE,      // > efface le contenu puis le remplace
    TOKEN_MERGE,       // >> ajoute le countenu a la fin du fichier
    TOKEN_HEREDOC,      // << écrire directement du texte dans le terminal
    TOKEN_EOF,          // retour d'erreur et sert de marqueur de fin (EOF = End Of File)
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
char *get_word(t_lexer *lexer);
void skip_spaces(t_lexer *lexer);
void free_tokens(t_token *tokens);

// lexer_cmd
t_token	*handle_pipe(t_lexer *lexer);
t_token	*handle_input_redirection(t_lexer *lexer);
t_token	*handle_output_redirection(t_lexer *lexer);


// utils
int	is_special(char c);
int	is_space(char c);

//print_tokken
void	print_token(t_token *token);

#endif

#ifndef MINISHELL_H
# define MINISHELL_H

// ============================================================================
// MACROS ET CONSTANTES
// ============================================================================

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

// =========================================================================
// INCLUDES
// =========================================================================
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <dirent.h>
# include "../utils/libft/libft.h"
# include "shared.h"
# include "parse.h"
# include "exec.h"
# include <sys/time.h>
# include "../animation/includes/animation.h"


// =========================================================================
// STRUCTURES PROPRE A MINISHELL
// =========================================================================

extern int g_exit_status;

typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_shell {
	t_env *env;
	char ***envp;
	int exit_status;
} t_shell;



// =========================================================================
// DÉCLARATIONS DE FONCTIONS SPÉCIFIQUES
// =========================================================================

// handle_line.c
// void init_lexer(t_lexer *lexer, char *input);
// t_token *tokenize(char *input);
// void print_ast(t_cmd *node, int depth);
// void handle_line(char *line);


//error_message.c
void	print_loop(const char *quote);
void	format_line(char *line, const char *quote);

//vanish.c
void	vanish_effect(char *temp, const char *ref);

//error_message.c 
void	puppetmaster_perror(const char *context);

#endif

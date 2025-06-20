#ifndef SHARED_H
#define SHARED_H

// Enums partagés
typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INFILE,
	TOKEN_OUTFILE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef enum
{
	NODE_COMMAND,
	NODE_PIPELINE,
	NODE_REDIR
}	t_node_type;

// Structures partagées
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	t_redir				*redirs;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

#endif

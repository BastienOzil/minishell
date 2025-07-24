/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:00:02 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 15:00:03 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

// Types de tokens
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INFILE,
	TOKEN_OUTFILE,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_DQUOTE,
	TOKEN_SQUOTE
}						t_token_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPELINE,
	NODE_REDIR,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}						t_node_type;

// modification du nom cmd pour la fonction free_ast
typedef struct s_cmd
{
	t_node_type			type;
	char				**args;
	char				*infile;
	char				*outfile;
	int					append;
	char				*heredoc;
	struct s_cmd		*left;
	struct s_cmd		*right;
	struct s_cmd		*next;
}						t_cmd;

// Structures partagées
typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	t_redir				*redirs;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

#endif

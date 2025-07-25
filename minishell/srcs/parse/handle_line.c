/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:53:36 by bozil             #+#    #+#             */
/*   Updated: 2025/07/25 19:36:05 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// initialise lexer
void	init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->i = 0;
}

static void	add_token_to_list(t_token **tokens, t_token **current,
		t_token *new_tok)
{
	if (!*tokens)
	{
		*tokens = new_tok;
		*current = *tokens;
	}
	else
	{
		(*current)->next = new_tok;
		*current = new_tok;
	}
}

// Transforme une ligne de commande en liste de tokens
t_token	*tokenize(char *input)
{
	t_lexer	lexer;
	t_token	*tokens;
	t_token	*current;
	t_token	*new_tok;

	init_lexer(&lexer, input);
	tokens = NULL;
	current = NULL;
	while (1)
	{
		new_tok = get_next_token(&lexer);
		if (!new_tok)
		{
			free_tokens(tokens);
			return (NULL);
		}
		if (new_tok->type == TOKEN_EOF)
		{
			add_token_to_list(&tokens, &current, new_tok);
			break ;
		}
		add_token_to_list(&tokens, &current, new_tok);
	}
	return (tokens);
}


// Traite la ligne de commande complète
void	handle_line(char *line, char ***envp)
{
	t_token	*tokens;
	t_cmd	*ast;

	if (!line || !*line)
		return ;
	tokens = tokenize(line);
	if (!tokens)
	{
		//ft_putstr_fd("Erreur lors de la tokenisation\n", 2);
		return ;
	}
	ast = parse(tokens);
	if (!ast)
	{
		//ft_putstr_fd("Erreur lors du parsing\n", 2);
		free_tokens(tokens);
		return ;
	}
	execute_all(ast, envp);
	free_tokens(tokens);
}

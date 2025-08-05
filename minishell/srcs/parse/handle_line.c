/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurgeorg <aurgeorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:53:36 by bozil             #+#    #+#             */
/*   Updated: 2025/08/05 12:29:05 by aurgeorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_token	*tokenize(char *input, char **envp)
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
		new_tok = get_next_token(&lexer, envp);
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

static t_cmd	*prepare_ast(char *line, t_token **tokens, char **envp)
{
	t_cmd	*ast;

	*tokens = tokenize(line, envp);
	if (!*tokens)
		return (NULL);
	ast = parse(*tokens, envp);
	if (!ast)
	{
		free_tokens(*tokens);
		return (NULL);
	}
	return (ast);
}

void	handle_line(char *line, char ***envp)
{
	t_token	*tokens;
	t_cmd	*ast;

	if (!line || !*line)
		return ;
	ignore_signals();
	ast = prepare_ast(line, &tokens, *envp);
	if (!ast)
	{
		setup_signals_interactive();
		return ;
	}
	execute_all(ast, envp);
	free_tokens(tokens);
	free_ast(ast);
	if (g_exit_status == SIGINT_CODE)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_exit_status = 0;
	}
	setup_signals_interactive();
	rl_on_new_line();
}

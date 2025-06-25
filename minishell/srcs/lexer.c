#include "../includes/minishell.h"

// ignore les espaces
void skip_spaces(t_lexer *lexer)
{
	while (lexer->input[lexer->i] && is_space(lexer->input[lexer->i]))
		lexer->i++;
}

// lit un mot jusqu'au prochain espace ou caractère spécial
char *get_word(t_lexer *lexer)
{
	int start;

	start = lexer->i;
	while (lexer->input[lexer->i] && !is_space(lexer->input[lexer->i]) 
		&& !is_special(lexer->input[lexer->i]))
		lexer->i++;
	return (ft_substr(lexer->input, start, lexer->i - start));
}

// cree un nouveau token
t_token *new_token(t_token_type type, char *value)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

// récupère le token suivant et envoi dans lexer_cmd.c
t_token *get_next_token(t_lexer *lexer)
{
	skip_spaces(lexer);
	if (!lexer->input[lexer->i])
		return (new_token(TOKEN_EOF, NULL));
	if (lexer->input[lexer->i] == '&')
		return (handle_and(lexer));
	if (lexer->input[lexer->i] == '|')
		return (handle_or(lexer));
	if (lexer->input[lexer->i] == '<')
		return (handle_input_redirection(lexer));
	if (lexer->input[lexer->i] == '>')
		return (handle_output_redirection(lexer));
	if (is_quote(lexer->input[lexer->i]))
		return (handle_quotes(lexer));
	if (lexer->input[lexer->i] == '$')
		return (handle_variable(lexer));
	if (lexer->input[lexer->i] == '(' || lexer->input[lexer->i] == ')')
		return (handle_parentheses(lexer));
	return (new_token(TOKEN_WORD, get_word(lexer)));
}


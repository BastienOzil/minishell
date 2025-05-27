#include "../includes/minishell.h"

void	skip_spaces(t_lexer *lexer)
{
	while (lexer->input[lexer->i] && is_space(lexer->input[lexer->i]))
		lexer->i++;
}

char	*get_word(t_lexer *lexer)
{
	int	start;

	start = lexer->i;
	while (lexer->input[lexer->i] && !is_space(lexer->input[lexer->i]) 
		&& !is_special(lexer->input[lexer->i]))
		lexer->i++;
	return (ft_substr(lexer->input, start, lexer->i - start));
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*get_next_token(t_lexer *lexer)
{
	skip_spaces(lexer);
	if (!lexer->input[lexer->i])
		return (new_token(TOKEN_EOF, NULL));
	if (lexer->input[lexer->i] == '|')
	{
		lexer->i++;
		return (new_token(TOKEN_PIPE, ft_substr("|", 0, 1)));
	}
	if (lexer->input[lexer->i] == '<')
	{
		if (lexer->input[lexer->i + 1] == '<')
		{
			lexer->i += 2;
			return (new_token(TOKEN_HEREDOC, ft_substr("<<", 0, 2)));
		}
		lexer->i++;
		return (new_token(TOKEN_REDIR_IN, ft_substr("<", 0, 1)));
	}
	if (lexer->input[lexer->i] == '>')
	{
		if (lexer->input[lexer->i + 1] == '>')
		{
			lexer->i += 2;
			return (new_token(TOKEN_APPEND, ft_substr(">>", 0, 2)));
		}
		lexer->i++;
		return (new_token(TOKEN_REDIR_OUT, ft_substr(">", 0, 1)));
	}
	return (new_token(TOKEN_WORD, get_word(lexer)));
}

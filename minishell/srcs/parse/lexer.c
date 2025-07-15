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
	while (lexer->input[lexer->i] && !is_space(lexer->input[lexer->i]) && !is_special(lexer->input[lexer->i]))
		lexer->i++;
	return (ft_substr(lexer->input, start, lexer->i - start));
}

// Fonction utilitaire pour vérifier si c'est un caractère spécial sauf quotes et $
int is_special_except_quotes_and_dollar(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')');
}

// Fonction pour obtenir un token qui peut contenir des mots, quotes, variables adjacents
t_token *get_complex_word(t_lexer *lexer)
{
    char *result = ft_strdup("");
    int has_content = 0;
    
    while (lexer->input[lexer->i] && !is_space(lexer->input[lexer->i]) && 
           !is_special_except_quotes_and_dollar(lexer->input[lexer->i]))
    {
        if (lexer->input[lexer->i] == '"')
        {
            char *quoted = get_double_quoted_string(lexer);
            if (!quoted)
            {
                free(result);
                return (NULL);
            }
            char *expanded = expand_string(quoted);
            char *temp = ft_strjoin(result, expanded);
            free(result);
            free(quoted);
            free(expanded);
            result = temp;
            has_content = 1;
        }
        else if (lexer->input[lexer->i] == '\'')
        {
            char *quoted = get_single_quoted_string(lexer);
            if (!quoted)
            {
                free(result);
                return (NULL);
            }
            char *temp = ft_strjoin(result, quoted);
            free(result);
            free(quoted);
            result = temp;
            has_content = 1;
        }
        else if (lexer->input[lexer->i] == '$')
        {
            lexer->i++;
            char *var_name = get_var_name(lexer);
            if (!var_name)
            {
                free(result);
                return (NULL);
            }
            char *var_value = get_env_value(var_name);
            char *temp = ft_strjoin(result, var_value);
            free(result);
            free(var_name);
            free(var_value);
            result = temp;
            has_content = 1;
        }
        else
        {
            char char_str[2] = {lexer->input[lexer->i], '\0'};
            char *temp = ft_strjoin(result, char_str);
            free(result);
            result = temp;
            lexer->i++;
            has_content = 1;
        }
    }
    if (!has_content)
    {
        free(result);
        return (NULL);
    }
    
    return (new_token(TOKEN_WORD, result));
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

// récupère le token suivant
t_token *get_next_token(t_lexer *lexer)
{
	skip_spaces(lexer);
	
	if (!lexer->input[lexer->i])
		return (new_token(TOKEN_EOF, NULL));
	if (lexer->input[lexer->i] == '|')
		return (handle_pipe(lexer));
	if (lexer->input[lexer->i] == '<')
		return (handle_input_redirection(lexer));
	if (lexer->input[lexer->i] == '>')
		return (handle_output_redirection(lexer));
	if (lexer->input[lexer->i] == '&')
		return (handle_and(lexer));
	if (lexer->input[lexer->i] == '(' || lexer->input[lexer->i] == ')')
		return (handle_parentheses(lexer));
	return (get_complex_word(lexer));
}

#include "../includes/minishell.h"

// Obtient la valeur d'une variable d'environnement
char	*get_env_value(char *var_name)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_exit_status));
	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

// Lit le nom d'une variable après $
char	*get_var_name(t_lexer *lexer)
{
	int	start;

	start = lexer->i;
	if (lexer->input[lexer->i] == '?')
	{
		lexer->i++;
		return (ft_substr(lexer->input, start, 1));
	}
	while (lexer->input[lexer->i] && (ft_isalnum(lexer->input[lexer->i])
			|| lexer->input[lexer->i] == '_'))
		lexer->i++;
	return (ft_substr(lexer->input, start, lexer->i - start));
}

// Gère l'expansion des variables $VAR
t_token	*handle_variable(t_lexer *lexer)
{
	char	*var_name;
	char	*value;

	lexer->i++;
	var_name = get_var_name(lexer);
	if (!var_name)
		return (NULL);
	value = get_env_value(var_name);
	free(var_name);
	return (new_token(TOKEN_WORD, value));
}

char	*handle_var_expansion(char *str, int *i)
{
	char	*name;
	char	*value;
	int		start;

	if (str[1] == '?')
	{
		*i += 2;
		return (ft_itoa(g_exit_status));
	}
	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start, *i - start);
	(*i)--;
	value = get_env_value(name);
	free(name);
	return (value);
}

// Fonction utilitaire pour joindre et libérer l'ancien résultat
static char	*join_and_free(char *old_str, char *to_add)
{
	char	*new_str;

	if (!old_str || !to_add)
		return (NULL);
	new_str = ft_strjoin(old_str, to_add);
	free(old_str);
	free(to_add);
	return (new_str);
}

// VERSION CORRIGÉE - Expanse une chaîne contenant des variables
char	*expand_string(char *str)
{
	char	*result;
	char	*temp;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			temp = handle_var_expansion(&str[i], &i);
			if (!temp)
			{
				free(result);
				return (NULL);
			}
			result = join_and_free(result, temp);
			if (!result)
				return (NULL);
		}
		else
		{
			temp = ft_substr(str, i, 1);
			if (!temp)
			{
				free(result);
				return (NULL);
			}
			result = join_and_free(result, temp);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}


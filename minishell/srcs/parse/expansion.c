/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:45:28 by bozil             #+#    #+#             */
/*   Updated: 2025/08/05 13:42:30 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*my_getenv(const char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_env_value(char *var_name, char **envp)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_exit_status));
	value = my_getenv(var_name, envp);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

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

t_token	*handle_variable(t_lexer *lexer, char **envp)
{
	char	*var_name;
	char	*value;

	lexer->i++;
	var_name = get_var_name(lexer);
	if (!var_name)
		return (NULL);
	value = get_env_value(var_name, envp);
	free(var_name);
	return (new_token(TOKEN_WORD, value));
}

char	*get_expansion_name(char *str, int *i)
{
	int	start;

	if (!str[*i + 1])
		return ((*i)++, ft_strdup("$"));
	if (str[*i + 1] == '?')
	{
		*i += 2;
		return (ft_strdup("?"));
	}
	if (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_')
		return ((*i)++, ft_strdup("$"));
	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

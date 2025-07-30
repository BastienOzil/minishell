/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:15:32 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 16:31:31 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_and_update(char *result, char *new_str)
{
	char	*temp;

	temp = ft_strjoin(result, new_str);
	free(result);
	return (temp);
}

char	*handle_double_quote(t_lexer *lexer, char *result)
{
	char	*quoted;

	quoted = get_double_quoted_string(lexer);
	if (!quoted)
		return (NULL);
	result = join_and_update(result, quoted);
	free(quoted);
	return (result);
}

char	*handle_single_quote(t_lexer *lexer, char *result)
{
	char	*quoted;

	quoted = get_single_quoted_string(lexer);
	if (!quoted)
		return (NULL);
	result = join_and_update(result, quoted);
	free(quoted);
	return (result);
}

char	*handle_variable2(t_lexer *lexer, char *result)
{
	char	*var_name;
	char	*var_value;

	if (!lexer->input[lexer->i + 1] || (!ft_isalnum(lexer->input[lexer->i + 1])
			&& lexer->input[lexer->i + 1] != '_' && lexer->input[lexer->i
			+ 1] != '?'))
	{
		return (handle_regular_char(lexer, result));
	}
	lexer->i++;
	var_name = get_var_name(lexer);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(var_name);
	result = join_and_update(result, var_value);
	free(var_name);
	free(var_value);
	return (result);
}

char	*handle_regular_char(t_lexer *lexer, char *result)
{
	char	char_str[2];

	char_str[0] = lexer->input[lexer->i];
	char_str[1] = '\0';
	result = join_and_update(result, char_str);
	lexer->i++;
	return (result);
}

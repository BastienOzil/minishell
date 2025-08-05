/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:15:32 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 17:55:58 by bozil            ###   ########.fr       */
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

char	*handle_variable_utils(t_lexer *lexer, char *result)
{
	char	*var_name;
	char	*var_value;
	char	next_char;

	next_char = lexer->input[lexer->i + 1];
	if (!next_char || (!ft_isalnum(next_char) && next_char != '_'
			&& next_char != '?'))
		return (handle_regular_char(lexer, result));
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

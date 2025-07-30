/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:10:32 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 16:34:13 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_token(t_token *token)
{
	char	*types[8];

	types[0] = "WORD";
	types[1] = "PIPE";
	types[2] = "REDIR_IN";
	types[3] = "REDIR_OUT";
	types[4] = "APPEND";
	types[5] = "HEREDOC";
	types[6] = "EOF";
	types[7] = NULL;
	printf("Type: %s", types[token->type]);
	if (token->value)
		printf(", Value: '%s'", token->value);
	printf("\n");
}

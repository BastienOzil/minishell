/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:43:44 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 17:56:17 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_ast(t_cmd *ast)
{
	t_cmd	*next;
	int		i;

	while (ast)
	{
		if (ast->args)
		{
			i = 0;
			while (ast->args[i])
				free(ast->args[i++]);
			free(ast->args);
		}
		free(ast->infile);
		free(ast->outfile);
		free(ast->heredoc);
		if (ast->heredoc_list)
			free_heredoc_list(ast->heredoc_list);
		free_ast(ast->left);
		next = ast->next;
		free(ast);
		ast = next;
	}
}

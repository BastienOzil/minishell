/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:43:44 by bozil             #+#    #+#             */
/*   Updated: 2025/07/31 11:14:00 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_ast_content(t_cmd *ast)
{
	int	i;

	if (ast->args)
	{
		i = 0;
		while (ast->args[i])
			free(ast->args[i++]);
		free(ast->args);
	}
	if (ast->infile)
		free(ast->infile);
	if (ast->outfile)
		free(ast->outfile);
	if (ast->heredoc)
		free(ast->heredoc);
	if (ast->heredoc_list)
		free_heredoc_list(ast->heredoc_list);
}

void	free_ast(t_cmd *ast)
{
	t_cmd	*next;
	t_cmd	*left;
	t_cmd	*right;

	while (ast)
	{
		left = ast->left;
		right = ast->right;
		next = ast->next;
		free_ast_content(ast);
		free(ast);
		free_ast(left);
		free_ast(right);
		ast = next;
	}
}

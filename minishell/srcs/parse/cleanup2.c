/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:43:44 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 23:03:01 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_ast(t_cmd *ast)
{
	if (!ast)
		return ;
	
	if (ast->args)
		free_args(ast->args);
	if (ast->infile)
	{
		free(ast->infile);
		ast->infile = NULL;
	}
	if (ast->outfile)
	{
		free(ast->outfile);
		ast->outfile = NULL;
	}
	if (ast->heredoc)
	{
		free(ast->heredoc);
		ast->heredoc = NULL;
	}
	if (ast->heredoc_list)
	{
		free_heredoc_list(ast->heredoc_list);
		ast->heredoc_list = NULL;
	}
		
	free_ast(ast->left);
	free_ast(ast->right);
	free_ast(ast->next);
	free(ast);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:43:44 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 11:43:48 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_ast(t_cmd *ast)
{
	int	i;

	if (!ast)
		return ;
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
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	if (ast->next)
		free_ast(ast->next);
	free(ast);
}

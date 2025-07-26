/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:43:44 by bozil             #+#    #+#             */
/*   Updated: 2025/07/26 17:12:39 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_ast(t_cmd *ast)
{
	int	i;

	if (!ast || ast->freed)
		return ;
	ast->freed = 1;
	if (ast->args)
	{
		i = 0;
		while (ast->args[i])
		{
			free(ast->args[i]);
			i++;
		}
		free(ast->args);
	}
	free(ast->infile);
	free(ast->outfile);
	free(ast->heredoc);
	free_ast(ast->left);
	free_ast(ast->right);
	free_ast(ast->next);
	free(ast);
}

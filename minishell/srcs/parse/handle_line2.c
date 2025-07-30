/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:54:21 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 16:59:31 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		ft_putstr_fd("  ", 1);
		i++;
	}
}

static void	print_file_redirect(char *file, char *prefix, int depth, int append)
{
	print_indent(depth);
	ft_putstr_fd(prefix, 1);
	ft_putstr_fd(file, 1);
	if (append)
		ft_putstr_fd(" (append)", 1);
	ft_putstr_fd("\n", 1);
}

static void	print_redirections(t_cmd *node, int depth)
{
	if (node->infile)
		print_file_redirect(node->infile, "INPUT: ", depth, 0);
	if (node->outfile)
		print_file_redirect(node->outfile, "OUTPUT: ", depth, node->append);
	if (node->heredoc)
		print_file_redirect(node->heredoc, "HEREDOC: ", depth, 0);
}

static void	print_command_node(t_cmd *node, int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		ft_putstr_fd("  ", 1);
		i++;
	}
	ft_putstr_fd("COMMAND: ", 1);
	if (node->args && node->args[0])
	{
		i = 0;
		while (node->args[i])
		{
			ft_putstr_fd("'", 1);
			ft_putstr_fd(node->args[i], 1);
			ft_putstr_fd("' ", 1);
			i++;
		}
	}
	ft_putstr_fd("\n", 1);
}

void	print_ast(t_cmd *node, int depth)
{
	int	i;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		print_command_node(node, depth);
		print_redirections(node, depth);
	}
	else if (node->type == NODE_PIPELINE)
	{
		i = 0;
		while (i < depth)
		{
			ft_putstr_fd("  ", 1);
			i++;
		}
		ft_putstr_fd("PIPELINE:\n", 1);
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
}

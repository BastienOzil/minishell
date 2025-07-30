/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 22:26:54 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 22:52:03 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_heredoc	*create_heredoc_node(const char *delimiter)
{
	t_heredoc	*new_node;
	char		*delim_copy;

	if (!delimiter)
		return (NULL);
	new_node = malloc(sizeof(t_heredoc));
	if (!new_node)
		return (NULL);
	delim_copy = (char *)delimiter;
	new_node->delimiter = ft_strdup(delim_copy);
	if (!new_node->delimiter)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	add_heredoc_to_list(t_cmd *node, const char *delimiter)
{
	t_heredoc	*new_heredoc;
	t_heredoc	*current;

	if (!node || !delimiter)
		return ;
	new_heredoc = create_heredoc_node(delimiter);
	if (!new_heredoc)
		return ;
	if (!node->heredoc_list)
	{
		node->heredoc_list = new_heredoc;
		return ;
	}
	current = node->heredoc_list;
	while (current->next)
		current = current->next;
	current->next = new_heredoc;
}

void	free_heredoc_list(t_heredoc *list)
{
	t_heredoc	*current;
	t_heredoc	*next;

	current = list;
	while (current)
	{
		next = current->next;
		if (current->delimiter)
			free(current->delimiter);
		free(current);
		current = next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:10:51 by bozil             #+#    #+#             */
/*   Updated: 2025/07/29 11:40:25 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
		|| c == '"' || c == '\'' || c == '$');
}

t_cmd	*linearize_pipeline(t_cmd *ast)
{
	t_cmd	*list;
	t_cmd	*tail;

	if (!ast)
		return (NULL);
	if (ast->type != NODE_PIPELINE)
		return (ast);
	list = linearize_pipeline(ast->left);
	tail = list;
	while (tail && tail->next)
		tail = tail->next;
	tail->next = linearize_pipeline(ast->right);
	return (list);
}

void	print_cmd_not_found(const char *cmd)
{
	int	tty_fd;

	errno = ENOENT;
	tty_fd = open("/dev/tty", O_WRONLY);
	if (tty_fd != -1)
		dup2(tty_fd, STDERR_FILENO);
	puppetmaster_perror(cmd);
	exit(127);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

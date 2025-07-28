/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:01 by bozil             #+#    #+#             */
/*   Updated: 2025/07/28 11:24:03 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:01 by bozil             #+#    #+#             */
/*   Updated: 2025/07/24 14:58:03 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirections(t_cmd *cmd)
{
	if (cmd->infile)
	{
		if (exec_input_redirection(cmd) == -1)
			return (-1);
	}
	else if (cmd->heredoc)
		exec_heredoc(cmd);
	if (cmd->append)
	{
		if (exec_append_redirection(cmd) == -1)
			return (-1);
	}
	else if (cmd->outfile)
	{
		if (exec_output_redirection(cmd) == -1)
			return (-1);
	}
	return (0);
}

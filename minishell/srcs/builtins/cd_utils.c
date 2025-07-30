/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurelia <aurelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:58:31 by bozil             #+#    #+#             */
/*   Updated: 2025/07/30 09:46:55 by aurelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_cd_error(char *path)
{
	write(2, "minishell: cd: ", 16);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	perror(NULL);
}

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	return (S_ISDIR(sb.st_mode));
}

int	count_args_cd(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

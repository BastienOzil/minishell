#include "../includes/minishell.h"

void	handle_redirections(t_cmd *cmd)
{
	if (cmd->infile)
		exec_input_redirection(cmd);
	else if (cmd->heredoc)
		exec_heredoc(cmd);
	if (cmd->append)
		exec_append_redirection(cmd);
	else if (cmd->outfile)
		exec_output_redirection(cmd);
}

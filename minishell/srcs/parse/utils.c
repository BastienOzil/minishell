#include "../includes/minishell.h"

// Vérifie si c'est un caractère d'espacement
int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

// Vérifie si c'est un caractère spécial
int is_special(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&' || 
            c == '(' || c == ')' || c == '"' || c == '\'' || c == '$');
}

//_____ajout de cette fonctin pour convertir les ast en liste chainée
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

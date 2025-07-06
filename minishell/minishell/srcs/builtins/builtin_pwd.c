#include "../../includes/minishell.h"

int pwd_builtin(void)
{
    char *cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        puppetmaster_perror("pwd");
        return (1);
    }
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
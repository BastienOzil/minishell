#include "../../includes/minishell.h"

//check if variable exist in env
int is_var_exist(char *var, char ***envp)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(var);

    while((*envp)[i])
    {
        if((ft_strncmp(var,(*envp)[i], len) == 0) && (*envp)[i][len] == '=')
        {
           return (1);
        }
        i++;
    }
    return (0);
}

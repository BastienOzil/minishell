#include "../includes/minishell.h"
#include "../animation/includes/animation.h"

int main(void)
{
    char *line;
    
    launch_animation(); // lance le programme d'animation
    
    while (1)
    {
        write(1, "\033[1;32m", 7);
        slow_type_prompt("[Puppet~master]> ");
        write(1, "\033[0m", 4);
        
        line = readline("");
        
        int fd = open("fichier_qui_nexiste_pas.txt", O_RDONLY);
        if (fd < 0)
            puppetmaster_perror("open");
            
        if (!line)
            break;
        if (*line)
            add_history(line);
        handle_line(line);
        free(line);
    }
    printf("exit\n");
    return (0);
}

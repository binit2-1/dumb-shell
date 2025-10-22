#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <linux/limits.h>

#include "banner.h"
#include "input.h"




void dumb_loop(void)
{
    char *line;
    char **args;
    int status = 1;
    do
    {
        char pwd[PATH_MAX];
        if (getcwd(pwd, sizeof(pwd)) != NULL)
        {
            printf("%s $ ", pwd);
        }
        else
        {
            perror("getcwd() error");
        }
        
        line = dumb_read();
        

    } while (status);
}

int main(void)
{
    print_banner();
    dumb_loop();
    return 0;
}
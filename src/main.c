#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <linux/limits.h>

#include "banner.h"
#include "input.h"
#include "splitline.h"
#include "execute.h"
#include "prompt.h"

void dumb_loop(void)
{
    char *line;
    char **args;
    int status;
    int last_status = 0;
    do
    {
        lsh_print_prompt(last_status);

        line = dumb_read();
        args = dumb_split_line(line);
        status = dumb_execute(args);

        last_status = status;

        free(line);
        free(args);
        

    } while (status);
}

int main(void)
{
    print_banner();
    dumb_loop();
    return 0;
}
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
#include "trie.h"


void loadHistory(TrieNode* root){
    char path[PATH_MAX];
    char *home_directory = getenv("HOME");
    if(home_directory == NULL){
        return;
    }
    snprintf(path, sizeof(path), "%s/.dumb_shell_history", home_directory);
    FILE* file = fopen(path, "r");
    if(file == NULL){
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        insert(root, buffer);
    }
}

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
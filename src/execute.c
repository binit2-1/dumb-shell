#include <stdio.h>
#include <string.h>
#include "builtins.h"
#include "external.h"

int dumb_execute(char **args){
    if(args[0] == NULL){
        return 1; // Empty command
    }

    for(int i = 0; i < dumb_num_builtins(); i++){
        if(strcmp(args[0], builtins_cmds[i]) == 0){
            return builtin_func[i](args);
        }
    }

    return external_cmd(args); // Command not found then execute external command
}
#include <stdio.h>
#include <unistd.h>

/*========== Builtin Commands =========*/
char *builtins_cmds[] = {
    "cd",
    "help",
    "exit"
};

/*========== Calculates Number of Builtins =========*/
int dumb_num_builtins() {
    return sizeof(builtins_cmds) / sizeof(char *);
}


/* ========= Builtin Commands ========= */

/* change directory command */
int dsh_cd(char **args){
    if (args[1] == NULL) {
        fprintf(stderr, "dsh: cd: missing argument(maybe a directory name?)\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("dsh");
        }
    }
    return 1;
}

/* help command */
int dsh_help(char **args) {
    (void)args; // Silences the "unused variable" warning

    printf("\n");
    printf("You're using dumb-shell and you need... `help`?\n");
    printf("Alright, fine. I guess I can't expect everyone to be a genius...\n\n");

    printf("This shell was (allegedly) \"made by a dumb developer,\" so let's keep it simple.\n");
    printf("\n");
    
    printf("--- My Amazing Built-in Commands ---\n");
    printf("  help\t\t- You're lookin' at it. Try to keep up.\n");
    printf("  cd [dir]\t- Changes your directory. You know, so you can get lost somewhere new.\n");
    printf("  exit\t\t- Lets you escape from all this... 'dumb'-ness. (Or just hit Ctrl+D, whatever).\n");
    printf("\n");

    printf("--- Everything Else ---\n");
    printf("For any *actual* commands (like `ls`, `grep`, `rm -rf /` -- *don't try that*),\n");
    printf("I'll pass the buck to the OS. I'm smart enough to know when to delegate.\n\n");
    
    printf("Now, go run something.\n\n");

    return 1; 
}

/* exit command */
int dsh_exit(char **args) {
    (void)args; // Silences the "unused variable" warning
    return 0; 
}

/*==========Array of function pointers for builtin commands =========*/
int (*builtin_func[])(char **) = {
    &dsh_cd,
    &dsh_help,
    &dsh_exit
};

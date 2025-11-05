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
    printf("Ugh. You're using **barely-alive shell**... and you actually need `help`?\n");
    printf("Sigh. Fine. I'll stop... *not*... working for a second to explain.\n");
    printf("Honestly, I'm as surprised as you are that this even launched.\n");
    printf("\n");
    
    printf("--- The Few Things I Can (Probably) Do ---\n");
    printf("  help\t\t- You're staring at it. This is peak performance. Impressed?\n");
    printf("  cd [dir]\t- Go on, `cd` somewhere. Maybe you'll find a shell with more ambition.\n");
    printf("  exit\t\t- The sweet release. Lets you put this poor thing out of its misery.\n");
    printf("\n");

    printf("--- Everything Else ---\n");
    printf("Look, for anything *actually* useful (like `ls`, `grep`, `type`, etc.),\n");
    printf("I just pawn the work off on the REAL operating system. Don't expect *me* to do it.\n\n");
    
    printf("Are we done here? Good.\n\n");

    return 1; // 1 means "keep running the shell"
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

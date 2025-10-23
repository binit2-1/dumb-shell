#ifndef BUILTINS_H
#define BUILTINS_H

/* variable declarations (defined in src/builtins.c) */
extern char *builtins_cmds[];
extern int (*builtin_func[])(char **);

/* functions */
int dumb_num_builtins(void);
int dsh_cd(char **args);
int dsh_help(char **args);
int dsh_exit(char **args);

#endif /* BUILTINS_H */

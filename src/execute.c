#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "execute.h"

#define DSH_TOKBUF_SIZE 1024
#define DSH_TOK_DELIM " \t\r\n\a"

char **dumb_split_line(char *line){
    int bufsize = DSH_TOKBUF_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "dumb-shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DSH_TOK_DELIM);
    while(token !=NULL){
        tokens[position++] = token;
        
        if(position >= bufsize){
            bufsize += DSH_TOKBUF_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if(!tokens){
                fprintf(stderr, "dumb-shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, DSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
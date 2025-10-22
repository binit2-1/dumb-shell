#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#define DSH_BUFFER_SIZE 1024

char *dumb_read(void){
    int bufsize = DSH_BUFFER_SIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if(!buffer){
        fprintf(stderr, "dumb-shell: allocation error\n");
        exit(EXIT_FAILURE);
    }
    while(1){
        c = getchar();

        if(c == EOF ){
            exit(EXIT_SUCCESS);
        } else if( c == '\n'){
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if(position >= bufsize){
            bufsize += DSH_BUFFER_SIZE;
            buffer = realloc(buffer, bufsize);
            if(!buffer){
                fprintf(stderr, "dumb-shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
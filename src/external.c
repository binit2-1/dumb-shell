#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


int external_cmd(char **args){
    pid_t pid;
    int status;

    // new child process
    pid= fork();
    //child process created
    if(pid == 0){
        //valid command not found in path
        if(execvp(args[0], args) == -1){
            perror("dsh");
        }
        exit(EXIT_FAILURE); 
    } else if(pid < 0){
        //child not created
        perror("dsh");
    } else {
        //the parent process waits while the child process executes after executing pid stores the process ID of the child process
        while(1){
            pid_t wpid = waitpid(pid, &status, WUNTRACED); //status stores the exit code of the child process
            if(wpid == -1){ //if exit code is -1 then error occurred
                if(errno == EINTR) continue;
                perror("waitpid");
                break;  
            }
            // if the child process has exited or was terminated by a signal, break the loop or exited by exit command 
            if((WIFEXITED(status) || WIFSIGNALED(status))){
                break;
            }
        }
    }
    return 1;
}
///////////////////////////////////////////////////////////////////////////////
// Authors:         Rohit Kumar Sharma, M. Giri Prasanna
// NetID:           rsharma54, mugundakrish
// CSLogin:         rsharma, mgiriprasanna
// Email:           rsharma@cs.wisc.edu, mugundakrish@wisc.edu
// Created on:      October 25, 2018
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "text_parsing.h"
#include "build_spec_graph.h"
#include "build_spec_repr.h"

void execute_program(MakeNode *node) {
    command *commands = node->rules;
    while (commands != NULL) {
        pid_t parent = getpid();
        pid_t pid = fork();

        if (pid == -1) {
            fprintf(stderr, "Failed to fork()\n");
        }
        else if (pid > 0) {
            // Parent proc: wait for child
            int status;
            if (waitpid(pid, &status, 0) > 0) {
                if (WIFEXITED(status) && !WEXITSTATUS(status))  
                fprintf(stderr, "program execution successfull\n"); 
                else if (WIFEXITED(status) && WEXITSTATUS(status)) { 
                    if (WEXITSTATUS(status) == 127) { 
    
                        // execv failed 
                        fprintf(stderr, "execv failed\n"); 
                    } 
                    else 
                        fprintf(stderr, "program terminated normally,"
                        " but returned a non-zero status\n");                 
                } 
                else 
                fprintf(stderr, "Could not wait for the child process. The program could not be terminated normally.\n"); 
            }
            else {
                fprintf(stderr, "waitpid() returned with a failure status.\n");
            }
        }
        else {
            // Child proc
            // char *argv[4] = {"echo", "Hello,", "World!", NULL};
            // execvp("echo", argv);
            char **args = tokenize_string(commands->rule);
            execvp(args[0], args);
            fprintf(stderr, "Exec should never return, but it returned with a failure\n");
            exit(1);    // To avoid the fork bomb
        }
        commands = commands->next;
    }
}

int main() {
    MakeNode *temp = (MakeNode *) malloc(sizeof(MakeNode));
    temp->name = "target";
    command *commands = create_command("echo Hello, World");
    commands->next = create_command("echo Done");
    temp->rules = commands;
    execute_program(temp);

    return 0;
}
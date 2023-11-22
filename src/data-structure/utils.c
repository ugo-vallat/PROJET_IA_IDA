#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <errno.h>
#include <stdbool.h>


void erreur(char* msg, int exit_val) {
    if(errno)
        perror(msg);
    else
        fprintf(stderr, "%s\n", msg);
    exit(exit_val);
}

void testArgNull(void* arg, char* nom_fun) {
    if(arg == NULL) {
        fprintf(stderr, "[in %s] arg NULL\n", nom_fun);
        exit(EXIT_FAILURE);
    }       
}
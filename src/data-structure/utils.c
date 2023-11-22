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

void testCoupEstValide(Coup c, char* fun) {
    bool test = true;
    test &= c.id >= 1;
    test &= c.id <= 9;
    test &= c.p_src >= 0;
    test &= c.p_src <= 3;
    test &= c.p_dst >= 0;
    test &= c.p_dst <= 3; 
    if(!test) {
        fprintf(stderr, "[in %s] Coup invalide (id = %d, p_src = %d, p_dst = %d, weight = %d)\n",
             fun, c.id, c.p_src, c.p_dst, c.weight);
        exit(EXIT_FAILURE);
    }
}
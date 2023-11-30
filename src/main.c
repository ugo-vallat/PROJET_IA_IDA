#include <signal.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include "data-structure/state.h"
#include "data-structure/list.h"
#include "data-structure/stack.h"
#include "modules/modules_utils.h"
#include "modules/depth.h"
#include "../test/dataTest.h"



void printStackTrace() {
    void* buffer[64];
    int nbv = backtrace(buffer, sizeof(buffer));
    char** strings = backtrace_symbols(buffer, nbv);
    for (int i = 1; i<nbv; i++) { // démarre à 1 pour ignorer l'appel de cette fonction
        fprintf(stderr, "%s\n", strings[i]);
    }
    free(strings);
}


void segfaultHandler(int sig) {
    (void)sig;
    printf("########## SEGFAULT ##########\n\n");
    printStackTrace();
    exit(1);
}


int main(void){
    
    printf("    <+>-------- DONE \n");
    return 0;

}

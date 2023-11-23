#include <signal.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include "data-structure/state.h"
#include "data-structure/list.h"
#include "data-structure/stack.h"
#include "modules/modules_utils.h"
#include "modules/depth.h"

int m1_start[4][4] = {
    {0,0,0,0},
    {3,1,2,3},
    {3,4,5,6},
    {3,7,8,9}
};

int m1_end[4][4] = {
    {3,6,3,9},
    {2,1,2,0},
    {2,4,5,0},
    {2,7,8,0}
};

int m2_start[4][4] = {
    {3,1,5,9},
    {2,2,6,0},
    {2,3,7,0},
    {2,4,8,0}
};

int m2_end[4][4] = {
    {3,6,1,7},
    {2,2,8,0},
    {2,3,0,0},
    {2,4,9,5}
};

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



void loadMatrixInState(State *s, int m[4][4]) {
    for(unsigned i = 0; i < 4; i++)
        for(unsigned j = 0; j < 4; j++)
            s->matrix[i][j] = m[i][j];
}

void test_state() {
    State e;
    e.matrix[0][0] = 3;e.matrix[1][0] = 3;e.matrix[2][0] = 3;e.matrix[3][0] = 0;
    e.matrix[0][1] = 1;e.matrix[1][1] = 2;e.matrix[2][1] = 3;e.matrix[3][1] = 0;
    e.matrix[0][2] = 4;e.matrix[1][2] = 5;e.matrix[2][2] = 6;e.matrix[3][2] = 0;
    e.matrix[0][3] = 7;e.matrix[1][3] = 8;e.matrix[2][3] = 9;e.matrix[3][3] = 0;

    Move mouvements_possibles[9];

    Move m;
    m.id = 7;
    m.weight = 1;
    m.stem_src = 0;
    m.stem_dst = 3;
    Action a = applyMove(e,m);
    displayState(a.before);
    displayState(a.after);
    e = a.after;
    findMoves(e,mouvements_possibles);
    for(int i = 0; i< 9; i++){
      if (mouvements_possibles[i].id != -1){
        displayMove(mouvements_possibles[i]);
      }
    }
    m.id = 4;
    m.weight = 1;
    m.stem_src = 0;
    m.stem_dst = 3;
    a = applyMove(e,m);
    displayState(a.before);
    displayState(a.after);
}


void test_list() {
    List *l = createList(8);
    Action a;
    State e;
    loadMatrixInState(&e, m1_start);
    Move m = {6,1,2,0};

    a = applyMove(e, m);
    Action *s = malloc(sizeof(Action));
    copyAction(&a, s);
    displayAction(s);
    for(int i = 0; i < 64; i++) {
        printf("size = %d\n", listSize(l));
        listAdd(l, s);
    }
    listDisplay(l);
}


void test_depth() {
    State s_start, s_end;
    loadMatrixInState(&s_start, m1_start);
    loadMatrixInState(&s_end, m1_end);

    ResSearch* res;
    displayState(s_start);
    displayState(s_end);
    res = search_depth(s_start, s_end, 5);
    displayResSearch(res);
    showGameAnimation(res, s_start);
    deleteResSearch(res);
    
}


int main(void){
    sigset_t mask;
    sigfillset(&mask);

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_mask = mask;
    act.sa_handler = segfaultHandler;

    sigaction(SIGSEGV, &act, NULL);

    

    // test_list();
    test_depth();



    return 0;

}

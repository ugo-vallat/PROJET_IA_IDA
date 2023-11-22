#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "state.h"

void afficherState(State e){
    for(int i = 3;i>0; i--){
        printf("| %d  %d  %d  %d |\n", e.matrix[0][i], e.matrix[1][i], e.matrix[2][i], e.matrix[3][i]);
    }
    printf("______________\n");
}

Move* findMoves(State e){
    Move[9] moves;
    Move m;
    int moves_iterator = 0;
    for(int i=0; i<4; i++){
        (if e.matrix[i][0] != 0)
        for(int j = 0; j < 4; j++){
            (if e.matrix[j][0] != 3 && j != i ){
                m.id = e.matrix[i][e.matrix[i][0]];
                m.weight = 1;
                m.stem_src = i+1;
                m.stem_dest = j+1;
                moves[moves_iterator] = m;
                moves_iterator++;
            }
        }
    }
    return moves;
    
}

MoveState applyMove(State s, Move m){
    MoveState ms;
    s.matrix[m.stem_dest][s.matrix[m.stem_dest][0] + 1] = m.id;
    s.matrix[m.stem_src][s.matrix[m.stem_src][0]] = 0
    s.matrix[m.stem_src][0]--;
    ms.move = m;
    ms.result = s;
    return ms;

}
bool estBut(State s, State but){
    if (egal(s,but)){
        return true;
    }
    else{
        return false;
    }
}

bool egal(State s1, State s2){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (s1.matrix[i][j] != s2.matrice2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void opPoss(State s, MoveState *res, int *nb_move){
    //TODO
}


void testMoveIsValid(Move m, char* fun_name) {
    bool test = true;
    test &= m.id >= 1;
    test &= m.id <= 9;
    test &= m.stem_src >= 0;
    test &= m.stem_src <= 3;
    test &= m.stem_dst >= 0;
    test &= m.stem_dst <= 3; 
    if(!test) {
        fprintf(stderr, "[in %s] Coup invalide (id = %d, stem_src = %d, stem_dst = %d, weight = %d)\n",
             fun_name, m.id, m.stem_src, m.stem_dst, m.weight);
        exit(EXIT_FAILURE);
    }
}

bool isMovePossible(State s, Move m){
    //TODO
    return null;
}


void testStemValid(int stem, char* fun_name) {
    if (0 > stem || 3 < stem) {
        fprintf(stderr, "[in %s] Argument stem invalide", fun_name);
        exit(EXIT_FAILURE);
    }
}
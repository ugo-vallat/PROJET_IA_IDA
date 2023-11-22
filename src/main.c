#include "data-structure/state.h"

int main(void){
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
    afficherState(a.before);
    afficherState(a.after);
    e = a.after;
    findMoves(e,mouvements_possibles);
    for(int i = 0; i< 9; i++){
      if (mouvements_possibles[i].id != -1){
        afficherMove(mouvements_possibles[i]);
      }
    }
    m.id = 4;
    m.weight = 1;
    m.stem_src = 0;
    m.stem_dst = 3;
    a = applyMove(e,m);
    afficherState(a.before);
    afficherState(a.after);

    return 0;

}

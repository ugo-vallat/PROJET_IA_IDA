#include "data-structure/state.h"

int main(void){
    State e;
    e.matrix[0][0] = 3;e.matrix[1][0] = 3;e.matrix[2][0] = 3;e.matrix[3][0] = 0;
    e.matrix[0][1] = 1;e.matrix[1][1] = 2;e.matrix[2][1] = 3;e.matrix[3][1] = 0;
    e.matrix[0][2] = 4;e.matrix[1][2] = 5;e.matrix[2][2] = 6;e.matrix[3][2] = 0;
    e.matrix[0][3] = 7;e.matrix[1][3] = 8;e.matrix[2][3] = 9;e.matrix[3][3] = 0;

    AfficherState(e);

    return 0;

}

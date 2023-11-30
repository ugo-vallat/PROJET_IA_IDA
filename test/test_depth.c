#include <stdio.h>
#include "../src/data-structure/state.h"
#include "../src/modules/depth.h"
#include "dataTest.h"
#include <unistd.h>

void test_1(int id, int depth) {
    State start;
    State end;
    ResSearch *res;

    getEtatTest(id, &start, &end);
    displayState(start);
    displayState(end);
    res = search_depth(start, end, depth);
    displayResSearch(res);
    sleep(1);
    showGameAnimation(res, start);
    deleteResSearch(res);

}



int main() {
    int id,depth;

    printf("Numero test : ");
    scanf("%d", &id);
    printf("Profondeur max : ");
    scanf("%d", &depth);

    test_1(id,depth);

    return 0;
}
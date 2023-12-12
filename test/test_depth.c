#include <stdio.h>
#include "../src/data-structure/state.h"
#include "../src/modules/depth.h"
#include "dataTest.h"
#include <unistd.h>

State start, end;
int max_depth;

void test_depth_main() {
    ResSearch *res;

    res = search_depth(start, end, max_depth);

    displayResSearch(res);
    sleep(1);
    showGameAnimation(res);
    deleteResSearch(res);
}

void test_speed() {
    ResSearch *res;
    double mean = 0;

    unsigned nb_test = 10;

    /* calcul de la moyenne */
    for(unsigned i = 1; i < nb_test; i++) {
        res = search_depth(start, end, max_depth);
        mean += res->time;
        printf("\n");
        deleteResSearch(res);
    }

    /* affichage des performances */
    printf("\n\n ┏━━━━━━━━━━ PERFORMANCES :\n");
    printf(" ┃ Nombre exécutions    : %d\n", nb_test);
    printf(" ┃ Temps moyen exécution: %f\n", mean/nb_test);
    printf(" ┗━━━━━━\n");
}

int main(int argc, const char* argv[]) {
    if(argc != 4) {
        error("usage : <id_start> <id_end> <max_depth>", 1);
    }
    int id_start, id_end;

    sscanf(argv[1], "%d", &id_start);
    getEtatStart(id_start, &start);
    sscanf(argv[2], "%d", &id_end);
    getEtatEnd(id_end, &end);
    sscanf(argv[3], "%d", &max_depth);

    displayState(start);
    displayState(end);
    

    test_depth_main();
    // test_speed();

    return 0;
}
#include <stdio.h>
#include "../src/data-structure/state.h"
#include "../src/modules/ida.h"
#include "dataTest.h"
#include "../src/modules/ida_param.h"
#include <stdlib.h>
#include <unistd.h>

State start, end;
fun_heuristic fun_h;
fun_move_cost fun_mc;

void test_ida_main() {
    ResSearch *res;

    res = ida(start, end, fun_h, fun_mc);

    displayResSearch(res);
    sleep(1);
    showGameAnimation(res);
    deleteResSearch(res);
}

void test_speed() {
    ResSearch *res;
    double mean = 0;

    unsigned nb_test = 10;

    /* affichage des résultats de la recherche */
    res = ida(start,end, fun_h, fun_mc);
    mean += res->time;
    displayResSearch(res);
    deleteResSearch(res);

    /* calcul de la moyenne */
    for(unsigned i = 1; i < nb_test; i++) {
        res = ida(start, end, fun_h, fun_mc);
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
    if(argc != 5) {
        error("usage : <id_start> <id_end> <id_h> <id_mc>", EXIT_FAILURE);
    }
    int id_start, id_end, id_h, id_mc;

    sscanf(argv[1], "%d", &id_start);
    getEtatStart(id_start, &start);
    sscanf(argv[2], "%d", &id_end);
    getEtatEnd(id_end, &end);
    sscanf(argv[3], "%d", &id_h);
    fun_h = getFunHeuristic(id_h);
    sscanf(argv[4], "%d", &id_mc);
    fun_mc = getFunMoveCost(id_mc);

    displayState(start);
    displayState(end);
    

    test_ida_main();
    // test_speed();

    return 0;
}
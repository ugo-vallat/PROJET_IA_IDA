#include <stdio.h>
#include "../src/data-structure/state.h"
#include "../src/modules/depth.h"
#include "dataTest.h"
#include <unistd.h>

void test_depth_main(int id, int depth) {
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

void test_speed(int id, int depth) {
    State start;
    State end;
    ResSearch *res;
    double mean = 0;

    unsigned nb_test = 10;

    /* récupération jeu de test */
    getEtatTest(id, &start, &end);
    displayState(start);
    displayState(end);

    /* affichage des résultats de la recherche */
    res = search_depth(start, end, depth);
    mean += res->time;
    displayResSearch(res);
    deleteResSearch(res);

    /* calcul de la moyenne */
    for(unsigned i = 1; i < nb_test; i++) {
        res = search_depth(start, end, depth);
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



int main() {
    int id,depth;

    printf("Numero test : ");
    scanf("%d", &id);
    printf("Profondeur max : ");
    scanf("%d", &depth);

    // test_depth_main(id,depth);
    test_speed(id, depth);

    return 0;
}
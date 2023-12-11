#include <stdio.h>
#include "../src/data-structure/state.h"
#include "../src/modules/ida.h"
#include "dataTest.h"
#include <unistd.h>

void test_ida_main(int id) {
    State start;
    State end;
    ResSearch *res;

    getEtatTest(id, &start, &end);
    displayState(start);
    displayState(end);
    res = ida(start, end);
    displayResSearch(res);
    sleep(1);
    showGameAnimation(res, start);
    deleteResSearch(res);
}

void test_speed(int id) {
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
    res = ida(start,end);
    mean += res->time;
    displayResSearch(res);
    deleteResSearch(res);

    /* calcul de la moyenne */
    for(unsigned i = 1; i < nb_test; i++) {
        res = ida(start, end);
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
    int id;

    printf("Numero test : ");
    scanf("%d", &id);
    test_ida_main(id);
    test_speed(id);

    return 0;
}
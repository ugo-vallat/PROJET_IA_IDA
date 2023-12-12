#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "modules_utils.h"


#define STRING_BUFF_SIZE 64

/*
    ===================
    ===  AFFICHAGE  ===
    ===================
*/

char* algoToString(Algo a) {
    char *buff = malloc(sizeof(char)*STRING_BUFF_SIZE);
    switch ((int)a) {
        case DEPTH:
            snprintf(buff, STRING_BUFF_SIZE, "recherche en profondeur bornée");
            break;
        case IDA:
            snprintf(buff, STRING_BUFF_SIZE, "IDA*");
            break;
        default:
            snprintf(buff, STRING_BUFF_SIZE, "< unknown >");
            break;
    }
    return buff;
}

void displayResSearch(ResSearch *res) {
    char* algo;
    printf("\n ┏━━━━━━━━━━━━━━━━━━━━ RESULTAT :\n");
    algo = algoToString(res->algo);
    printf(" ┃ Algo               : %s\n", algo);
    free(algo);
    printf(" ┃ Depth              : %d\n", res->depth);
    printf(" ┃ Chemin trouvé      : %s\n", (res->found?"oui":"non"));
    printf(" ┃ Nombre itérations  : %u\n", res->nb_ite);
    printf(" ┃ Noeuds créés       : %u\n", res->nb_state_created);
    printf(" ┃ Noeuds explorés    : %u\n", res->nb_state_processed);
    printf(" ┃ Temps d'exécution  : %f\n", res->time);
    if(!res->found) return;
    printf(" ┃ Taille du chemin   : %d\n", res->size_path);
    printf(" ┃ Coût               : %d\n", res->cost);
    printf(" ┃ Chemin             :\n");
    Move m;
    for(unsigned i = 0; i < res->size_path; i++) {
        m = res->path[i];
        printf(" ┃   %2d-  id %2d : (%d -> %d) - %d\n",m.mouv_index, m.id, m.stem_src, m.stem_dst, m.weight);
    }
    printf(" ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n\n");
}

void loadingBarDepth(int size, int max, int ite) {
    int i = 0;
    for(; i < size && i < max; i++)
        printf("=");
    printf("|");
    for(; i < max; i++)
        printf(" ");
    printf("%-8d\r", ite);fflush(stdout);
}

void showGameAnimation(ResSearch *res) {
    if(!res->found) return;
    __useconds_t time_wait = 1000000;
    displayState(res->initial_state);

    /* si chemin vide on arrête */
    if(res->size_path <= 0) return;

    /* affichage premier mouvement  */
    printf("\033[4A\r");
    usleep(time_wait);
    Action act = applyMove(res->initial_state, res->path[0]);
    displayState(act.after);
    printf("\033[4A\r");
    usleep(time_wait);

    /* affichage mouvements suivants */
    for(unsigned i = 1; i < res->size_path; i++) {
        act = applyMove(act.after, res->path[i]);
        displayState(act.after);
        printf("\033[4A\r");
        usleep(time_wait);
    }
    printf("\033[5B");
}

/*
    ===================
    ===  ResSearch  ===
    ===================
*/

ResSearch* createResSearch(Algo algo, unsigned size_path_max) {
    ResSearch *res = malloc(sizeof(ResSearch));
    res->algo = algo;
    res->depth = 0;
    res->cost = 0;
    res->found = false;
    res->nb_ite = 0;
    res->nb_state_created = 0;
    res->nb_state_processed = 0;
    stateEmpty(&(res->initial_state));
    res->path = malloc(sizeof(Action)*size_path_max);
    res->size_path = 0;
    res->time = 0;
    return res;
}

void deleteResSearch(ResSearch *res) {
    free(res->path);
    free(res);
}
#include <signal.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "data-structure/state.h"
#include "data-structure/list.h"
#include "data-structure/stack.h"
#include "modules/modules_utils.h"
#include "modules/depth.h"
#include "modules/ida.h"
#include "modules/ida_param.h"
#include "../test/dataTest.h"
#include "modules/modules_utils.h"
#include "data-structure/utils.h"


Algo getAlgoFromUser() {
    int res;
    printf("\n\t 1 - Profondeur bornée\n");
    printf("\t 2 - IDA* \n");
    printf("Choisir algorithme :");
    scanf("%d",&res);
    if(res != DEPTH && res != IDA)
        error("Choix de l'algorithme invalide ", EXIT_FAILURE);
    return res;
}

State getStateStartFromUser() {
    int res;
    State start;
    printf("\nliste états départ : {1,...,7}\n");
    printf("Choisir départ :");
    scanf("%d",&res);
    if(res < 1 || res > 7)
        error("Choix de l'état départ invalide ", EXIT_FAILURE);
    getEtatStart(res, &start);
    return start;
}

State getStateEndFromUser() {
    int res;
    State end;
    printf("\nliste états arrivée : {1,...,15}\n");
    printf("Choisir arrivée :");
    scanf("%d",&res);
    if(res < 1 || res > 15)
        error("Choix de l'état arrivée invalide ", EXIT_FAILURE);
    getEtatEnd(res, &end);
    return end;
}

unsigned getMaxDepthFromUser() {
    int res;
    printf("\nChoisir profondeur max :");
    scanf("%d",&res);
    if(res < 1 )
        error("Choix de la profondeur invalide ", EXIT_FAILURE);
    return res;
}

fun_heuristic getHeuristicFromUser() {
    int res;
    printf("\n\t 1 - Etat mal positionné\n");
    printf("\t 2 - Mal positionné + profondeur\n");
    printf("Choisir heuristique :");
    scanf("%d",&res);
    if(res != H_SIMPLE && res != H_DEPTH)
        error("Choix de l'heuristique invalide ", EXIT_FAILURE);
    return getFunHeuristic(res);
}

fun_move_cost getMoveCostFromUser() {
    int res;
    printf("\n\t 1 - Coup 1\n");
    printf("\t 2 - Coup = id de l'anneau\n");
    printf("Choisir calcul des coups :");
    scanf("%d",&res);
    if(res != C_ONE && res != C_ID)
        error("Choix de l'heuristique invalide ", EXIT_FAILURE);
    return getFunMoveCost(res);
}

int main(){
    

    Algo algo = getAlgoFromUser();

    
    State start = getStateStartFromUser();
    State end = getStateEndFromUser();

    ResSearch *res;

    if(algo == DEPTH) {
        unsigned max_depth = getMaxDepthFromUser();

        displayState(start);
        displayState(end);

        res = search_depth(start, end, max_depth);
    }

    if (algo == IDA) {
        fun_heuristic heuristic = getHeuristicFromUser();
        fun_move_cost move_cost = getMoveCostFromUser();
        
        displayState(start);
        displayState(end);

        res = ida(start, end, heuristic, move_cost);
    }

    

    displayResSearch(res);
    sleep(1);
    printf("ETAT INITIAL:\n\n");
    displayState(start);
    printf("ETAT FINAL:\n\n");
    displayState(end);
    printf("MOUVEMENTS :\n\n");
    showGameAnimation(res, start);
    deleteResSearch(res);

    return 0;
}

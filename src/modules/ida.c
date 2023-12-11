#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "depth.h"
#include "../data-structure/stack.h"
#include "../data-structure/list.h"
#include "../data-structure/state.h"
#include "modules_utils.h"

State goal;
State solution;
unsigned bound;
int infinite = 999999999;


State emptyStateida = {{
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }};


int min(int a, int b) {
    return (a < b) ? a : b;
}


int heuristic(State init){
    int sums = 0;
    for (int i = 0; i < 4; i++)
    {
       int max_depth;
       for(int j = init.matrix[i][0]; j> 1 ; j--){
            max_depth = j;
            if (init.matrix[i][j] != goal.matrix[i][j]){
                sums+= max_depth;
                break;
            }
       } 
    }
    
    return sums;
}



unsigned int fEtat(State init, int g){
    return g + heuristic(init);
}

int cost_movement(State s){
    return 1;
}

void addToPath_ida(List* path, Action* act) {
    /* si à la racine */
    if(act->move.mouv_index == -1) {
        listAdd(path, act);
        return;
    }

    /* cherche le parent de act */
    while(!listEmpty(path) && !equalState(act->before, listLast(path)->after))
        listPop(path);

    /* si auncun parent : echec */
    if(listEmpty(path)) {
        error("Echec ajout au chemin", EXIT_FAILURE);
    }

    /* ajout au chemin */
    listAdd(path, act);
}


bool bounded_depth(List* buff, List* done, List *path, int g, unsigned *created, unsigned *processed, unsigned *ite){
    Action* cur;    /* etat en train d'être traité */
    Action* next_actions = malloc(sizeof(Action)*16); /* actions depuis cur */
    Action tmp_action;
    unsigned path_size;
    int nb_next_actions;
    int newBound = infinite;
    int res_search;

    /* info du programme */
    unsigned nb_created = 0;     /* nombre d'états créés */
    unsigned nb_processed = 0;  /* nombre d'états explorés */
    unsigned nb_ite = 0;            /* nombre d'itérations */

    while (!listEmpty(buff)){
        nb_ite++;
        nb_processed++;
        loadingBarDepth(listSize(path), bound+1, nb_ite);

        /* récupérer prochain élément */
        cur = listPop(buff);

        /* ajouter à la liste des vus */
        listAdd(done, cur);

        /* ajouter au chemin */
        addToPath_ida(path, cur);
        path_size = listSize(path); 

        if (equalState(cur->after, goal)) {
            /* fin */
            solution = cur->after;
            free(next_actions);
            *created = nb_created;
            *processed = nb_processed;
            *ite = nb_ite; 
            return true;
        }
        else if ( path_size < bound + 1) {
            /* récupérer les prochaines actions */
            stateFindNextActions(cur->after, &nb_next_actions, next_actions);
            nb_created+=nb_next_actions;

            /* les ajouter au buffer */
            for(int i = 0; i < nb_next_actions; i++) {
                tmp_action = next_actions[i];
                tmp_action.move.mouv_index = path_size;
                int new_g = g + cost_movement(tmp_action.after); // changer la fonction cost_movement si jamais on implémente les déplacement à différent couts

                /* recherche recherche du nouveau état dans les états déjà traités  */
                res_search = searchElem(done, &tmp_action, equal_action);

                if(fEtat(tmp_action.after,new_g) <= bound && res_search == -1) {
                    /* si jamais rencontré */
                    listAdd(buff, createAction(tmp_action.before, tmp_action.move, tmp_action.after));
                }
                else {
                    newBound = min(newBound,fEtat(tmp_action.after,new_g));
                    nb_processed--;
                }
            }
        }


    }

    free(next_actions);
    *created = nb_created;
    *processed = nb_processed;
    *ite = nb_ite; 

    if (newBound == infinite){
        return true;
    }
    else {
        bound = newBound;
        return false;
    }



}










ResSearch* ida(State initial_state, State goal_gived){


    /* initialisation outils */
    List *buff = createList(STACK_MAX_SIZE);
    List* done = createList(LIST_DONE_SIZE);
    List* path = createList(bound+4);
    goal = goal_gived;
    int g = 0;

    
    /* création racine */
    State state; 
    copyState(&emptyStateida, &state);
    Move mv = {0,0,0,0,-1};
    Action *act = createAction(state, mv, initial_state);
    listAdd(buff, act);
    bound = fEtat(initial_state,g);

    

   /* Initialisation structure résultat*/
    ResSearch *res = createResSearch(IDA, bound+4);

    /* lancement du timer */
    clock_t start, end;
    start = clock();

    while (!(res->found)){
        res->found = bounded_depth(buff, done, path,g,
        &(res->nb_state_created), &(res->nb_state_processed), &(res->nb_ite));
    }

    /* fin du timer */
    end = clock();
    res->time = ((double) (end - start)) / CLOCKS_PER_SEC;

     /* récupérations du chemin */
    res->size_path = listSize(path) -1;
    for(unsigned i = 1; i < listSize(path); i++) {
        copyMove(&(listGet(path, i)->move), &res->path[i-1]);
        res->cost += listGet(path, i)->move.weight;
    }

 /* libération de la mémoire */
    while(!listEmpty(done))
        deleteAction(listPop(done));
    while(!listEmpty(buff)) {
        deleteAction(listPop(buff));
        // stackPop(buff);
    }

    deleteList(&path);
    deleteList(&buff);
    deleteList(&done);
    res->depth = bound;

    if (solution.matrix != NULL){
        return res;
    }
    //return fail;
    return NULL;

}



#include <stdio.h>
#include <stdlib.h>
#include "depth.h"
#include "../data-structure/stack.h"
#include "../data-structure/list.h"
#include "../data-structure/state.h"
#include "modules_utils.h"

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

int fEtat(Action act){
    return 0;
}


bool bounded_depth(List* buff, List* done, List *path,State initial_state, State goal){
    Action* cur;    /* etat en train d'être traité */
    Action* next_actions = malloc(sizeof(Action)*16); /* actions depuis cur */
    Action tmp_action;
    unsigned path_size;
    int nb_next_actions;
    int newBound = infinite;
    int res_search;

    /* info du programme */
    unsigned nb_created = 0;     /* nombre d'états créés */

    while (!listEmpty(buff)){
        /* récupérer prochain élément */
        cur = listPop(buff);

        /* ajouter à la liste des vus */
        listAdd(done, cur);

        /* ajouter au chemin */
        addToPath(path, cur);
        path_size = listSize(path); 

        if (equalState(cur->after, goal)) {
            /* fin */
            solution = cur->after;
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

                /* recherche recherche du nouveau état dans les états déjà traités  */
                res_search = searchElem(done, &tmp_action, equal_action);

                if(fEtat(tmp_action) <= bound && res_search == -1) {
                    /* si jamais rencontré */
                    listAdd(buff, createAction(tmp_action.before, tmp_action.move, tmp_action.after));
                }
                else {
                    newBound = min(newBound,fEtat(tmp_action));
                }
            }
        }


    }
    if (newBound == infinite){
        return true;
    }
    else {
        bound = newBound;
        return false;
    }



}










ResSearch* ida(State initial_state, State goal){

    /* initialisation outils */
    List *buff = createList(STACK_MAX_SIZE);
    List* done = createList(LIST_DONE_SIZE);
    List* path = createList(bound+4);

    
    /* création racine */
    State state; 
    copyState(&emptyStateida, &state);
    Move mv = {0,0,0,0,-1};
    Action *act = createAction(state, mv, initial_state);
    listAdd(buff, act);


    bool end_search = false;
    bound = fEtat(*act);
    while (!end_search){
        end_search = bounded_depth(buff, done, path, initial_state, goal);
    }
    if (solution.matrix != NULL){
        //return solution;
        return NULL;
    }
    //return fail;
    return NULL;

}



int heuristic(State init, State goal){
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


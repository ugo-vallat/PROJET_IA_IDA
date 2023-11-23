
#include <stdio.h>
#include <stdlib.h>
#include "depth.h"
#include <unistd.h>
#include "modules_utils.h"
#include "../data-structure/stack.h"
#include "../data-structure/list.h"
#include "../data-structure/state.h"


State emptyState = {{
        {-1,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }};


void addToPath(List* path, Action* act) {
    if(act->before.matrix[0][0] == -1) {
        listAdd(path, act);
        return;
    }
    while(!listEmpty(path) && !equalState(act->before, listLast(path)->after))
        listPop(path);
    listAdd(path, act);
}


bool search_depth_main(Stack* buff, List* done, List *path, State goal, unsigned *nb_ite, unsigned max_depth) {
    Action* cur;
    Action* next_actions = malloc(sizeof(Action)*16);
    Action tmp_action;
    bool found = false;
    int nb_next_actions, ite = 0;

    while(!found && !stackEmpty(buff) && !stackOverflow(buff)) {
        /* information itération */
        ite++;
        usleep(10000);
        loadingBarDepth(listSize(path), max_depth+1, ite);

        /* récupérer prochain élément */
        cur = stackTop(buff);
        buff = stackPop(buff);

        /* ajouter à la liste des vus */
        listAdd(done, cur);

        /* ajouter au chemin */
        addToPath(path, cur);

        if(equalState(cur->after, goal)) {
            /* fin */
            found = true;
        } else if (listSize(path) < max_depth + 1) {
            /* récupérer les prochaines actions */
            stateOpPoss(cur->after, &nb_next_actions, next_actions);

            /* les ajouter au buffer */
            for(int i = 0; i < nb_next_actions; i++) {
                tmp_action = next_actions[i];
                if(!searchElem(done, &tmp_action, equal_action))
                    stackPush(buff, createAction(next_actions[i].before, 
                        next_actions[i].move, next_actions[i].after));

            }
        }
    }
    if(stackOverflow(buff)) printf("[in search_depth_main] Stask full\n");
    free(next_actions);
    *nb_ite = ite;
    return found;
}



ResSearch* search_depth(State initial_state, State goal, unsigned max_depth) {
    /* Initialisation structure résultat*/
    ResSearch *res = createResSearch(DEPTH, max_depth+2);

    /* initialisation outils */
    Stack* buff = createStack(STACK_MAX_SIZE);
    List* path = createList(STACK_MAX_SIZE);
    List* done = createList(16);
    State state; 
    copyState(&emptyState, &state);
    Move mv = {0,0,0,0};
    Action *act = createAction(state, mv, initial_state);
    stackPush(buff, act);

    /* recherche du chemin */
    res->found = search_depth_main(buff, done, path, goal, &res->nb_ite, max_depth);

    /* récupérations du chemin */
    res->size_path = listSize(path) -1;
    for(unsigned i = 1; i < listSize(path); i++) {
        copyMove(&(listGet(path, i)->move), &res->path[i-1]);
        res->cost += listGet(path, i)->move.weight;
    }

    /* récupération des informations d'exécution */
    res->nb_state_created = listSize(done) + stackSize(buff);;
    res->nb_state_processed = listSize(done);

    /* libération de la mémoire */
    while(!listEmpty(done))
        deleteAction(listPop(done));
    while(!stackEmpty(buff)) {
        deleteAction(stackTop(buff));
        stackPop(buff);
    }
    deleteList(&path);
    deleteStack(&buff);
    deleteList(&done);

    return res;

}
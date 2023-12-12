#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "depth.h"
#include "../data-structure/list.h"
#include "../data-structure/state.h"
#include "modules_utils.h"
#include "ida_param.h"

State init_state;
State goal;
unsigned bound;
fun_heuristic heuristic;
fun_move_cost move_cost;
int infinite = 999999999;



int min(int a, int b) {
    return (a < b) ? a : b;
}



unsigned int fEtat(State init, int g){
    return g + heuristic(init, goal);
}

void addToPath_ida(List* path, Action* act) {
    /* si à la racine */
    if(act->move.mouv_index == 0) {
        listAdd(path, createAction(act->before, act->move, act->after));
        return;
    }

    /* cherche le parent de act */
    while(!listIsEmpty(path) && !equalState(act->before, listLast(path)->after))
        free(listPop(path));

    /* si auncun parent : echec */
    if(listIsEmpty(path)) {
        error("Echec ajout au chemin", EXIT_FAILURE);
    }

    /* ajout au chemin */
    listAdd(path, createAction(act->before, act->move, act->after));
}

/**
 * @brief Applique IDA* pour un seuil ( @ref bound )
 * 
 * @param initial_state Etat de départ
 * @param path_solution Chemin vers la solution (vide si non-trouvée)
 * @param created Nombre de noeuds créés
 * @param processed Nombre de noeuds explorés
 * @param ite Nombre d'itérations 
 * @return true si solution, false sinon
 */

bool bounded_depth(List **path_solution, unsigned *created, unsigned *processed, unsigned *ite){
    /* initialisation des listes */
    List* buff = createList(STACK_MAX_SIZE);    /* noeuds à explorer */
    List* done = createList(LIST_DONE_SIZE);    /* liste des noeuds vus */
    List* path = createList(bound+4);           /* chemin actuel */
    /* gestion des actions */
    Action* cur;    /* etat en train d'être traité */
    Action tmp_action;
    Action* next_actions = malloc(sizeof(Action)*16); /* actions depuis cur */
    int nb_next_actions;

    /* varibles locales suplémentaires */
    unsigned path_size = 1;
    unsigned newBound = infinite;
    int res_search;
    bool found = false;
    int f_value;

    /* Ajout de la racine au buffer */
    State state; 
    stateEmpty(&state);
    Move mv = {0,0,0,0,0,0};
    listAdd(buff, createAction(state, mv, init_state));

    /* info du programme */
    unsigned nb_created = 0;     /* nombre d'états créés */
    unsigned nb_processed = 0;  /* nombre d'états explorés */
    unsigned nb_ite = 0;            /* nombre d'itérations */

    while (!found && !listIsEmpty(buff)) {
        nb_ite++;
        nb_processed++;
        loadingBarDepth(path_size, bound+1, nb_ite);

        /* récupérer prochain élément */
        cur = listPop(buff);

        /* ajouter à la liste des vus */
        listAdd(done, cur);

        /* ajouter au chemin */
        addToPath_ida(path, cur);
        path_size = listSize(path);
        
        /* tester si but */
        if (equalState(cur->after, goal)) {
            /* fin */
            found = true;
        } else { 
            /* récupérer les prochaines actions */
            stateFindNextActions(cur->after, &nb_next_actions, next_actions);
            nb_created+=nb_next_actions;

            /* les ajouter au buffer */
            for(int i = 0; i < nb_next_actions; i++) {
                tmp_action = next_actions[i];
                tmp_action.move.mouv_index = path_size;
                tmp_action.move.weight = move_cost(tmp_action.move); // changer la fonction move_cost si jamais on implémente les déplacement à différent couts
                tmp_action.move.g_value = cur->move.g_value + tmp_action.move.weight;
                
                /*calcul de f */
                f_value = fEtat(tmp_action.after, tmp_action.move.g_value);
                
                /* recherche du nouveau état dans les états déjà traités  */
                res_search = searchElem(done, &tmp_action, equal_action);

                if(f_value <= (int)bound && res_search == -1) {
                    /* si jamais rencontré */
                    listAdd(buff, createAction(tmp_action.before, tmp_action.move, tmp_action.after));
                }
                else if(f_value > (int)bound) {
                    newBound = min(newBound,f_value);
                } else if (f_value <= (int)bound && res_search != -1) {
                    if (listGet(done, res_search)->move.g_value > tmp_action.move.g_value) {
                            /* si meilleur chemin */
                            listAdd(buff, createAction(tmp_action.before, 
                                tmp_action.move, tmp_action.after));
                            deleteAction(listRemove(done, res_search));
                            nb_processed--;
                        }
                }
            }
        }
    }
    /* libération de la mémoire */
    free(next_actions);
    listClear(buff); deleteList(&buff);
    listClear(done); deleteList(&done);

    /* mise à jour du seuil */
    if(newBound <= bound)
        error("newBound <= bound", EXIT_FAILURE);
    bound = newBound;

    /* renvoie des informations */
    *created += nb_created;
    *processed += nb_processed;
    *ite += nb_ite;
    if(!found) listClear(path);
    *path_solution = path;
    return found;
}




ResSearch* ida(State initial_state, State goal_gived, fun_heuristic fun_h, fun_move_cost fun_mc){
    /* initialisation variables globales  */
    heuristic = fun_h;
    move_cost = fun_mc;
    init_state = initial_state;
    goal = goal_gived;
    bound = fEtat(initial_state,0);
    

   /* Initialisation structure résultat*/
    ResSearch *res = createResSearch(IDA, 50);
    res->initial_state = initial_state;
    List *path;

    /* lancement du timer */
    clock_t start, end;
    start = clock();

    /* recherche tant que la solution n'est pas trouvée */
    unsigned old_bound;
    while (!(res->found)){
        old_bound = bound;
        /* lancement de ida */
        printf("\n ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ seuil : %d\n", bound);
        res->found = bounded_depth(&path, &(res->nb_state_created), &(res->nb_state_processed), &(res->nb_ite));
        printf("\033[2A\r");
    }
    printf("\033[4B\r");

    /* fin du timer */
    end = clock();
    res->time = ((double) (end - start)) / CLOCKS_PER_SEC;

     /* récupérations du chemin */
    res->size_path = listSize(path) -1;
    for(unsigned i = 1; i < listSize(path); i++) {
        copyMove(&(listGet(path, i)->move), &res->path[i-1]);
        res->cost += listGet(path, i)->move.weight;
    }
    listClear(path);
    deleteList(&path);
    res->depth = old_bound;

    return res;
}



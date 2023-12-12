#ifndef __IDA_H__
#define __IDA_H__


#include <stdbool.h>
#include "modules_utils.h"
#include "../data-structure/state.h"
#include "../data-structure/list.h"
#include "ida_param.h"


#define LIST_DONE_SIZE 512

/**
 * @brief Réalise Ida*
 * 
 * @param initial_state Etat de départ
 * @param goal_gived Etat But
 * @param fun_h Heuristique utilisée
 * @param fun_mc Fonction de calcul des coûts utilisée
 * @return Le Résultat de la recherche
 */


ResSearch* ida(State initial_state, State goal_gived, fun_heuristic fun_h, fun_move_cost fun_mc);




#endif
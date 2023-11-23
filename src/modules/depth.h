


#ifndef __DEPTH_H__
#define __DEPTH_H__

#include <stdbool.h>
#include "modules_utils.h"
#include "../data-structure/state.h"



/**
 * @brief Cherche l'état but en applique l'algorithme de recherche en 
 * profondeur
 * 
 * @param initial_state Etat initial
 * @param goal Etat but
 * @param max_depth profondeur maximale
 * @return Résultats dans la structure ResSearch
 */
ResSearch* search_depth(State initial_state, State goal, unsigned max_depth);


#endif
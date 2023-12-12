#ifndef __DATATEST_H__
#define __DATATEST_H__
#include "../src/data-structure/state.h"


/* Association des tests : 
    start -> end
    1     -> 1,2
    2     -> 3,4,5,6
    3     -> 7
    4     -> 8
    5     -> 9
    6     -> 10,11,12,13,14
    7     -> 15
*/

/**
 * @brief Met dans start l'état départ associé à l'id
 * 
 * @param id id de l'état de départ
 * @param start Etat à remplir
 */
void getEtatStart(int id, State *start);


/**
 * @brief Met dans end l'état d'arrivée associé à l'id
 * 
 * @param id id de l'état d'arrivée
 * @param end Etat à remplir
 */
void getEtatEnd(int id, State *end);

#endif
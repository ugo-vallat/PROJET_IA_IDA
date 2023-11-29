#ifndef __DATATEST_H__
#define __DATATEST_H__
#include "utils.h"
#include "state.h"


/**
 * @brief Mets à jour les états fournis pour qu'ils correspondent au jeux de test voulu
 * 
 * @param id Numéro du jeu de test
 * @param ed Nom de l'état initial
 * @param ef Nom de l'état final
 */
void getEtatTest(int id, State *ed, State *ef);


#endif
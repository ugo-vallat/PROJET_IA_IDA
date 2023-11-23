
#ifndef __LIST_H__
#define __LIST_H__
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include "state.h"
#include "utils.h"

/*------------------------------------------------------------------*/
/*                        STRUCTURE LIST                            */
/*------------------------------------------------------------------*/

/* Définition opaque de la structure list */
typedef struct s_list List;
typedef List *ptrList;

/**
 * @brief Crée une liste vide
 *
 * @param size Espace mémoire initial (en nombre d'éléments)
 *
 * @return pointeur vers la liste
 */
List *createList(unsigned int size);

/**
 * @brief Supprime la liste et libère la mémoire
 *
 * @param l liste à supprimer
 * @pre l != NULL
 * @pre *l != NULL
 */
void deleteList(ptrList *l);

/**
 * @brief Ajoute l'élément à la fin de la liste
 *
 * @param l Pointeur vers la liste
 * @param v Valeur à ajouter
 * @pre l != NULL
 */
void listAdd(List *l, TYPE v);


/**
 * @brief Supprime le dernier élément de la liste
 *
 * @param l list
 * @pre l != NULL
 *
 * @pre taille liste > 0
 * @return valeur avant suppression
 **/
TYPE listPop(List *l);



/**

 * @brief Renvoie si la liste est vide
 *
 * @param l Pointeur vers la liste
 * @pre l != NULL
 * @return true si vide, false sinon
 */
bool listEmpty(List *l);

/**
 * @brief Renvoie la taille de la liste (position + 1 du dernier élément)
 *
 * @param l Pointeur vers la liste
 * @return taille de la liste
 *
 */

unsigned int listSize(List *l);

/**
 * @brief Renvoie le dernier élément de la liste, NULL si vide
 * 
 * @param l Liste
 * @return Dernier élément 
 */
TYPE listLast(List *l);
/**
 * @brief Renvoie l'élément à la position i
 * 
 * @param l Liste
 * @param i position
 * @return TYPE 
 */
TYPE listGet(List *l, unsigned i);


/**
 * @brief Cherheche l'element dans la liste
 * 
 * @param l Liste
 * @param s Element à chercher
 * @return true si trouvé, false sinon
 */
bool searchElem(List *l, TYPE e, bool (*equal)(TYPE e1, TYPE e2));

bool equal_state(TYPE e1, TYPE e2);

bool equal_action(TYPE e1, TYPE e2);


/**
 * @brief Afficher la liste dans stdout
 * 
 * @param l liste à afficher
 */
void listDisplay(List* l);




#endif

#ifndef __LIST_H__
#define __LIST_H__
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include "state.h"
#include "utils.h"

#define MEMORY_STEP 64

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
void listAdd(List *l, Action* v);


/**
 * @brief Supprime le dernier élément de la liste
 *
 * @param l list
 * @pre l != NULL
 *
 * @pre taille liste > 0
 * @return valeur avant suppression
 **/
Action* listPop(List *l);



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
Action* listLast(List *l);
/**
 * @brief Renvoie l'élément à la position i
 * 
 * @param l Liste
 * @param i position
 * @return Action* 
 */
Action* listGet(List *l, unsigned i);

/**
 * @brief Enlève l'élément à l'indice i
 * 
 * @param l liste
 * @param i indice de l'élément à retirer
 * @return élément supprimé
 */
Action* listRemove(List *l, unsigned i);


/**
 * @brief Cherheche l'element dans la liste
 * 
 * @param l Liste
 * @param s Element à chercher
 * @return position de lélement, -1 si pas trouvé
 */
int searchElem(List *l, Action* e, bool (*equal)(Action* e1, Action* e2));

bool equal_state(State* e1, State* e2);

bool equal_action(Action* e1, Action* e2);


/**
 * @brief Afficher la liste dans stdout
 * 
 * @param l liste à afficher
 */
void listDisplay(List* l);




#endif
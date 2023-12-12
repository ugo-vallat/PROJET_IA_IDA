

#include "list.h"
#include "state.h"
#include "utils.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------*/
/*                        STRUCTURE LIST                            */
/*------------------------------------------------------------------*/

/* Définition de la structure list*/
struct s_list {
    unsigned int memory_size; /* Taille du tableau en mémoire */
    unsigned int size;        /* taille de la liste (nombre éléments) */
    Action** tab;                 /* tableau des valeurs */
};



List *createList(unsigned int size) {
    List *l = malloc(sizeof(List));
    if (l == NULL)
        error("erreur malloc list", EXIT_FAILURE);

    l->tab = malloc(sizeof(Action*) * size);
    if (l->tab == NULL && size != 0)
        error("[in createList] erreur malloc tab", EXIT_FAILURE);

    l->memory_size = size;
    l->size = 0;
    return l;
}



void deleteList(ptrList *l) {
    /* test l != NULL */
    testArgNull(l, "deleteList");
    testArgNull((*l), "deleteList");

    /* libération de la mémoire */
    free((*l)->tab);
    free((*l));
    *l = NULL;
}

/**
 * @brief Modifie l'espace mémoire aloué au tableau
 *
 * @param l Pointeur vers la liste
 * @param new_size Nouvelle taille du tableau
 * @pre l != NULL
 */
void adjustMemorySizeList(List *l, unsigned int new_size) {
    testArgNull(l, "adjustMemorySizeList");

    /* nouvelle taille de la liste */
    l->memory_size = new_size;

    /* modification taille du tableau */
    l->tab = realloc(l->tab, new_size * sizeof(Action*));
    if (new_size != 0 && l->tab == NULL)
        error("[in adjustMemorySizeList] echec realloc tab", EXIT_FAILURE);
}



void listAdd(List *l, Action* v) {
    /* test l != NULL */
    testArgNull(l, "listAdd");

    /* agrandissement de la liste si pleine */
    if (l->size+2 >= l->memory_size)
        adjustMemorySizeList(l, l->memory_size + MEMORY_STEP);

    /* Ajout de la valeur */
    l->tab[l->size] = v;
    l->size++;
}




Action* listPop(List *l) {
    /* vérification paramêtre */
    testArgNull(l, "listPop");
    if (l->size <= 0)
        error("[in listPop] liste déjà vide", EXIT_FAILURE);

    /* suppression de l'élément */
    Action* elem = l->tab[l->size-1];
    l->size--;
    adjustMemorySizeList(l, l->size);
    return elem;
}



bool listIsEmpty(List *l) {
    testArgNull(l, "listEmpty");
    return l->size == 0;
}

void listClear(List* l){
    while (!listIsEmpty(l))
        free(listPop(l));
}


unsigned int listSize(List *l) {
    testArgNull(l, "lestSize");
    return l->size;
}

Action* listLast(List *l) {
    testArgNull(l, "listLast");
    if(l->size == 0) return NULL;
    else return l->tab[l->size-1];
}


Action* listGet(List *l, unsigned i) {
    testArgNull(l, "listGet");
    if(i >= l->size)
        error("[in listGet] Invalide position", EXIT_FAILURE);
    return l->tab[i];
}


int searchElem(List *l, Action* e, bool (*equal)(Action* e1, Action* e2)) {
    testArgNull(l, "searchElem");
    for(unsigned i = 0; i < l->size; i++)
        if(equal(e, l->tab[i])) 
            return i;
    return -1;
}

Action* listRemove(List *l, unsigned i) {
    testArgNull(l, "listRemove");
    if(i >= l->size)
        error("[in listRemove] Invalide position", EXIT_FAILURE);
    
    /* récupérer l'élément à supprimer */
    Action *save = l->tab[i];

    /* supprimer l'élément de la liste */
    for(unsigned c = i ; c < l->size-1; c++)
        l->tab[c] = l->tab[c+1];
    l->size--;

    /* renvoyer l'élément */
    return save;
}



bool equal_state(State* e1, State* e2) {
    return equalState(*((State*)e1), *((State*)e2));
}

bool equal_action(Action* e1, Action* e2) {
    return equalState(e1->after, e2->after);
}



void listDisplay(List* l) {
    printf("list (%d) : ---<+> \n", l->size);
    for(unsigned i = 0; i < l->size; i++) {
        displayAction(l->tab[i]);
    }
}
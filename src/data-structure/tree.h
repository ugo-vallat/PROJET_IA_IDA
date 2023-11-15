


#ifndef __TREE_H__
#define __TREE_H__

#include "etat.h"
#include "utils.h"



typedef struct s_tree Tree;

struct s_tree {
    int pere;
};

/**
 * @brief Crée un abre
 * 
 * @return Tree* 
 * @note NULL = Arbre vide
 */
Tree* treeCreate();

/**
 * @brief Ajoute une valeur dans l'arbre
 * 
 * @param t 
 * @param c 
 * @param e 
 * @return Tree* 
 */
Tree* treeAddValue(Tree* t, Couple c, Etat* e);







#endif
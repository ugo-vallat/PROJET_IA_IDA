
#ifndef __TREE_H__
#define __TREE_H__

#include "state.h"
#include "utils.h"
#include <stdbool.h>


typedef struct s_link Link;

typedef struct s_tree Tree;

struct s_link {
    Move move;          /* mouvement de l'Etat source vers destination */
    Tree* tree_src;     /* arbre source */
    Tree* tree_dst;     /* arbre destination */
};

struct s_tree {
    State state;        /* Etat du noeud */
    unsigned depth;          /* profondeur du noeud : racine = 0*/
    Link parent;        /* NULL si root */
    Link child[4][4];   /* [pile_src][pile_dst] */
};



/**
 * @brief Crée un abre
 * 
 * @param s Etat du noeud racine
 * @return Arbre créé
 */
Tree* createTree(State s);

/**
 * @brief Ajoute une feuille au noeud courant
 * 
 * @param t Arbre à compléter
 * @param s Nouvel Etat
 * @param m Mouement transition 
 */
void addLeaf(Tree* t, State s, Move m);

/**
 * @brief Test si le sous tree existe
 * 
 * @param t Arbre courrant
 * @param stem_src Pige source
 * @param stem_dst Pige destination
 * @return true si existe, false sinon
 */
bool existChild(Tree* t, int stem_src, int stem_dst);

/**
 * @brief Renvoie le mouvement associée au coup (stem_src,stem_dst)
 * 
 * @param t Arbre courant
 * @param stem_src Pige source
 * @param stem_dst Pige destination
 * @return Move 
 */
Move getMov(Tree* t, int stem_src, int stem_dst);

/**
 * @brief Renvoie l'adresse du sous arbre fils
 * 
 * @param t Arbre courant
 * @param stem_src Pige source
 * @param stem_dst Pige destination
 * @return Racine du sous tree, NULL si aucun
 */
Tree* getChild(Tree* t, int stem_src, int stem_dst);

/**
 * @brief Renvoie l'arbre parent de l'arbre courant (noeud parent)
 * 
 * @param t Arbre courant
 * @return Arbre parent, NULL si racine
 */
Tree* getParent(Tree* t);


/**
 * @brief Test si le noeud courant est la racine
 * 
 * @param t Arbre Courant
 * @return true si racine, false sinon
 */
bool isRoot(Tree* t);


/**
 * @brief Renvoie la profondeur de l'arbre courant
 * 
 * @param t Arbre courant
 * @return profondeur 
 */
unsigned getDepth(Tree *t);

/**
 * @brief test si un arbre est une feuille
 * 
 * @param t arbre à tester
 * @return true si feuille, false sinon
 */
bool isLeaf(Tree *t);



#endif
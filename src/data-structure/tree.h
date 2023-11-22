


#ifndef __TREE_H__
#define __TREE_H__

#include "etat.h"
#include "utils.h"
#include <stdbool.h>


typedef struct s_link Link;

typedef struct s_arbre Arbre;

// typedef struct s_noeud Noeud;

struct s_link {
    Coup coup;      /* informations sur le coup joué */
    Arbre* a_src;     /* Noeud source */
    Arbre* a_dst;    /* Noeud destination */
};

struct s_arbre {
    Etat etat;          /* Etat du noeud */
    Link pere;         /* NULL si root */
    Link fils[4][4];   /* [pile_src][pile_dst] */
};



/**
 * @brief Crée un abre
 * 
 * @return Arbre* 
 * @note Renvoie une sentinelle
 */
Arbre* creer_arbre(Etat e);

/**
 * @brief Ajoute une feuille au noeud courant
 * 
 * @param a Arbre (noeud) courant
 * @param c 
 * @param e 
 */
void ajouter_Noeud(Arbre* a, Coup c, Etat e);

/**
 * @brief fusionne 2 arbre (ajout de l'arbre fils dans l'arbre père)
 * 
 * @param a_pere Pere
 * @param a_fils Fils
 * @param c Coup de l'etat pere à l'etat fils
 * @return Arbre pere
 */
Arbre* arbre_fusioner(Arbre* a_pere, Arbre* a_fils, Coup c);

/**
 * @brief Renvoie l'adresse du sous arbre fils
 * 
 * @param a Arbre parcouru
 * @param c Coup vers prochain Etat
 * @return Racine du sous arbre, NULL si aucun
 */
Arbre* vers_fils(Arbre* a, Coup c);

/**
 * @brief Renvoie l'arbre parent de l'arbre courant (noeud parent)
 * 
 * @param a Arbre courant
 * @return Arbre parent, NULL si racine
 */
Arbre* vers_pere(Arbre* a);



/**
 * @brief Test si le sous arbre existe
 * 
 * @param a Arbre courrant
 * @param c Coup à tester
 * @return true si existe, false sinon
 */
bool existe_fils(Arbre* a, Coup c);

/**
 * @brief Test si le noeud courant est la racine
 * 
 * @param a Arbre parcouru
 * @return true si racine, false sinon
 */
bool est_racine(Arbre* a);



#endif
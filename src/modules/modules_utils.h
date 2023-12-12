#ifndef __MOD_UTILS_H__
#define __MOD_UTILS_H__

#include "../data-structure/state.h"

#define STACK_MAX_SIZE 10000

typedef enum e_algo {
    DEPTH=1, IDA=2
} Algo;

typedef struct s_result_search ResSearch;

struct s_result_search {
    Algo algo;          /* type d'algo utilisé */
    unsigned depth;     /* profondeur de recherce */
    bool found;         /* true si chemin trouvé */
    unsigned size_path; /* taille du chemin (nombre de mouvements)*/
    State initial_state;/* Etat initial */
    Move *path;         /* chemin (liste de mouvements)*/
    int cost;           /* Cout du chemin */
    unsigned nb_ite;    /* nombre d'itérations */
    unsigned nb_state_created;   /* Nombre d'états créés */
    unsigned nb_state_processed; /* Nombre d'états explorés */
    double time;        /* temps d'exécution */
};

/*
    ===================
    ===  AFFICHAGE  ===
    ===================
*/

/**
 * @brief Affiche les résultats de l'algo
 * 
 * @param res Resultats à afficher
 */
void displayResSearch(ResSearch *res);

/**
 * @brief Affiche une barre de chargement
 * 
 * @param size Taille de la barre
 * @param max taille max de la barre
 * @param ite numéro d'itération
 */
void loadingBarDepth(int size, int max, int ite);

/**
 * @brief Affiche le déroulé de la partie sous forme d'animation
 * 
 * @param res Résultat de la recherche
 * @param init_state Etat initiale
 */
void showGameAnimation(ResSearch *res);

/*
    ===================
    ===  ResSearch  ===
    ===================
*/

/**
 * @brief Crée, alloue (malloc) et initialise la structure ResSearch
 * 
 * @param algo Algo utilisé
 * @param size_path_max Taille maximale du chemin
 * @return ResSearch* 
 */
ResSearch* createResSearch(Algo algo, unsigned size_path_max);

/**
 * @brief Supprime la structure res et libère la mémoire
 * 
 * @param res Résultat
 */
void deleteResSearch(ResSearch *res);



#endif
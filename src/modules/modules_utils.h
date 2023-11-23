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
    bool found;         /* true si chemin trouvé */
    unsigned size_path; /* taille du chemin (nombre de mouvements)*/
    Move *path;         /* chemin (liste de mouvements)*/
    int cost;           /* Cout du chemin */
    unsigned nb_ite;    /* nombre d'itérations */
    unsigned nb_state_created;   /* Nombre d'états créés */
    unsigned nb_state_processed; /* Nombre d'états explorés */
};

/**
 * @brief Affiche les résultats de l'algo
 * 
 * @param res Resultats à afficher
 */
void displayResSearch(ResSearch *res);


void loadingBarDepth(int size, int max, int ite);

void showGameAnimation(ResSearch *res, State init_state);

ResSearch* createResSearch(Algo algo, unsigned size_path);

void deleteResSearch(ResSearch *res);



#endif
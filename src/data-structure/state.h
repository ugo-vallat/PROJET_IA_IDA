#ifndef __STATE_H__
#define __STATE_H__
#include "utils.h"
#include "stdbool.h"

typedef struct s_state {
    int matrix[4][4];
}State;

/**
 * @brief contient les informations relatives au déplacement d'un anneau
 * 
 */
typedef struct s_move {
    int id;         /* numéro(id) de l'anneau. Pre : 1 <= id <= 9*/
    int weight;     /* poids du coup  */
    int stem_src;   /* tige source. Pre : 0 <= p_src <= 3 */
    int stem_dst;   /* tige destination. Pre : 0 <= p_dst <= 3 */
} Move;

/**
 * @brief Contient les informations de déplacement et le résultat obtenu
 * 
 */
typedef struct s_action{
    State before; /* Etat avant déplacement */
    Move move;    /* Déplacement */ 
    State after;  /* Etat après déplacement */
}Action;

void afficherState(State e);

/**
 * @brief Renvoie les mouvements Possible d'un Etat
 * 
 * @param e Etat initiale
 * @return Un tableau de tout les mouvements possible de l'Etat
 */

Move* findMoves(State e);

/**
 * @brief Renvoie le nouvel Etat suite à un déplacement
 * 
 * @param s Etat initiale
 * @param m Mouvement à appliquer 
 * @return Nouvel Etat 
 */
Action applyMove(State s, Move m);

/**
 * @brief Test si l'état correspond au but
 * 
 * @param s Etat testé 
 * @return true si égal au but, false sinon
 */
bool estBut(State s, State but);

/**
 * @brief Test si 2 états son similaires
 * 
 * @param s1 Etat 1
 * @param s2 Etat 2
 * @return true si égaux, false sinon
 */
bool egal(State s1, State s2);

/**
 * @brief Renvoie la liste des mouvement-etats possibles
 * 
 * @param s Etat initiale
 * @param res Tableau des mouvement-etats possibles
 * @param nb_move Nombre de mouvement-etats possibles
 */
void opPoss(State s, MoveState *res, int *nb_move);

/**
 * @brief Test si un coup est valide (respect des prédicats)
 * @param c coup à tester
 * @param fun_name Nom de la fonction appelante
 * 
 */
void testMoveIsValid(Move m, char* fun_name);


/**
 * @brief Renvoie si le mouvement est possible
 * 
 * @param s Etat initiale
 * @param m Movement à tester sur l'Etat
 * @return true si possible, false sinon
 */
bool isMovePossible(State s, Move m);

/**
 * @brief Test si la valeur d'un pique est valide
 * 
 * @param stem Pique à tester
 * @param fun_name Nom de la fonction appelante
 */
void testStemValid(int stem, char* fun_name);


#endif

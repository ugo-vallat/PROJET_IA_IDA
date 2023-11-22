#ifndef __UTILS_H__
#define __UTILS_H__

typedef struct s_coup {
    int id;     /* numéro(id) de l'anneau. Pre : 1 <= id <= 9*/
    int weight; /* poids du coup  */
    int p_src;    /* pique source. Pre : 0 <= p_src <= 3 */
    int p_dst;    /* pique destination. Pre : 0 <= p_dst <= 3 */
} Coup;

/**
 * @brief Exit le programme en affichant le message msg
 * 
 * @param msg Message à afficher
 * @param exit_val Valeur de sortie
 */
void erreur(char* msg, int exit_val);

/**
 * @brief Test si l'argument est NULL et exit si oui
 * 
 * @param arg argument à tester
 * @param fun Nom de la fonction appelante
 */
void testArgNull(void* arg, char* fun);

/**
 * @brief Test si un coup est valide (respect des prédicats)
 * @param c coup à tester
 * @param fun Nom de la fonction appelante
 * 
 */
void testCoupEstValide(Coup c, char* fun);

#endif

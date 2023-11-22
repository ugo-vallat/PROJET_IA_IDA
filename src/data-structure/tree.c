
#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "etat.h"
#include "tree.h"
#include "utils.h"

/**
 * @brief Initialise les lien vers les fils à NULL
 * 
 * @param a Arbre à initialiser
 */
void init_pere_et_fils(Arbre* a) {
    testArgNull(a, "init_pere_et_fils");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            a->fils[i][j].a_dst = NULL;
            a->fils[i][j].a_src = a;
        }
    }
    a->pere.a_dst = a;
}


Arbre* creer_arbre(Etat e) {
    Arbre* a = malloc(sizeof(Arbre));
    a->etat = e;
    a->pere.a_src = NULL;
    init_pere_et_fils(a);
    return a;
}


void ajouter_feuille(Arbre* a, Coup c, Etat e) {
    testArgNull(a, "ajouter_feuille");
    testCoupEstValide(c, "ajouter_feuille");
    Arbre* sa = creer_arbre(e);
    a->fils[c.p_src][c.p_dst].coup = c;
    a->fils[c.p_src][c.p_dst].a_dst = sa;

    sa->pere.coup = c;
    sa->pere.a_src = a;
}


Arbre* arbre_fusioner(Arbre* a_pere, Arbre* a_fils, Coup c) {
    testArgNull(a_pere, "arbre_fusioner");
    testArgNull(a_fils, "arbre_fusioner");
    testCoupEstValide(c, "arbre_fusioner");
    a_pere->fils[c.p_src][c.p_dst].coup = c;
    a_pere->fils[c.p_src][c.p_dst].a_dst = a_fils;

    a_fils->pere.a_src = a_pere;
    a_fils->pere.coup = c;
    return a_pere;
}


Arbre* vers_fils(Arbre* a, Coup c) {
    testArgNull(a, "vers_fils");
    testCoupEstValide(c, "vers_fils");
    return a->fils[c.p_src][c.p_dst].a_dst;
}

Arbre* vers_pere(Arbre* a) {
    testArgNull(a, "vers_pere");
    return a->pere.a_src;
}


bool existe_fils(Arbre* a, Coup c) {
    testArgNull(a, "existe_fils");
    testCoupEstValide(c, "existe_fils");
    return a->fils[c.p_src][c.p_dst].a_dst != NULL;
}


bool est_racine(Arbre* a) {
    testArgNull(a, "est_racine");
    return a->pere.a_src == NULL;
}
#ifndef __ETAT_H__
#define __ETAT_H__
#include <utils.h>

typedef struct s_etat {
  int matrice[4][4];
}Etat;

typedef struct s_operationPossibles{
  Couple operations;
  Etat etatFils
  int couts;
}operationPossibles;

void AfficherEtat(Etat e);

Couple* TrouverMouvements(Etat e);

Etat Deplacer(Etat e,int pique_depart, int pique_arrivee);

bool estBut(Etat e);

bool  egal(Etat e, Etat but);

operationPossibles opPoss(Etat e);



#endif

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "state.h"


/*
    ===========================================
    ===  Utils pour les algos de recherche  ===
    ===========================================
*/


void findMoves(State e, Move* moves){
    Move m;
    int moves_iterator = 0;
    int top_src; /* hauteur de la pisque source */
    for(int i=0; i<4; i++){
        /* lecture top */
        top_src = e.matrix[i][0];
        /* si la pique n'est pas vide */
        if (top_src != 0) 
        for(int j = 0; j < 4; j++){
            /* si la pique destination n'est pas pleine et n'est pas la pique source */
            if (e.matrix[j][0] != 3 && j != i ){
                m.id = e.matrix[i][top_src];
                m.weight = 1;
                m.stem_src = i;
                m.stem_dst = j;
                m.mouv_index = 0;
                m.g_value = 1;
                moves[moves_iterator] = m;
                moves_iterator++;
            }
        }
    }
    for (int i = moves_iterator; i < 9; i++) {
      m.id = -1;
      moves[i] = m;
    }
}

Action applyMove(State s, Move m){
    Action ms;
    ms.before = s;
    s.matrix[m.stem_dst][s.matrix[m.stem_dst][0] + 1] = m.id;
    s.matrix[m.stem_src][s.matrix[m.stem_src][0]] = 0;
    s.matrix[m.stem_src][0]--;
    s.matrix[m.stem_dst][0]++;
    ms.move = m;
    ms.after = s;
    return ms;

}

bool stateIsGoal(State s, State but){
    return equalState(s,but);
}

void stateFindNextActions(State s, int *nb_move, Action* action_possibles){
    Move moves_tab[12];
    *nb_move = 0;
    findMoves(s, moves_tab);
    for (int i = 0 ; i < 9; i++) {
      if (moves_tab[i].id != -1){
        action_possibles[i] = applyMove(s,moves_tab[i]);
        (*nb_move)++;
      }
    }
}


bool isMovePossible(State s, Move m){
    bool test = true;
    if (s.matrix[m.stem_src][0] <= 0 || s.matrix[m.stem_dst][0] > 3){
      return false;
    }
    return test;
}


/*
    ===============
    ===  STATE  ===
    ===============
*/

bool equalState(State s1, State s2){
    /* comparer la taille des colonnes */
    for(unsigned i = 0; i < 4; i++)
        if(s1.matrix[i][0] != s2.matrix[i][0])
            return false;
    /* comparer les éléments dans les colonnes */
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < (s1.matrix[i][0]+1); j++) {
            if (s1.matrix[i][j] != s2.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void stateEmpty(State* s) {
    for(unsigned i = 0; i < 4; i++)
        for(unsigned j = 0; j < 4; j++)
            s->matrix[i][j] = 0;
}

void copyState(State *src, State *dst) {
    for(unsigned i = 0; i < 4; i++)
        for(unsigned j = 0; j < 4; j++)
            dst->matrix[i][j] = src->matrix[i][j];
}


/*
    ================
    ===  ACTION  ===
    ================
*/
Action* createAction(State before, Move move, State after) {
    Action *act = malloc(sizeof(Action));
    copyState(&(before), &(act->before));
    copyState(&(after), &(act->after));
    copyMove(&(move), &(act->move));
    return act;
}

void deleteAction(Action* act) {
    free(act);
}

void copyAction(Action *src, Action *dst) {
    copyState(&(src->before), &(dst->before));
    copyState(&(src->after), &(dst->after));
    copyMove(&(src->move), &(dst->move));
}



/*
    ==============
    ===  MOVE  ===
    ==============
*/

void copyMove(Move *src, Move *dst) {
    dst->id = src->id;
    dst->stem_src = src->stem_src;
    dst->stem_dst = src->stem_dst;
    dst->weight = src->weight;
    dst->mouv_index = src->mouv_index;
    dst->g_value = src->g_value;
}

void testMoveIsValid(Move m, char* fun_name) {
    bool test = true;
    test &= m.id >= 1;
    test &= m.id <= 9;
    test &= m.stem_src >= 0;
    test &= m.stem_src <= 3;
    test &= m.stem_dst >= 0;
    test &= m.stem_dst <= 3;
    if(!test) {
        fprintf(stderr, "[in %s] Coup invalide (id = %d, stem_src = %d, stem_dst = %d, weight = %d)\n",
             fun_name, m.id, m.stem_src, m.stem_dst, m.weight);
        exit(EXIT_FAILURE);
    }
}

/*
    ===============
    ===  UTILS  ===
    ===============
*/

void testStemValid(int stem, char* fun_name) {
    if (0 > stem || 3 < stem) {
        fprintf(stderr, "[in %s] Argument stem invalide", fun_name);
        exit(EXIT_FAILURE);
    }
}


/*
    ===================
    ===  AFFICHAGE  ===
    ===================
*/


void displayMove(Move m){
  printf("(pic depart = %d , pic arrivee = %d , valeur deplacee = %d, index = %d, weight = %d, g_value = %d)\n", 
    m.stem_src,m.stem_dst,m.id, m.mouv_index, m.weight, m.g_value);
}

#define BLUE "\033[38;5;27m"
#define YELLOW "\033[38;5;226m"
#define RED "\033[38;5;196m"
#define REST "\033[0m"

/**
 * @brief Convertion valeur en char (vtc)
 * 
 * @param v valeur de l'anneau
 * @return char 
 */
char vtc(int v) {
    switch(v) {
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
    }
    return ' ';
}

void displayState(State s){
#ifdef DEBUG
    for(int i = 3; i >= 1; i--)
        printf("┃ %c %c %c %c ┃\n", vtc(s.matrix[0][i]), vtc(s.matrix[1][i]), vtc(s.matrix[2][i]), vtc(s.matrix[3][i]));
    printf("┠─────────┨\n");
    printf("┃ %d %d %d %d ┃\n", s.matrix[0][0],s.matrix[1][0],s.matrix[2][0],s.matrix[3][0]);
    printf("┖─────────┚\n");
#else
    for(int i = 3; i >= 1; i--)
        printf("┃ %c %c %c %c ┃\n", vtc(s.matrix[0][i]), vtc(s.matrix[1][i]), vtc(s.matrix[2][i]), vtc(s.matrix[3][i]));
    printf("┖─────────┚\n");
#endif
}

void displayAction(Action *a) {
    Move m = a->move;
    State before = a->before;
    State after = a->after;
    printf("_____(%d =%d=> %d)_____<w:%d><i:%d>\n", m.stem_src, m.id, m.stem_dst, m.weight, m.mouv_index);
    for(int i = 3; i >= 1; i--) {
        printf("|%c %c %c %c| ", vtc(before.matrix[0][i]), vtc(before.matrix[1][i]), vtc(before.matrix[2][i]), vtc(before.matrix[3][i]));
        printf(" |%c %c %c %c|\n", vtc(after.matrix[0][i]), vtc(after.matrix[1][i]), vtc(after.matrix[2][i]), vtc(after.matrix[3][i]));
    }
    printf("--------------------\n");
}
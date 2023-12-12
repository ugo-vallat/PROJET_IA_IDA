/**
 * @file ida_param.h
 * @author Ugo VALLAT
 * @brief Ce fichier défini les fonction donnant l'heuristique pour un état et le cout pour un mouvement
 * utilisées dans IDA*
 */
#include "ida_param.h"
#include "../data-structure/state.h"
#include <stdlib.h>
#include <stdio.h>





int h_simpl(State cur, State goal) {
    int sums = 0;
    for (int i = 0; i < 4; i++)
    {
       for(int j = cur.matrix[i][0]; j> 0 ; j--){
            if (cur.matrix[i][j] != goal.matrix[i][j]){
                sums+= 1;
            }
       } 
    }
    return sums;
}


int h_depth(State cur, State goal) {
    int sum = 0;
    int j;
    bool found;

    for (int i = 0; i < 4; i++)
    {
       j = 1;
       found = false;
       while (!found && j <= cur.matrix[i][0]) {
            if(cur.matrix[i][j] != goal.matrix[i][j]) {
                sum += (cur.matrix[i][0] - j + 1);
                found = true;
            }
            j++;
       }
    }
    return sum;
}

int h_depth_2(State cur, State goal) {
    int sum = 0;
    int j;
    bool found;

    for (int i = 0; i < 4; i++)
    {
       j = 1;
       found = false;
       while (!found && j <= cur.matrix[i][0]) {
            if(cur.matrix[i][j] != goal.matrix[i][j]) {
                /* coût tige départ */
                sum += (cur.matrix[i][0] - j + 1) * 3;

                /* coût tige arrivée */
                for(unsigned l = 0; l < 4; l++)
                    for(unsigned c = 1; c < 4; c++)
                        if(goal.matrix[l][c] == cur.matrix[i][j])
                            sum += (cur.matrix[l][0] - c + 1);
                
                found = true;
            }
            j++;
       }
    }
    return sum;
}


int h_for_cost(State cur, State goal) {
    int sums = 0;
    for (int i = 0; i < 4; i++)
    {
       for(int j = cur.matrix[i][0]; j> 0 ; j--){
            if (cur.matrix[i][j] != goal.matrix[i][j]){
                sums+= cur.matrix[i][j];
            }
       } 
    }
    return sums;
}


int c_one(Move m) {
    (void)m;
    return 1;
}

int c_id(Move m) {
    return m.id;
}


fun_heuristic getFunHeuristic(Heuristic e) {
    switch (e) {
        case H_SIMPLE:
            return h_simpl;
        case H_DEPTH:
            return h_depth;
        case H_DEPTH_2:
            return h_depth_2;
        case H_FOR_COST:
            return h_for_cost;
    }

    error("ID heuristique invalide", EXIT_FAILURE);
    return NULL;
}

fun_move_cost getFunMoveCost(MoveCost mc) {
    switch (mc) {
        case C_ONE:
            return c_one;
        case C_ID:
            return c_id;
    }
    printf(" mc : %d\n", mc);
    error("ID coup invalide", EXIT_FAILURE);
    return NULL;
}
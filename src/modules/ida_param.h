/**
 * @file ida_param.h
 * @author Ugo VALLAT
 * @brief Ce fichier défini les fonction donnant l'heuristique pour un état et le cout pour un mouvement
 * utilisées dans IDA*
 */

#ifndef __IDA_PARAM_H__
#define __IDA_PARAM_H__

#include "../data-structure/state.h"

typedef int (*fun_heuristic)(State cur, State goal);

typedef int (*fun_move_cost)(Move m); 

typedef enum e_heuristic{
    H_SIMPLE=1, H_DEPTH=2, H_DEPTH_2=3, H_FOR_COST=4
} Heuristic;

typedef enum e_move_cost{
    C_ONE=1, C_ID=2
} MoveCost;

fun_heuristic getFunHeuristic(Heuristic e);

fun_move_cost getFunMoveCost(MoveCost mc);






#endif
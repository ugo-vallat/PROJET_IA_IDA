#ifndef __IDA_H__
#define __IDA_H__


#include <stdbool.h>
#include "modules_utils.h"
#include "../data-structure/state.h"
#include "../data-structure/list.h"
#define LIST_DONE_SIZE 512

int min(int a, int b);

ResSearch* ida(State initial_state, State goal);

unsigned int fEtat(State init, int g);

int heuristic(State init);

bool bounded_depth(List* buff, List* done, List *path,int g, unsigned *created, unsigned *processed, unsigned *ite);

void addToPath_ida(List* path, Action* act);

int cost_movement(State s);



#endif
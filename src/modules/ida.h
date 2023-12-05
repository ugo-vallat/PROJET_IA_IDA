#ifndef __IDA_H__
#define __IDA_H__


#include <stdbool.h>
#include "modules_utils.h"
#include "../data-structure/state.h"
#define LIST_DONE_SIZE 512

int min(int a, int b);

ResSearch* ida(State initial_state, State goal);

int fEtat(Action act);

int heuristic(State init, State goal);

bool bounded_depth(List* buff, List* done, List *path,State initial_state);






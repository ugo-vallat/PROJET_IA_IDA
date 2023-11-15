

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    Tree *t = malloc(sizeof(Tree));
    t->pere = 2;
    printf("t = %d\n", t->pere);
    return 0;
}
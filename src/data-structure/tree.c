
#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "state.h"
#include "tree.h"
#include "utils.h"

/**
 * @brief Initialise les lien vers les fils à NULL
 * 
 * @param a Arbre à initialiser
 */
void init_tree_link(Tree* t) {
    testArgNull(t, "init_tree_link");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            t->child[i][j].tree_dst = NULL;
            t->child[i][j].tree_src = t;
        }
    }
    t->parent.tree_dst = t;
    t->parent.tree_src = NULL;
}


Tree* createTree(State s) {
    Tree * t = malloc(sizeof(Tree));
    init_tree_link(t);
    t->state = s;
    t->depth = 0;
    return t;
}


void addLeaf(Tree* t, State s, Move m) {
    testArgNull(t, "addLeaf");
    testMoveIsValid(m, "addLeaf");

    Tree *st = malloc(sizeof(Tree));
    init_tree_link(st);

    st->depth = t->depth++;
    st->state = s;
    st->parent.tree_src = t;
    st->parent.move = m;

    t->child[m.stem_src][m.stem_dst].move = m;
    t->child[m.stem_src][m.stem_dst].tree_dst = st;
}

bool existChild(Tree* t, int stem_src, int stem_dst) {
    testArgNull(t, "existChild");
    testStemValid(stem_src, "getChild");
    testStemValid(stem_dst, "getChild");
    
    return t->child[stem_src][stem_dst].tree_dst != NULL;
}

Move getMov(Tree* t, int stem_src, int stem_dst) {
    testArgNull(t, "getMov");
    testStemValid(stem_src, "getChild");
    testStemValid(stem_dst, "getChild");

    return t->child[stem_src][stem_dst].move;
}

Tree* getChild(Tree* t, int stem_src, int stem_dst) {
    testArgNull(t, "getChild");
    testStemValid(stem_src, "getChild");
    testStemValid(stem_dst, "getChild");
    return t->child[stem_src][stem_dst].tree_dst;
}

Tree* getParent(Tree* t) {
    testArgNull(t, "getParent");
    return t->parent.tree_src;
}


bool isRoot(Tree* t) {
    testArgNull(t, "isRoot");
    return t->parent.tree_src == NULL;
}

unsigned getDepth(Tree *t) {
    testArgNull(t, "getDepth");
    return t->depth;
}

bool isLeaf(Tree *t) {
    testArgNull(t, "isLeaf");
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(existChild(t, i, j))
                return false;
        }
    }
    return true;
}
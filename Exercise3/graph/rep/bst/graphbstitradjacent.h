
#ifndef GRAPHBSTITRADJACENT_H
#define GRAPHBSTITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"
#include "graphbst.h"

/* ************************************************************************** */

typedef struct BSTItrInterface {
    int vertexName;
    AdjacentBSTLst* adjacentTree;
    GraphBST* graphBST;
} BSTItrInterface;

typedef struct GraphBSTAdjacentIterator {
    BSTItrInterface* bstInterface;
    ITRObject* treeIterator;
} GraphBSTAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructBSTAdjacentIterator();
void DestructBSTAdjacentIterator(ITRType* type);

/* ************************************************************************** */

BSTItrInterface* initializeBSTIterator(int name, void* graphBST);


#endif

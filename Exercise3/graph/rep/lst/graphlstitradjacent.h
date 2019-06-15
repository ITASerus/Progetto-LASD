
#ifndef GRAPHLSTITRADJACENT_H
#define GRAPHLSTITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"
#include "graphlst.h"

/* ************************************************************************** */

typedef struct LstItrInterface {
    int vertexName;
    AdjacentLst* adjacent;
} LstItrInterface;

typedef struct GraphLstAdjacentIterator {
    LstItrInterface* element;
} GraphLstAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructLstAdjacentIterator();
void DestructLstAdjacentIterator(ITRType* type);

/* ************************************************************************** */

LstItrInterface* initializeLstIterator(int name, void* adjacentLst);

#endif


#ifndef GRAPHMATITRADJACENT_H
#define GRAPHMATITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"
#include "graphmat.h"

/* ************************************************************************** */

typedef struct MatItrInterface {
    int vertexName;
    int rowVertex;
    GraphMat* graphMat;
} MatItrInterface;

typedef struct GraphMatAdjacentIterator {
    MatItrInterface* matInterface;
    int currentElement;
} GraphMatAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructMatAdjacentIterator();
void DestructMatAdjacentIterator(ITRType* type);

/* ************************************************************************** */

MatItrInterface* initializeMatIterator(int name, void* adjacentMatrix);

#endif

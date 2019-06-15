
#ifndef GRAPHMATITRADJACENT_H
#define GRAPHMATITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"

#include "graphmat.h"

/* ************************************************************************** */

typedef struct GraphMatAdjacentIterator {
    AdjacentMatrix* adjacentMatrix;
    int currentRow;
    int currentColumn;
} GraphMatAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructMatAdjacentIterator();
void DestructMatAdjacentIterator(ITRType* type);

/* ************************************************************************** */

#endif

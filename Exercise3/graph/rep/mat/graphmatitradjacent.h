
#ifndef GRAPHMATITRADJACENT_H
#define GRAPHMATITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"

#include "graphmat.h"

/* ************************************************************************** */

typedef struct GraphMatAdjacentIterator {
    bool** element;
    int numVertex;
} GraphMatAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructMatAdjacentIterator();
void DestructMatAdjacentIterator(ITRType* type);

/* ************************************************************************** */

#endif

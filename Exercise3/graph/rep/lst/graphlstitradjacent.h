
#ifndef GRAPLSTITRADJACENT_H
#define GRAPLSTITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"

#include "graphlst.h"

/* ************************************************************************** */

typedef struct GraphLstAdjacentIterator {
    AdjacentLst* element;
} GraphLstAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructLstAdjacentIterator();
void DestructLstAdjacentIterator(ITRType* type);

/* ************************************************************************** */

#endif


#ifndef GRAPHITRVERTEX_H
#define GRAPHITRVERTEX_H

/* ************************************************************************** */

#include "graph.h"

/* ************************************************************************** */

typedef struct GraphVertexIterator {
    VertexLst* element;
} GraphVertexIterator;

/* ************************************************************************** */

ITRType* ConstructVertexIterator();
void DestructVertexIterator(ITRType* type);

/* ************************************************************************** */

#endif

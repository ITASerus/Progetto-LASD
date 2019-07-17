
#ifndef GRAPHITRPOSTORD_H
#define GRAPHITRPOSTORD_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../stack/stack.h"

#include "graph.h"

/* ************************************************************************** */

typedef struct SupportPost {
    int name;
    char color;
} SupportPost;

typedef struct GraphPostOrderIterator {
    GraphObject* graph;
    Vertex* currentVertex;
    SupportPost* support;

    StackObject* stackVertices;
    StackObject* stackAdjacent;
    StackObject* stackIndexes;

    int indexVertices;
    ITRObject* verticesIterator;
    ITRObject* currentAdjIterator;

    DataType *ptrType;
} GraphPostOrderIterator;

/* ************************************************************************** */

ITRType* ConstructGraphPostOrderIterator();
void DestructGraphPostOrderIterator(ITRType* type);

/* ************************************************************************** */

#endif

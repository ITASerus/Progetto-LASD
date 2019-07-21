
#ifndef GRAPHITRBREADTH_H
#define GRAPHITRBREADTH_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../queue/queue.h"

#include "graph.h"

/* ************************************************************************** */

typedef struct SupportBreadth {
    int name;
    char color;
} SupportBreadth;

typedef struct GraphBreadthIterator {
    GraphObject* graph;
    Vertex* currentVertex;
    SupportBreadth* support;

    QueueObject* queue;

    ITRObject* verticesIterator;

    DataType* intType;
} GraphBreadthIterator;

/* ************************************************************************** */

ITRType* ConstructGraphBreadthIterator();
void DestructGraphBreadthIterator(ITRType* type);

/* ************************************************************************** */

#endif

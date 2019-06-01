
#ifndef GRAPHLST_H
#define GRAPHLST_H

/* ************************************************************************** */

#include "../../graph.h"

/* ************************************************************************** */

typedef struct AdjacentVertex AdjacentVertex;
struct AdjacentVertex {
    void* vertexPointer;
    AdjacentVertex* next;
};

typedef struct Vertex {
    int name;
    DataObject* label;
} Vertex;

typedef struct GraphLst GraphLst;
struct GraphLst {
    Vertex* vertexInfo;
    AdjacentVertex* adjacentLst;

    GraphLst* next;
};

/* ************************************************************************** */

GraphRepresentation* ConstructGraphLst();
void DestructGraphLst(GraphRepresentation* type);

/* ************************************************************************** */

#endif

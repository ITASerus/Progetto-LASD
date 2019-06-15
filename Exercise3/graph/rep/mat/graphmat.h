
#ifndef GRAPHMAT_H
#define GRAPHMAT_H

/* ************************************************************************** */

#include "../../graph.h"

/* ************************************************************************** */

typedef struct AdjacentMatrix{
    bool** matrix;

    int numVertex;
    int slotAllocated;
} AdjacentMatrix;

typedef struct GraphMat {
  VertexLst* vertexLst;
  AdjacentMatrix* adjacentMatrix;
} GraphMat;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphMat();
void DestructGraphMat(GraphRepresentation* type);

/* ************************************************************************** */

#endif

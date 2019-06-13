
#ifndef GRAPHMAT_H
#define GRAPHMAT_H

/* ************************************************************************** */

#include "../../graph.h"

/* ************************************************************************** */

typedef struct Matrix{
    bool** adjacentMatrix;
    int slotAllocated;

    int numVertex;
} Matrix;

typedef struct GraphMat {
  VertexLst* vertexLst;
  Matrix* adjacentMatrix;

  /*
  bool** adjacentMatrix;
  int slotAllocated;

  int numVertex;*/
} GraphMat;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphMat();
void DestructGraphMat(GraphRepresentation* type);

/* ************************************************************************** */

#endif

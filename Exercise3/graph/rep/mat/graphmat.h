
#ifndef GRAPHMAT_H
#define GRAPHMAT_H

/* ************************************************************************** */

#include "../../graph.h"

/* ************************************************************************** */

typedef struct GraphMat {
  VertexLst* vertexLst;

  bool** adjacentMatrix;
  int slotAllocated;

  int numVertex;
} GraphMat;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphMat();
void DestructGraphMat(GraphRepresentation* type);

/* ************************************************************************** */

#endif

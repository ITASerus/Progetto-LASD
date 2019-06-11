
#ifndef GRAPHBST_H
#define GRAPHBST_H

/* ************************************************************************** */

#include "../../graph.h"

#include "../../../bst/bst.h"

/* ************************************************************************** */

typedef struct AdjacentBSTLst AdjacentBSTLst;
struct AdjacentBSTLst {
    Vertex* vertexPointer;
    BSTObject* adjacentTree;
    AdjacentBSTLst* nextVertex;
};

typedef struct GraphBST {
    VertexLst* vertexLst;
    AdjacentBSTLst* adjacentBSTLst;
} GraphBST;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphBST();
void DestructGraphBST(GraphRepresentation* type);

/* ************************************************************************** */

#endif

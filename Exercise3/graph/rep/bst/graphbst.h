/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

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

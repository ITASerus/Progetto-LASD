/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

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

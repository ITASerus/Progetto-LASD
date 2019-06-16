/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef GRAPHBSTITRADJACENT_H
#define GRAPHBSTITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"
#include "graphbst.h"

/* ************************************************************************** */

typedef struct BSTItrInterface {
    int vertexName;
    AdjacentBSTLst* adjacentTree;
    GraphBST* graphBST;
} BSTItrInterface;

typedef struct GraphBSTAdjacentIterator {
    BSTItrInterface* bstInterface;
    ITRObject* treeIterator;
} GraphBSTAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructBSTAdjacentIterator();
void DestructBSTAdjacentIterator(ITRType* type);

/* ************************************************************************** */

BSTItrInterface* initializeBSTIterator(int name, void* graphBST);


#endif

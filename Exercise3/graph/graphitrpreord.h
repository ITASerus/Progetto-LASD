/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef GRAPHITRPREORD_H
#define GRAPHITRPREORD_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../stack/stack.h"

#include "graph.h"

/* ************************************************************************** */

typedef struct SupportPre {
    int name;
    char color;
} SupportPre;

typedef struct GraphPreOrderIterator {
    GraphObject* graph;
    Vertex* currentVertex;
    SupportPre* support;

    StackObject* stackVertices;
    StackObject* stackAdjacent;

    int indexVertices;
    ITRObject* verticesIterator;
    ITRObject* currentAdjIterator;

    DataType *ptrType;
} GraphPreOrderIterator;

/* ************************************************************************** */

ITRType* ConstructGraphPreOrderIterator();
void DestructGraphPreOrderIterator(ITRType* type);

/* ************************************************************************** */

#endif

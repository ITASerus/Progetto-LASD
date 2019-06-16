/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef GRAPHMATITRADJACENT_H
#define GRAPHMATITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"
#include "graphmat.h"

/* ************************************************************************** */

typedef struct MatItrInterface {
    int vertexName;
    int rowVertex;
    GraphMat* graphMat;
} MatItrInterface;

typedef struct GraphMatAdjacentIterator {
    MatItrInterface* matInterface;
    int currentElement;
} GraphMatAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructMatAdjacentIterator();
void DestructMatAdjacentIterator(ITRType* type);

/* ************************************************************************** */

MatItrInterface* initializeMatIterator(int name, void* adjacentMatrix);

#endif

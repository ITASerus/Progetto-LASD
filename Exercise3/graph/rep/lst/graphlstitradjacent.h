/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef GRAPHLSTITRADJACENT_H
#define GRAPHLSTITRADJACENT_H

/* ************************************************************************** */

#include "graph.h"
#include "graphlst.h"

/* ************************************************************************** */

typedef struct LstItrInterface {
    int vertexName;
    AdjacentLst* adjacent;
} LstItrInterface;

typedef struct GraphLstAdjacentIterator {
    LstItrInterface* element;
} GraphLstAdjacentIterator;

/* ************************************************************************** */

ITRType* ConstructLstAdjacentIterator();
void DestructLstAdjacentIterator(ITRType* type);

/* ************************************************************************** */

LstItrInterface* initializeLstIterator(int name, void* adjacentLst);

#endif

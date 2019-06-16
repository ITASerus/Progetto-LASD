/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef GRAPHLST_H
#define GRAPHLST_H

/* ************************************************************************** */

#include "../../graph.h"

/* ************************************************************************** */

//Struttura che rappresenta un nodo della lista dei vertici adiacenti al vertce puntato da vertexPoiner
typedef struct AdjacentLst AdjacentLst;
struct AdjacentLst {
    Vertex* vertexPointer;
    AdjacentLst* nextAdjacent;
    AdjacentLst* nextVertex;
};

//Struttura che rappresenta l'intero grafo sottoforma di lista di adiacenza
typedef struct GraphLst {
    VertexLst* vertexLst;
    AdjacentLst* adjacentVertexLst;
} GraphLst;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphLst();
void DestructGraphLst(GraphRepresentation* type);

/* ************************************************************************** */

#endif

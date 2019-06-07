
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

//Struttura che rappresenta l'intero grafo rappresentato sottoforma di lista di adiacenza
typedef struct GraphLst {
    VertexLst* vertexLst;
    AdjacentLst* adjacentVertexLst;
} GraphLst;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphLst();
void DestructGraphLst(GraphRepresentation* type);

/* ************************************************************************** */

#endif

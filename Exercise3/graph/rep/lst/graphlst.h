
#ifndef GRAPHLST_H
#define GRAPHLST_H

/* ************************************************************************** */

#include "../../graph.h"

/* ************************************************************************** */

//Struttura che rappresenta le informazioni di un vertice del grafo
typedef struct Vertex {
    int name;
    DataObject* label;
} Vertex;

//Struttura che rappresenta un nodo della lista dei vertici adiacenti al vertce puntato da vertexPoiner
typedef struct AdjacenLst AdjacenLst;
struct AdjacenLst {
    Vertex* vertexPointer;
    AdjacenLst* nextAdjacent;
    AdjacenLst* nextVertex;
};

//Struttura che rappresenta la lista dei vertici presenti nel grafo
typedef struct VertexLst VertexLst;
struct VertexLst {
    Vertex* vertexInfo;
    VertexLst* nextVertex;
};

//Struttura che rappresenta l'intero grafo rappresentato sottoforma di lista di adiacenza
typedef struct GraphLst {
    VertexLst* vertexLst;
    AdjacenLst* adjacentVertexLst;
} GraphLst;

/* ************************************************************************** */

GraphRepresentation* ConstructGraphLst();
void DestructGraphLst(GraphRepresentation* type);

/* ************************************************************************** */

#endif

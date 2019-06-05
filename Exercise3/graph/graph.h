
#ifndef GRAPH_H
#define GRAPH_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

#include "../itr/itr.h"

/* ************************************************************************** */

typedef void* (*GraphConstruct)(void*);
typedef void (*GraphDestruct)(void*);

typedef bool (*GraphEmpty)(void*);

typedef void* (*GraphClone)(void*);
// typedef type (*GraphTranspose)(arguments);

typedef void (*GraphInsertVertex)(void* graph, int name, DataObject* label);
typedef void (*GraphRemoveVertex)(void* graph, int name);
typedef void (*GraphInsertEdge)(void* graph, int fromVertexName, int toVertexName);
typedef void (*GraphRemoveEdge)(void* graph, int fromVertexName, int toVertexName);

typedef bool (*GraphExistsVertex)(void* graph, int name);
typedef bool (*GraphExistsEdge)(void* graph, int fromVertexName, int toVertexName);

// typedef type (*GraphGetVertexData)(arguments);
// typedef type (*GraphSetVertexData)(arguments);

// typedef type (*GraphVertexFromPointer)(arguments); //restituisce nome del nodo puntato

// typedef type (*GraphVertices)(arguments); //Restituisce iteratore che  permette di iterare su tutti i nodi. Collegata con GraphVertexFromPointer Deferenzi/referenzi ecc
// typedef type (*GraphVertexEdges)(arguments); //Restituisce iteratore

//----

typedef bool (*GraphEqual)(void* firstGraph, void* secondGraph);

typedef int (*GraphShortestPath)(void*, void*); //Lunghezza Se tra due nodi non esiste un percorso, restituisco -1

// typedef type (*GraphIsAcyclic)(arguments);
// typedef type (*GraphTopologicalOrder)(arguments); Restituisce iteratore

typedef void* (*GraphMaximalReachableSubgraph)(void*);// Restituisce grafo nuovo, separato e e riallocato

// typedef type (*GraphSCCGraph)(arguments); Grafo delle componenti fortemente connesse. I dati sono il nome di uno dei vertici (DatObject Intero)a cui la componente fa riferimento

// typedef type (*GraphPreOrderMap)(arguments);
// typedef type (*GraphPostOrderMap)(arguments);
// typedef type (*GraphBreadthMap)(arguments);
// typedef type (*GraphPreOrderFold)(arguments);
// typedef type (*GraphPostOrderFold)(arguments);
// typedef type (*GraphBreadthFold)(arguments);

/* ************************************************************************** */

typedef struct GraphRepresentation {
  GraphConstruct graphConstruct;
  //GraphDestruct graphDestruct;
  GraphEmpty graphEmpty;
  //GraphClone graphClone;
  GraphInsertVertex graphInsertVertex;
  GraphRemoveVertex graphRemoveVertex;
  GraphInsertEdge  graphInsertEdge;
  GraphExistsVertex graphExistsVertex;
  GraphExistsEdge graphExistsEdge;
} GraphRepresentation;

typedef struct GraphType { //void* puntatore alla rappresentazione + graphrapresentation*
  GraphRepresentation* graphRep;
  //Struct da completare!
} GraphType;

typedef struct GraphObject
{
  // Struct da completare! void* matrice, lista e albero
  GraphType* type;
  void* graph;

} GraphObject;

/* ************************************************************************** */

GraphObject* graphConstruct(GraphType* type);
void graphDestruct(GraphObject* graphObject);

bool graphEmpty(GraphObject* graphObject);

// type graphVertexNumber(arguments);
// type graphEdgeNumber(arguments);

void graphClear(GraphObject* graphObject);

GraphObject* graphClone(GraphObject* graphObject);

// type graphTranspose(arguments);

void graphInsertVertex(GraphObject* graphObject, int name, DataObject* label); //TODO: Bool?
void graphRemoveVertex(GraphObject* graphObject, int name);
void graphInsertEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);
void graphRemoveEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);

bool graphExistsVertex(GraphObject* graphObject, int name); //TODO: prende solo nome o anche dataobject?
bool graphExistsEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);

// type graphGetVertexData(arguments);
// type graphSetVertexData(arguments);

// type graphVertexFromPointer(arguments);

// type graphVertices(arguments);
// type graphVertexEdges(arguments);

// type graphEqual(arguments);

// type graphExistsVertexWithData(arguments);

// type graphShortestPath(arguments);

// type graphIsAcyclic(arguments);
// type graphTopologicalOrder(arguments);

// type graphMaximalReachableSubgraph(arguments);

// type graphSCCGraph(arguments);

// type graphPreOrderMap(arguments);
// type graphPostOrderMap(arguments);
// type graphBreadthMap(arguments);
// type graphPreOrderFold(arguments);
// type graphPostOrderFold(arguments);
// type graphBreadthFold(arguments);

/* ************************************************************************** */

#endif

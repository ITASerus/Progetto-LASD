
#ifndef GRAPH_H
#define GRAPH_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

#include "../itr/itr.h"

/* ************************************************************************** */

typedef void* (*GraphConstruct)(void* type);
typedef void (*GraphDestruct)(void* graph);

typedef bool (*GraphEmpty)(void* graph);

typedef void* (*GraphClone)(void* graph);
typedef void* (*GraphTranspose)(void* graph);

typedef bool (*GraphInsertVertex)(void* graph, int name, DataObject* label);
typedef int (*GraphRemoveVertex)(void* graph, int name);
typedef bool (*GraphInsertEdge)(void* graph, int fromVertexName, int toVertexName);
typedef bool (*GraphRemoveEdge)(void* graph, int fromVertexName, int toVertexName);

typedef bool (*GraphExistsVertex)(void* graph, int name);
typedef bool (*GraphExistsEdge)(void* graph, int fromVertexName, int toVertexName);

typedef DataObject* (*GraphGetVertexData)(void* graph, int name);
typedef void (*GraphSetVertexData)(void* graph, int name, DataObject* newValue);

// typedef type (*GraphVertexFromPointer)(arguments); //restituisce nome del nodo puntato

// typedef type (*GraphVertices)(arguments); //Restituisce iteratore che  permette di iterare su tutti i nodi. Collegata con GraphVertexFromPointer Deferenzi/referenzi ecc
// typedef type (*GraphVertexEdges)(arguments); //Restituisce iteratore

//----

typedef bool (*GraphEqual)(void* firstGraph, void* secondGraph);

typedef int (*GraphShortestPath)(void*, void*); //Lunghezza, Se tra due nodi non esiste un percorso, restituisco -1

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

//Struttura che rappresenta le informazioni di un vertice del grafo
typedef struct Vertex {
    int name;
    DataObject* label;
} Vertex;

//Struttura che rappresenta la lista dei vertici presenti nel grafo
typedef struct VertexLst VertexLst;
struct VertexLst {
    Vertex* vertexInfo;
    VertexLst* nextVertex;
};

typedef struct GraphRepresentation {
  GraphConstruct graphConstruct;
  GraphDestruct graphDestruct;

  GraphEmpty graphEmpty;

  GraphClone graphClone;
  GraphTranspose graphTranspose;

  GraphInsertVertex graphInsertVertex;
  GraphRemoveVertex graphRemoveVertex;
  GraphInsertEdge  graphInsertEdge;
  GraphRemoveEdge  graphRemoveEdge;

  GraphExistsVertex graphExistsVertex;
  GraphExistsEdge graphExistsEdge;

  GraphGetVertexData graphGetVertexData;
  GraphSetVertexData  graphSetVertexData;

} GraphRepresentation;

typedef struct GraphType { //void* puntatore alla rappresentazione + graphrapresentation*
  GraphRepresentation* graphRep;
  //Struct da completare!
} GraphType;

typedef struct GraphObject
{
  GraphType* type;
  void* graph;

  int numVertex;
  int numEdge;

} GraphObject;

/* ************************************************************************** */

GraphObject* graphConstruct(GraphType* type);
void graphDestruct(GraphObject* graphObject);

bool graphEmpty(GraphObject* graphObject);

int graphVertexNumber(GraphObject* graphObject);
int graphEdgeNumber(GraphObject* graphObject);

void graphClear(GraphObject* graphObject);

GraphObject* graphClone(GraphObject* graphObject);

GraphObject* graphTranspose(GraphObject* graphObject);

void graphInsertVertex(GraphObject* graphObject, int name, DataObject* label); //TODO: Bool?
void graphRemoveVertex(GraphObject* graphObject, int name);
void graphInsertEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);
void graphRemoveEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);

bool graphExistsVertex(GraphObject* graphObject, int name);
bool graphExistsEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);

DataObject* graphGetVertexData(GraphObject* graphObject, int name);
void graphSetVertexData(GraphObject* graphObject, int name, DataObject* newValue);

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

Vertex* createVertex(int name, DataObject* label);
VertexLst* createVertexLstElement(Vertex* vertexInfo, VertexLst* next);
void deleteVertexLstElem(VertexLst* vertexLstElem);

#endif

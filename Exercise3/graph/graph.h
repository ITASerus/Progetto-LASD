
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

typedef int (*GraphVertexFromPointer)(void* iterator);

typedef ITRObject* (*GraphVertices)(void* graph);
typedef ITRObject* (*GraphVertexEdges)(void* graph, int name);

typedef bool (*GraphEqual)(void* firstGraph, void* firstGraphRepresentation, void* secondGraph, void* secondGraphRepresentation);

typedef int (*GraphShortestPath)(void* graph, int numVertex, void* graphRepresentation, int firstName, int secondName);

// typedef type (*GraphIsAcyclic)(arguments);
// typedef type (*GraphTopologicalOrder)(arguments);

//typedef void* (*GraphMaximalReachableSubgraph)(void*);

// typedef type (*GraphSCCGraph)(arguments);

typedef void (*GraphPreOrderMap)(void* graph, void* graphRepresentation, MapFun mapFunction, void* parameter);
typedef void (*GraphPostOrderMap)(void* graph, void* graphRepresentation, MapFun mapFunction, void* parameter);
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

  GraphVertexFromPointer graphVertexFromPointer;

  GraphVertices graphVertices;
  GraphVertexEdges graphVertexEdges;

} GraphRepresentation;

typedef struct GraphType {
  GraphRepresentation* graphRep;

  GraphEqual graphEqual;

  GraphShortestPath graphShortestPath;

  GraphPreOrderMap graphPreOrderMap;
  GraphPostOrderMap graphPostOrderMap;

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

void graphInsertVertex(GraphObject* graphObject, int name, DataObject* label);
void graphRemoveVertex(GraphObject* graphObject, int name);
void graphInsertEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);
void graphRemoveEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);

bool graphExistsVertex(GraphObject* graphObject, int name);
bool graphExistsEdge(GraphObject* graphObject, int fromVertexName, int toVertexName);

DataObject* graphGetVertexData(GraphObject* graphObject, int name);
void graphSetVertexData(GraphObject* graphObject, int name, DataObject* newValue);

int graphVertexFromPointer(GraphObject* graphObject, ITRObject* iterator);

ITRObject* graphVertices(GraphObject* graphObject);
ITRObject* graphVertexEdges(GraphObject* graphObject, int name);

bool graphEqual(GraphObject* firstGraphObject, GraphObject* secondGraphObject);

// type graphExistsVertexWithData(arguments);

int graphShortestPath(GraphObject* graphObject, int firstName, int secondName);

// type graphIsAcyclic(arguments);
// type graphTopologicalOrder(arguments);

// type graphMaximalReachableSubgraph(arguments);

// type graphSCCGraph(arguments);

void graphPreOrderMap(GraphObject* graphObject, MapFun mapFunction, void* parameter);
void graphPostOrderMap(GraphObject* graphObject, MapFun mapFunction, void* parameter);
// type graphBreadthMap(arguments);
// type graphPreOrderFold(arguments);
// type graphPostOrderFold(arguments);
// type graphBreadthFold(arguments);

/* ************************************************************************** */

Vertex* createVertex(int name, DataObject* label);
VertexLst* createVertexLstElement(Vertex* vertexInfo, VertexLst* next);
void deleteVertexLstElem(VertexLst* vertexLstElem);

#endif


#include "graph.h"

/* ************************************************************************** */

GraphObject* graphConstruct(GraphType* type) {
    GraphObject* object = (GraphObject*)malloc(sizeof(GraphObject));

    object->type = type;
    object->graph = type->graphRep->graphConstruct(type);

    object->numVertex = 0;
    object->numEdge = 0;

    return object;
}

void graphDestruct(GraphObject* graphObject) { //TODO: ATTENZIONE A QUANDO VIENE USATA. Il grafo dopo sembra ancora utilizzabile ma in realtà non lo è. trova il modo di mettere a null
    graphObject->type->graphRep->graphDestruct(graphObject->graph);

    graphObject->numVertex = 0;
    graphObject->numEdge = 0;

    free(graphObject);
}

bool graphEmpty(GraphObject* graphObject) {
    return graphObject->type->graphRep->graphEmpty(graphObject->graph);
}

int graphVertexNumber(GraphObject* graphObject) {
    return graphObject->numVertex;
}

int graphEdgeNumber(GraphObject* graphObject) {
    return graphObject->numEdge;
}

GraphObject* graphClone(GraphObject* graphObject) { //TODO: Assicurati di copiare anche labeò
    GraphObject* clonedGraphObject =(GraphObject*)malloc(sizeof(GraphObject));
    clonedGraphObject->type = graphObject->type;
    clonedGraphObject->graph = graphObject->type->graphRep->graphClone(graphObject->graph);

    clonedGraphObject->numVertex = graphObject->numVertex;
    clonedGraphObject->numEdge = graphObject->numEdge;

    return clonedGraphObject;
}

GraphObject* graphTranspose(GraphObject* graphObject) { //TODO: Assicurati di copiare anche label
    GraphObject* transposedGraphObject =(GraphObject*)malloc(sizeof(GraphObject));
    transposedGraphObject->type = graphObject->type;
    transposedGraphObject->graph = graphObject->type->graphRep->graphTranspose(graphObject->graph);

    transposedGraphObject->numVertex = graphObject->numVertex;
    transposedGraphObject->numEdge = graphObject->numEdge;

    return transposedGraphObject;
}

void graphInsertVertex(GraphObject* graphObject, int name, DataObject* label) {
    if(graphObject->type->graphRep->graphInsertVertex(graphObject->graph, name, label)) {
        graphObject->numVertex++;
    }
}

void graphRemoveVertex(GraphObject* graphObject, int name) {
    int adjacentRemoved = graphObject->type->graphRep->graphRemoveVertex(graphObject->graph, name);

    if(adjacentRemoved != -1) {
        graphObject->numVertex--;
        graphObject->numEdge -= adjacentRemoved;
    }

}

void graphInsertEdge(GraphObject* graphObject, int fromVertexName, int toVertexName) {
    if(graphObject->type->graphRep->graphInsertEdge(graphObject->graph, fromVertexName, toVertexName)) {
        graphObject->numEdge++;
    }
}

void graphRemoveEdge(GraphObject* graphObject, int fromVertexName, int toVertexName) {
    if(graphObject->type->graphRep->graphRemoveEdge(graphObject->graph, fromVertexName, toVertexName)) {
        graphObject->numEdge--;
    }
}

bool graphExistsVertex(GraphObject* graphObject, int name) {
    return graphObject->type->graphRep->graphExistsVertex(graphObject->graph, name);
}

bool graphExistsEdge(GraphObject* graphObject, int fromVertexName, int toVertexName) {
    return graphObject->type->graphRep->graphExistsEdge(graphObject->graph, fromVertexName, toVertexName);
}

DataObject* graphGetVertexData(GraphObject* graphObject, int name) {
    return graphObject->type->graphRep->graphGetVertexData(graphObject->graph, name);
}

void graphSetVertexData(GraphObject* graphObject, int name, DataObject* newValue) {
    graphObject->type->graphRep->graphSetVertexData(graphObject->graph, name, newValue);
}

/* ************************************************************************** */

Vertex* createVertex(int name, DataObject* label) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

    newVertex->name = name;
    newVertex->label = adtClone(label);

    return newVertex;
}

VertexLst* createVertexLstElement(Vertex* vertexInfo, VertexLst* next) {
    VertexLst *newVertexLstElement = (VertexLst *) malloc(sizeof(VertexLst));

    newVertexLstElement->vertexInfo = vertexInfo;
    newVertexLstElement->nextVertex = next;

    return newVertexLstElement;
}

void deleteVertexLstElem(VertexLst* vertexLstElem){
    adtDestruct(vertexLstElem->vertexInfo->label);
    free(vertexLstElem);
}
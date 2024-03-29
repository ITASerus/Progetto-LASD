/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

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

void graphDestruct(GraphObject* graphObject) {
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

void graphClear(GraphObject* graphObject) {
    ITRObject* vertexIterator = graphVertices(graphObject);

    while(!itrTerminated(vertexIterator)) {
        ITRObject* adjacentIterator = graphVertexEdges(graphObject, ((Vertex*)itrElement(vertexIterator))->name);

        while(!itrTerminated(adjacentIterator)) {
            int adjacent = ((Vertex*)itrElement(adjacentIterator))->name;
            itrSuccessor(adjacentIterator);
            graphRemoveEdge(graphObject, ((Vertex*)itrElement(vertexIterator))->name, adjacent);
        }
        int vertex =  ((Vertex*)itrElement(vertexIterator))->name;
        itrSuccessor(vertexIterator);
        graphRemoveVertex(graphObject, vertex);

        itrDestruct(adjacentIterator);
    }

    itrDestruct(vertexIterator);
}

GraphObject* graphClone(GraphObject* graphObject) {
    GraphObject* clonedGraphObject =(GraphObject*)malloc(sizeof(GraphObject));
    clonedGraphObject->type = graphObject->type;
    clonedGraphObject->graph = graphObject->type->graphRep->graphClone(graphObject->graph);

    clonedGraphObject->numVertex = graphObject->numVertex;
    clonedGraphObject->numEdge = graphObject->numEdge;

    return clonedGraphObject;
}

GraphObject* graphTranspose(GraphObject* graphObject) {
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

int graphVertexFromPointer(GraphObject* graphObject, ITRObject* iterator) {
    return graphObject->type->graphRep->graphVertexFromPointer(iterator);
}

ITRObject* graphVertices(GraphObject* graphObject) {
    return  graphObject->type->graphRep->graphVertices(graphObject->graph);
}

ITRObject* graphVertexEdges(GraphObject* graphObject, int name) {
    return  graphObject->type->graphRep->graphVertexEdges(graphObject->graph, name);
}

bool graphEqual(GraphObject* firstGraphObject, GraphObject* secondGraphObject) {
    return firstGraphObject->type->graphEqual(firstGraphObject->graph, firstGraphObject->type->graphRep, secondGraphObject->graph, secondGraphObject->type->graphRep);
}

int graphShortestPath(GraphObject* graphObject, int firstName, int secondName) {
    return graphObject->type->graphShortestPath(graphObject->graph, graphObject->numVertex, graphObject->type->graphRep, firstName, secondName);
}

bool graphIsAcyclic(GraphObject* graphObject) {
    return graphObject->type->graphIsAcyclic(graphObject);
}

void graphPreOrderMap(GraphObject* graphObject, MapFun mapFunction, void* parameter) {
    graphObject->type->graphPreOrderMap(graphObject, graphObject->type->graphRep, mapFunction, parameter);
}

void graphPostOrderMap(GraphObject* graphObject, MapFun mapFunction, void* parameter) {
    graphObject->type->graphPostOrderMap(graphObject, graphObject->type->graphRep, mapFunction, parameter);
}

void graphBreadthMap(GraphObject* graphObject, MapFun mapFunction, void* parameter) {
    graphObject->type->graphBreadthMap(graphObject, graphObject->type->graphRep, mapFunction, parameter);
}

void graphPreOrderFold(GraphObject* graphObject, FoldFun foldFunction, void* accumulator, void* parameter) {
    graphObject->type->graphPreOrderFold(graphObject, graphObject->type->graphRep, foldFunction, accumulator, parameter);
}

void graphPostOrderFold(GraphObject* graphObject, FoldFun foldFunction, void* accumulator, void* parameter) {
    graphObject->type->graphPostOrderFold(graphObject, graphObject->type->graphRep, foldFunction, accumulator, parameter);
}

void graphBreadthFold(GraphObject* graphObject, FoldFun foldFunction, void* accumulator, void* parameter) {
    graphObject->type->graphBreadthFold(graphObject, graphObject->type->graphRep, foldFunction, accumulator, parameter);
}

/* ************************************************************************** */

/**
 * Crea un vertice (coppia nome-etichetta)
 * @param name Nome del vertice
 * @param label Etichetta del vertice
 * @return Nuova istanza di un vertice con i dati passati come parametro
 */
Vertex* createVertex(int name, DataObject* label) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

    newVertex->name = name;
    newVertex->label = adtClone(label);

    return newVertex;
}

/**
 * Crea una istanza di VertexLst, ovvero una linked-list di vertici (Vertex*)
 * @param vertexInfo Vertice a cui si riferirà la nuova istanza VertexLst
 * @param next Nodo successivo della linked-list di VertexLst
 * @return Nuova istanza di VertexLst
 */
VertexLst* createVertexLstElement(Vertex* vertexInfo, VertexLst* next) {
    VertexLst *newVertexLstElement = (VertexLst *) malloc(sizeof(VertexLst));

    newVertexLstElement->vertexInfo = vertexInfo;
    newVertexLstElement->nextVertex = next;

    return newVertexLstElement;
}

/**
 * Elimina un nodo nella linked-list di VertexLst
 * @param vertexLstElem Nodo da eliminare
 */
void deleteVertexLstElem(VertexLst* vertexLstElem){
    adtDestruct(vertexLstElem->vertexInfo->label);
    free(vertexLstElem);
}
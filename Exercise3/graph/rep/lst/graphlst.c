
#include "graphlst.h"

/* ************************************************************************** */

void* lstGraphConstruct() {
    GraphLst* newVertex = (GraphLst*)malloc(sizeof(GraphLst));

    newVertex->vertexInfo = NULL;
    newVertex->adjacentLst = NULL;

    newVertex->next = NULL;

    return newVertex;
}

void lstGraphInsertVertex(void* graph, int name, DataObject* label) { //TODO: Ottimizzare, complessità lineare
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));

    newVertex->name = name;
    newVertex->label = adtClone(label);

    GraphLst* graphLstElem = graph;
    while(graphLstElem->vertexInfo != NULL) {
        graphLstElem = graphLstElem->next;
    }

    graphLstElem->vertexInfo = newVertex;
    graphLstElem->adjacentLst = NULL;
    graphLstElem->next = lstGraphConstruct();
}

void lstGraphInsertEdge(void* graph, int fromVertexName, int toVertexName) {
    GraphLst* graphLstElem = graph;
    while(graphLstElem->vertexInfo != NULL && graphLstElem->vertexInfo->name != fromVertexName) {
        graphLstElem = graphLstElem->next;
    }

    if(graphLstElem->vertexInfo->name == fromVertexName) {
        GraphLst* tmp = graph;
        while(tmp->vertexInfo != NULL && tmp->vertexInfo->name != toVertexName) {
            tmp = tmp->next;
        }
        if(tmp != NULL) {
            AdjacentVertex* newAdjacentVertex = (AdjacentVertex*)malloc(sizeof(AdjacentVertex));

            newAdjacentVertex->vertexPointer = tmp;
            newAdjacentVertex->next = graphLstElem->adjacentLst;

            graphLstElem->adjacentLst = newAdjacentVertex;
        } else {
            printf("Vertice destinazione non trovato\n");
            return;
        }
    } else {
        printf("Vertice non trovato\n");
    }
}

bool lstGraphExistsVertex(void* graph, int name) {
    GraphLst* graphLstElem = graph;

    while(graphLstElem->vertexInfo != NULL && (graphLstElem->vertexInfo->name != name)) {
        graphLstElem = graphLstElem->next;
    }

    if(graphLstElem->vertexInfo == NULL) {
        return false;
    } else {
        return true;
    }
}

bool lstGraphEmpty(void* graph) {
    if(((GraphLst*)graph)->vertexInfo == NULL) {
        return true;
    } else {
        return false;
    }
}

GraphRepresentation* ConstructGraphLst() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = lstGraphConstruct;
    type->graphInsertVertex = lstGraphInsertVertex;
    type->graphExistsVertex = lstGraphExistsVertex;
    type->graphInsertEdge = lstGraphInsertEdge;
    type->graphEmpty = lstGraphEmpty;


    return type;
}

void DestructGraphLst(GraphRepresentation* type) {
    free(type);
}

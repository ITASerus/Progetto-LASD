
#include "graphlst.h"

/* ************************************************************************** */

void* lstGraphConstruct() {
    GraphLst* newGraphLst = (GraphLst*)malloc(sizeof(GraphLst));

    newGraphLst->vertexLst = NULL;
    newGraphLst->adjacentVertexLst = NULL;

    return newGraphLst;
}

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

void lstGraphInsertVertex(void* graph, int name, DataObject* label) {
    GraphLst* graphLst = graph;

    if(graphLst->vertexLst == NULL || graphLst->vertexLst->vertexInfo->name > name) { //Il grafo è vuoto

        //Creazione del nuovo vertice
        Vertex* newVertex = createVertex(name, label);

        /*VertexLst* newVertexLstElement = (VertexLst*)malloc(sizeof(VertexLst));
        newVertexLstElement->vertexInfo = newVertex;

        //Inserimento del vertice nella lista di vertici
        newVertexLstElement->nextVertex = graphLst->vertexLst;
        graphLst->vertexLst = newVertexLstElement;*/
        VertexLst* newVertexLstElement = createVertexLstElement(newVertex, graphLst->vertexLst);
        graphLst->vertexLst = newVertexLstElement;

        //Creazione della lista dei vertici adiacenti del nuovo nodo
        AdjacenLst* newAjdacentVertexLst = (AdjacenLst*)malloc(sizeof(AdjacenLst));
        newAjdacentVertexLst->vertexPointer = newVertex;
        newAjdacentVertexLst->nextVertex = NULL;
        newAjdacentVertexLst->nextAdjacent = NULL;

        //Inserimento della nuova lista di adiacenti nella lista di liste di adiacenti
        graphLst->adjacentVertexLst = newAjdacentVertexLst;
    } else { //Il gravo ha almeno un vertice
        VertexLst* currentVertexLstElem = graphLst->vertexLst;
        AdjacenLst* currentAdjacentLstElem = graphLst->adjacentVertexLst;

        //Localizzazione del vertice che si trova prima del punto di inserimento
        while(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name < name) {
            currentVertexLstElem = currentVertexLstElem->nextVertex;
            currentAdjacentLstElem = currentAdjacentLstElem->nextVertex;
        }

        //Creazione del nuovo vertice
        Vertex* newVertex = createVertex(name, label);

        VertexLst* newVertexLstElement = (VertexLst*)malloc(sizeof(VertexLst));
        newVertexLstElement->vertexInfo = newVertex;

        //Inserimento del vertice nella lista di vertici
        newVertexLstElement->nextVertex = currentVertexLstElem->nextVertex;
        currentVertexLstElem->nextVertex = newVertexLstElement;

        //Creazione della lista dei vertici adiacenti del nuovo nodo
        AdjacenLst* newAjdacentLstElem = (AdjacenLst*)malloc(sizeof(AdjacenLst));
        newAjdacentLstElem->vertexPointer = newVertex;

        //Inserimento della lista dei vertici adiacenti del nuovo nodo
        newAjdacentLstElem->nextVertex = currentAdjacentLstElem->nextVertex;
        newAjdacentLstElem->nextVertex = currentAdjacentLstElem;
    }
}

bool lstGraphEmpty(void* graph) {
    return ((GraphLst*)graph)->vertexLst == NULL;
}

GraphRepresentation* ConstructGraphLst() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = lstGraphConstruct;
    type->graphInsertVertex = lstGraphInsertVertex;
    //type->graphExistsVertex = lstGraphExistsVertex;
    //type->graphInsertEdge = lstGraphInsertEdge;
    type->graphEmpty = lstGraphEmpty;

    return type;
}

void DestructGraphLst(GraphRepresentation* type) {
    free(type);
}

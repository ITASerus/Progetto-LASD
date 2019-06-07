
#include "graphmat.h"

/* ************************************************************************** */

void* matGraphConstruct() {
    GraphMat* newGraphMat = (GraphMat*)malloc(sizeof(GraphMat));

    newGraphMat->vertexLst = NULL;
    newGraphMat->adjacentMatrix = NULL;

    newGraphMat->slotAllocated = 0;
    newGraphMat->numVertex = 0;

    return newGraphMat;
}

bool matGraphInsertVertex(void* graph, int name, DataObject* label) {
    GraphMat* graphMat = graph;

    if(graphMat->vertexLst == NULL || graphMat->vertexLst->vertexInfo->name > name) { //Il grafo è vuoto o il vertice da inserire ha nome più piccolo di tutti gli altri

        if(graphMat->vertexLst != NULL && graphMat->vertexLst->vertexInfo->name == name) { //Il vertice da inserire è già presente
            printf("Vertice già presente (%d - %d)\n", graphMat->vertexLst->vertexInfo->name, name);
            return false;
        }

        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElement = createVertexLstElement(newVertex, graphMat->vertexLst);
        graphMat->vertexLst = newVertexLstElement;
        graphMat->numVertex++;

        //Allocazione matrice di adiacenza
        graphMat->slotAllocated = 4;
        bool** newAdjacentMatrix = (bool**)malloc(sizeof(bool*) * graphMat->slotAllocated); //Alloco il vettore di puntatori ai vettori che comporranno la matrice
        for(int i = 0; i < graphMat->slotAllocated; i++) {
            newAdjacentMatrix[i] = malloc(sizeof(bool) * graphMat->slotAllocated); //Alloco un vettore che conterrà gli archi //TODO: Sostiuire con calloc
            for(int j = 0; j < graphMat->slotAllocated; j++) {
                newAdjacentMatrix[i][j] = false;
            }
        }

        graphMat->adjacentMatrix = newAdjacentMatrix;

    } else { //Il grafo ha almeno un vertice
        //Creazione del vertice
        VertexLst* currentVertexLstElem = graphMat->vertexLst;

        //Localizzazione del vertice che si trova prima del punto di inserimento
        while(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name < name) {
            currentVertexLstElem = currentVertexLstElem->nextVertex;
        }

        if(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name == name) { //Controllo se il vertice che si vuole inserire non sia già presente
            printf("Vertice già presente (%d - %d)\n", currentVertexLstElem->nextVertex->vertexInfo->name, name);
            return false;
        }

        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElem = createVertexLstElement(newVertex, currentVertexLstElem->nextVertex);
        currentVertexLstElem->nextVertex = newVertexLstElem;
        graphMat->numVertex++;

        //Popolamento della rispettiva zona della  matrice di adiacenza
        if(graphMat->numVertex > graphMat->slotAllocated) { //La matrice di adiacenza va ingrandita
            printf("Matrice va ingrandita\n");
        }
    }

    return true;
}

bool matGraphEmpty(void* graph) {
    return ((GraphMat*)graph)->vertexLst == NULL;
}

bool matGraphInsertEdge(void* graph, int fromVertexName, int toVertexName) { //TODO: Ottimizza sfruttando il fatto di sapere già toVertexName
    int fromVertexPos = 0;
    int toVertexPos = 0;

    VertexLst* vertexLst = ((GraphMat*)graph)->vertexLst;
    while(vertexLst != NULL && vertexLst->vertexInfo->name != fromVertexName && vertexLst->nextVertex->vertexInfo->name <= fromVertexName) {
        vertexLst = vertexLst->nextVertex;
        fromVertexPos++;
    }

    printf("from: %d\n", fromVertexPos);
    if(vertexLst != NULL && vertexLst->vertexInfo->name == fromVertexName) { //Il vertice di partenza esiste
        vertexLst = ((GraphMat*)graph)->vertexLst;
        while(vertexLst != NULL && vertexLst->vertexInfo->name != toVertexName && vertexLst->nextVertex->vertexInfo->name <= toVertexName) {
            vertexLst = vertexLst->nextVertex;
            toVertexPos++;
        }
        printf("to: %d\n", toVertexPos);
        if(vertexLst != NULL && vertexLst->vertexInfo->name == toVertexName) { //Il vertice di arrivo esiste
            ((GraphMat*)graph)->adjacentMatrix[fromVertexPos][toVertexPos] = true;
            return true;
        }
    }

    return false;
}

bool matGraphExistsEdge(void* graph, int fromVertexName, int toVertexName) {
    int fromVertexPos = 0;
    int toVertexPos = 0;

    VertexLst* vertexLst = ((GraphMat*)graph)->vertexLst;
    while(vertexLst != NULL && vertexLst->vertexInfo->name != fromVertexName && (vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name <= fromVertexName)) {
        vertexLst = vertexLst->nextVertex;
        fromVertexPos++;
    }

    if(vertexLst != NULL && vertexLst->vertexInfo->name == fromVertexName) { //Il vertice di partenza esiste
        vertexLst = ((GraphMat*)graph)->vertexLst;
        while(vertexLst != NULL && vertexLst->vertexInfo->name != toVertexName && (vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name <= toVertexName)) {
            vertexLst = vertexLst->nextVertex;
            toVertexPos++;
        }

        return ((GraphMat*)graph)->adjacentMatrix[fromVertexPos][toVertexPos];
    }

    return false;
}

GraphRepresentation* ConstructGraphMat() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = matGraphConstruct;
    //type->graphDestruct = matGraphDestruct;

    type->graphEmpty = matGraphEmpty;

    //type->graphTranspose = matGraphTranspose;

    //type->graphClone = matGraphClone;

    type->graphInsertVertex = matGraphInsertVertex;
    //type->graphRemoveVertex = matGraphRemoveVertex;
    type->graphInsertEdge = matGraphInsertEdge;
    //type->graphRemoveEdge = matGraphRemoveEdge;

    //type->graphExistsVertex = matGraphExistsVertex;
    type->graphExistsEdge = matGraphExistsEdge;

    //type->graphGetVertexData = matGraphGetVertexData;
    //type->graphSetVertexData = matGraphSetVertexData;*/

    return type;
}

void DestructGraphMat(GraphRepresentation* type) {
    free(type);
}
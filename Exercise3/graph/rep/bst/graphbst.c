
#include "graphbst.h"
#include "bst/bst.h"
#include "rec/bstrec.h"
#include "adt/int/adtint.h"

AdjacentBSTLst* createAdjacentBSTLstElem(Vertex* vertexPointer, AdjacentBSTLst* nexVertex);

/* ************************************************************************** */

void* bstGraphConstruct() {
    GraphBST* newGraphBST = (GraphBST*)malloc(sizeof(GraphBST));

    newGraphBST->vertexLst = NULL;
    newGraphBST->adjacentBSTLst = NULL;

    return newGraphBST;
}

bool bstGraphEmpty(void* graph) {
    return ((GraphBST*)graph)->vertexLst == NULL;
}

bool bstGraphInsertVertex(void* graph, int name, DataObject* label) {
    GraphBST* graphBST = graph;

    if(graphBST->vertexLst == NULL || graphBST->vertexLst->vertexInfo->name >= name) { //TODO: Togliere l'uguale? //Il grafo è vuoto o il vertice da inserire ha nome più piccolo di tutti gli altri

        if(graphBST->vertexLst != NULL && graphBST->vertexLst->vertexInfo->name == name) { //TODO: Ottimizzare assolutamente codice qui e sotto
            printf("Vertice già presente (%d - %d)\n", graphBST->vertexLst->vertexInfo->name, name);
            return false;
        }

        //Creazione vertice
        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElement = createVertexLstElement(newVertex, graphBST->vertexLst);
        graphBST->vertexLst = newVertexLstElement;

        //Creazione rispettivo albero di adiacenza
        AdjacentBSTLst* newAjdacentBSTLst = createAdjacentBSTLstElem(newVertex, graphBST->adjacentBSTLst);
        graphBST->adjacentBSTLst = newAjdacentBSTLst;

    } else { //Il grafo ha almeno un vertice
        VertexLst* currentVertexLstElem = graphBST->vertexLst;
        AdjacentBSTLst* currentAdjacentBSTLstElem = graphBST->adjacentBSTLst;

        //Localizzazione del vertice che si trova prima del punto di inserimento
        while(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name < name) {
            currentVertexLstElem = currentVertexLstElem->nextVertex;
            currentAdjacentBSTLstElem = currentAdjacentBSTLstElem->nextVertex;
        }

        if(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name == name) { //Controllo se il vertice che si vuole inserire non sia già presente
            printf("Vertice già presente (%d - %d)\n", currentVertexLstElem->nextVertex->vertexInfo->name, name);
            return false;
        }

        //Creazione vertice
        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElem = createVertexLstElement(newVertex, currentVertexLstElem->nextVertex);
        currentVertexLstElem->nextVertex = newVertexLstElem;

        //Creazione rispettivo albero di adiacenza
        AdjacentBSTLst* newAjdacentBSTLstElem = createAdjacentBSTLstElem(newVertex, currentAdjacentBSTLstElem->nextVertex);
        currentAdjacentBSTLstElem->nextVertex = newAjdacentBSTLstElem;
    }

    return true;
}

bool bstGraphInsertEdge(void* graph, int fromVertexName, int toVertexName) {

    //Ricerca del nodo da cui parte l'arco
    AdjacentBSTLst* fromVertexReference = ((GraphBST*)graph)->adjacentBSTLst; //Indice della lista di alberi di adiacenza
    while(fromVertexReference != NULL && fromVertexReference->vertexPointer->name != fromVertexName) { //TODO: Ottimizzare ricerca mettendo limite
        fromVertexReference = fromVertexReference->nextVertex;
    }

    if(fromVertexReference != NULL) { //Il vertice da cui inserire l'arco è presente nel grafo
        //Ricerca del nodo in cui arriva l'arco
        VertexLst* toVertexReference = ((GraphBST*)graph)->vertexLst; //Indice della lista di vertici
        while(toVertexReference != NULL && toVertexReference->vertexInfo->name != toVertexName) {
            toVertexReference = toVertexReference->nextVertex;
        }

        if(toVertexReference != NULL) { //Il vertice verso cui inserire l'arco è presente nel grafo
            DataObject* newName = adtConstruct(ConstructIntDataType());
            adtSetValue(newName, &toVertexName);
            return recBSTInsert(&fromVertexReference->adjacentTree->root, newName);
        }
    }

    return false;
}

GraphRepresentation* ConstructGraphBST() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = bstGraphConstruct;
    //type->graphDestruct = bstGraphDestruct;

    type->graphEmpty = bstGraphEmpty;

    //type->graphTranspose = bstGraphTranspose;

    //type->graphClone = bstGraphClone;

    type->graphInsertVertex = bstGraphInsertVertex;
    //type->graphRemoveVertex = bstGraphRemoveVertex;
    type->graphInsertEdge = bstGraphInsertEdge;
    //type->graphRemoveEdge = bstGraphRemoveEdge;

    //type->graphExistsVertex = bstGraphExistsVertex;
    //type->graphExistsEdge = bstGraphExistsEdge;

    //type->graphGetVertexData = bstGraphGetVertexData;
    //type->graphSetVertexData = bstGraphSetVertexData;

    return type;
}

void DestructGraphBST(GraphRepresentation* type) {
    free(type);
}

/* ************************************************************************** */

AdjacentBSTLst* createAdjacentBSTLstElem(Vertex* vertexPointer, AdjacentBSTLst* nexVertex) {
    AdjacentBSTLst* newAdjacentBSTLst = (AdjacentBSTLst*)malloc(sizeof(AdjacentBSTLst));

    newAdjacentBSTLst->vertexPointer = vertexPointer;
    newAdjacentBSTLst->adjacentTree = bstConstruct(ConstructBSTRecursive());
    newAdjacentBSTLst->nextVertex = nexVertex;

    return newAdjacentBSTLst;
}
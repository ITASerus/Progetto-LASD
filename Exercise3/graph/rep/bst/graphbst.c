
#include "graphbst.h"
#include "bst/bst.h"
#include "bst/rec/bstrec.h"
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

int bstGraphRemoveVertex(void* graph, int name) {
    if(((GraphBST*)graph)->vertexLst != NULL) {
        int adjacentRemoved = 0;

        if(((GraphBST*)graph)->vertexLst->vertexInfo->name == name) { //Il vertice da rimuovere si trova in cima alla lista
            //Rimozione vertice
            VertexLst* vertexLstElemToRemove = ((GraphBST*)graph)->vertexLst;
            ((GraphBST*)graph)->vertexLst = ((GraphBST*)graph)->vertexLst->nextVertex;
            deleteVertexLstElem(vertexLstElemToRemove);

            //Rimozione albero di adiacenza
            AdjacentBSTLst* adjacentLstToRemove = ((GraphBST*)graph)->adjacentBSTLst;

            adjacentRemoved = adjacentLstToRemove->adjacentTree->numberOfNodes;
            bstDestruct(adjacentLstToRemove->adjacentTree);
            free(adjacentLstToRemove->vertexPointer);

            ((GraphBST*)graph)->adjacentBSTLst = ((GraphBST*)graph)->adjacentBSTLst->nextVertex;
        } else {
            VertexLst* vertexLst = ((GraphBST*)graph)->vertexLst;
            AdjacentBSTLst* adjacentLst = ((GraphBST*)graph)->adjacentBSTLst;

            //Ricerca del vertice da rimuovere e del rispettivo albero di adiacenza
            if(vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name != name) {
                do {
                    vertexLst = vertexLst->nextVertex;
                    adjacentLst = adjacentLst->nextVertex;
                } while (vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name < name);
            }

            if(vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name == name) { //Il vertice da rimuovere esiste
                //Rimozione vertice
                VertexLst* vertexLstElemToRemove = vertexLst->nextVertex;
                vertexLst->nextVertex = vertexLst->nextVertex->nextVertex;
                deleteVertexLstElem(vertexLstElemToRemove);

                //Rimozione albero di adiacenza
                AdjacentBSTLst* adjacentLstToRemove = adjacentLst->nextVertex;
                adjacentRemoved = adjacentLstToRemove->adjacentTree->numberOfNodes;
                bstDestruct(adjacentLstToRemove->adjacentTree);
                free(adjacentLstToRemove->vertexPointer);

                adjacentLst->nextVertex = adjacentLst->nextVertex->nextVertex;
            } else {
                return -1;
            }
        }

        //Rimuovo il resto degli archi
        if(adjacentRemoved > 0) { //Il vertice era presente nell'albero quindi è possibile che qualche altro vertice si riferisse ad esso
            AdjacentBSTLst* adjacentBSTLstIndex = ((GraphBST*)graph)->adjacentBSTLst;

            while(adjacentBSTLstIndex != NULL) {
                DataObject* nameToDelete = adtConstruct(ConstructIntDataType()); //TODO: Cercare di evitare di creare un constructInt ogni volta?
                adtSetValue(nameToDelete, &name);

                int numVer = adjacentBSTLstIndex->adjacentTree->numberOfNodes;
                bstRemove(adjacentBSTLstIndex->adjacentTree, nameToDelete);
                if(adjacentBSTLstIndex->adjacentTree->numberOfNodes < numVer) {
                    adjacentRemoved+= 1;
                }

                adjacentBSTLstIndex = adjacentBSTLstIndex->nextVertex;
            }
        }

        return adjacentRemoved;
    }

    return -1; //Vertice non presente
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
            DataObject* newName = adtConstruct(ConstructIntDataType()); //TODO: Cercare di evitare di creare un constructInt ogni volta?
            adtSetValue(newName, &toVertexName);

            //TODO: Cerca di utilizzare direttamente recBSTInsert
            int numVer = fromVertexReference->adjacentTree->numberOfNodes;
            bstInsert(fromVertexReference->adjacentTree, newName);
            if(fromVertexReference->adjacentTree->numberOfNodes > numVer) {
                return true;
            }
        }
    }

    return false;
}

bool bstGraphRemoveEdge(void* graph, int fromVertexName, int toVertexName) {
    if(((GraphBST*)graph)->vertexLst != NULL) { //Nel grafo c'è almeno un vertice
        AdjacentBSTLst* adjacentBSTLstElem = ((GraphBST*) graph)->adjacentBSTLst;

        if(adjacentBSTLstElem->vertexPointer->name != fromVertexName) {
            do {
                adjacentBSTLstElem = adjacentBSTLstElem->nextVertex;
            } while (adjacentBSTLstElem != NULL && adjacentBSTLstElem->vertexPointer->name < fromVertexName);
        }

        if(adjacentBSTLstElem != NULL && adjacentBSTLstElem->vertexPointer->name == fromVertexName) { //Il vertice da cui parte l'arco esiste
            DataObject* nameToDelete = adtConstruct(ConstructIntDataType()); //TODO: Cercare di evitare di creare un constructInt ogni volta?
            adtSetValue(nameToDelete, &toVertexName);

            int numVer = adjacentBSTLstElem->adjacentTree->numberOfNodes;
            bstRemove(adjacentBSTLstElem->adjacentTree, nameToDelete);
            if(adjacentBSTLstElem->adjacentTree->numberOfNodes < numVer) {
                return true;
            }
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
    type->graphRemoveVertex = bstGraphRemoveVertex;
    type->graphInsertEdge = bstGraphInsertEdge;
    type->graphRemoveEdge = bstGraphRemoveEdge;

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
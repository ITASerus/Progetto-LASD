
#include "graphlst.h"

Vertex* createVertex(int name, DataObject* label);
VertexLst* createVertexLstElement(Vertex* vertexInfo, VertexLst* next);
AdjacentLst* createAdjacentLstElement(Vertex* vertexPointer, AdjacentLst* nextVertex, AdjacentLst* nextAdjacent);

void deleteVertexLstElem(VertexLst* vertexLstElem);
void deleteAdjacentLst(AdjacentLst* adjacentLst);

/* ************************************************************************** */

void* lstGraphConstruct() {
    GraphLst* newGraphLst = (GraphLst*)malloc(sizeof(GraphLst));

    newGraphLst->vertexLst = NULL;
    newGraphLst->adjacentVertexLst = NULL;

    return newGraphLst;
}

void lstGraphInsertVertex(void* graph, int name, DataObject* label) {
    GraphLst* graphLst = graph;

    if(graphLst->vertexLst == NULL || graphLst->vertexLst->vertexInfo->name >= name) { //Il grafo è vuoto o il vertice da inserire ha nome più piccolo di tutti gli altri

        if(graphLst->vertexLst != NULL && graphLst->vertexLst->vertexInfo->name == name) { //TODO: Ottimizzare assolutamente codice qui e sotto
            printf("Vertice già presente (%d - %d)\n", graphLst->vertexLst->vertexInfo->name, name);
            return;
        }

        Vertex* newVertex = createVertex(name, label);

        VertexLst* newVertexLstElement = createVertexLstElement(newVertex, graphLst->vertexLst);
        graphLst->vertexLst = newVertexLstElement;

        AdjacentLst* newAjdacentVertexLst = createAdjacentLstElement(newVertex, graphLst->adjacentVertexLst, NULL);
        graphLst->adjacentVertexLst = newAjdacentVertexLst;
    } else { //Il grafo ha almeno un vertice
        VertexLst* currentVertexLstElem = graphLst->vertexLst;
        AdjacentLst* currentAdjacentLstElem = graphLst->adjacentVertexLst;

        //Localizzazione del vertice che si trova prima del punto di inserimento
        while(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name < name) {
            currentVertexLstElem = currentVertexLstElem->nextVertex;
            currentAdjacentLstElem = currentAdjacentLstElem->nextVertex;
        }

        if(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name == name) { //Controllo se il vertice che si vuole inserire non sia già presente
            printf("Vertice già presente (%d - %d)\n", currentVertexLstElem->nextVertex->vertexInfo->name, name);
            return;
        }

        Vertex* newVertex = createVertex(name, label);

        VertexLst* newVertexLstElement = createVertexLstElement(newVertex, currentVertexLstElem->nextVertex);
        currentVertexLstElem->nextVertex = newVertexLstElement;

        AdjacentLst* newAjdacentLstElem = createAdjacentLstElement(newVertex, currentAdjacentLstElem->nextVertex, NULL);
        currentAdjacentLstElem->nextVertex = newAjdacentLstElem;
    }
}

void lstGraphRemoveVertex(void* graph, int name) {

    if( ((GraphLst*)graph)->vertexLst != NULL) {

        if( ((GraphLst*)graph)->vertexLst->vertexInfo->name == name) { //Il vertice da rimuovere si trova in cima alla lista
            //Rimozione vertice
            VertexLst* vertexLstElemToRemove = ((GraphLst*)graph)->vertexLst;
            ((GraphLst*)graph)->vertexLst = ((GraphLst*)graph)->vertexLst->nextVertex;
            deleteVertexLstElem(vertexLstElemToRemove);

            //Rimozione lista di adiacenza
            AdjacentLst* adjacentLstElemToRemove = ((GraphLst*)graph)->adjacentVertexLst;
            ((GraphLst*)graph)->adjacentVertexLst = ((GraphLst*)graph)->adjacentVertexLst->nextVertex;
            deleteAdjacentLst(adjacentLstElemToRemove);

        } else {
            VertexLst* vertexLst = ((GraphLst*)graph)->vertexLst;
            AdjacentLst* adjacentLst = ((GraphLst*)graph)->adjacentVertexLst;

            //Ricerca del vertice da rimuovere e della rispettiva lista di adiacenza
            while(vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name != name) {
                vertexLst = vertexLst->nextVertex;
                adjacentLst = adjacentLst->nextVertex;
            }

            if(vertexLst->nextVertex != NULL) { //Il vertice da rimuovere esiste
                //Rimozione vertice
                VertexLst* vertexLstElemToRemove = vertexLst->nextVertex;
                vertexLst->nextVertex = vertexLst->nextVertex->nextVertex;
                deleteVertexLstElem(vertexLstElemToRemove);

                //Rimozione lista di adiacenza
                AdjacentLst* adjacentLstToRemove = adjacentLst->nextVertex;
                adjacentLst->nextVertex = adjacentLst->nextVertex->nextVertex;
                deleteAdjacentLst(adjacentLstToRemove);
            }
        }
    }
}

void lstGraphInsertEdge(void* graph, int fromVertexName, int toVertexName) {
    AdjacentLst* currentAdjacentLstElem = ((GraphLst*)graph)->adjacentVertexLst; //Indice della lista di adiacenza
    while(currentAdjacentLstElem != NULL && currentAdjacentLstElem->vertexPointer->name != fromVertexName) {
        currentAdjacentLstElem = currentAdjacentLstElem->nextVertex;
    }

    if(currentAdjacentLstElem != NULL) { //Il vertice da cui inserire l'arco è presente nel grafo
        VertexLst* currentVertexLstElem = ((GraphLst*)graph)->vertexLst; //Indice della lista di vertici
        while(currentVertexLstElem != NULL && currentVertexLstElem->vertexInfo->name != toVertexName) {
            currentVertexLstElem = currentVertexLstElem->nextVertex;
        }

        if(currentVertexLstElem != NULL) { //Il vertice verso cui inserire l'arco è presente nel grafo

            if(currentAdjacentLstElem->nextAdjacent == NULL || currentAdjacentLstElem->nextAdjacent->vertexPointer->name > toVertexName) { //La lista di adiacenza è vuota o il nuovo nodo adiacente ha nome più piccolo dei nomi di tutti gli altri adiacenti al vertice
                AdjacentLst* newAdjacent = createAdjacentLstElement(currentVertexLstElem->vertexInfo, NULL, currentAdjacentLstElem->nextAdjacent);
                currentAdjacentLstElem->nextAdjacent = newAdjacent;
            } else { //La lista di adiacenza ha almeno un vertice
                AdjacentLst* currentAdjacent = currentAdjacentLstElem; //Indice della lista degli adiacenti

                //Localizzazione del riferimento all'adiacente che si trova prima del punto di inserimento
                while(currentAdjacent->nextAdjacent != NULL && currentAdjacent->nextAdjacent->vertexPointer->name < toVertexName) {
                    currentAdjacent = currentAdjacent->nextAdjacent;
                }

                if(currentAdjacent->nextAdjacent != NULL && currentAdjacent->nextAdjacent->vertexPointer->name == toVertexName) { //Controllo se l'arco che si vuole inserire non sia già presente
                    printf("Arco già presente (%d - %d)\n", currentAdjacent->nextAdjacent->vertexPointer->name, toVertexName);
                    return;
                }

                AdjacentLst* newAjdacentLstElem = createAdjacentLstElement(currentVertexLstElem->vertexInfo, NULL, currentAdjacent->nextAdjacent);
                currentAdjacent->nextAdjacent = newAjdacentLstElem;
            }

        }
    }
}

bool lstGraphExistsVertex(void* graph, int name) {
    VertexLst* currentVertexLstElem = ((GraphLst*)graph)->vertexLst;

    while(currentVertexLstElem != NULL && currentVertexLstElem->vertexInfo->name != name) {
        currentVertexLstElem = currentVertexLstElem->nextVertex;
    }

    if(currentVertexLstElem != NULL) {
        return true;
    } else {
        return false;
    }
}

bool lstGraphExistsEdge(void* graph, int fromVertexName, int toVertexName) {
    AdjacentLst* adjacentLst = ((GraphLst*)graph)->adjacentVertexLst;

    while(adjacentLst != NULL && adjacentLst->vertexPointer->name != fromVertexName) {
        adjacentLst = adjacentLst->nextVertex;
    }

    if(adjacentLst != NULL) { //Il nodo da cui parte l'arco esiste
        adjacentLst = adjacentLst->nextAdjacent;
        while(adjacentLst!= NULL && adjacentLst->vertexPointer->name != toVertexName) {
            adjacentLst = adjacentLst->nextAdjacent;
        }

        if(adjacentLst != NULL) { //L'arco da cercare esiste
            return true;
        }
    }

    return false;
}

bool lstGraphEmpty(void* graph) {
    return ((GraphLst*)graph)->vertexLst == NULL;
}

GraphRepresentation* ConstructGraphLst() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = lstGraphConstruct;
    type->graphInsertVertex = lstGraphInsertVertex;
    type->graphRemoveVertex = lstGraphRemoveVertex;
    type->graphInsertEdge = lstGraphInsertEdge;
    type->graphExistsVertex = lstGraphExistsVertex;
    type->graphExistsEdge = lstGraphExistsEdge;

    type->graphEmpty = lstGraphEmpty;


    return type;
}

void DestructGraphLst(GraphRepresentation* type) {
    free(type);
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

AdjacentLst* createAdjacentLstElement(Vertex* vertexPointer, AdjacentLst* nextVertex, AdjacentLst* nextAdjacent) {
    AdjacentLst* newAjdacentVertexLst = (AdjacentLst*)malloc(sizeof(AdjacentLst));

    newAjdacentVertexLst->vertexPointer = vertexPointer;
    newAjdacentVertexLst->nextVertex = nextVertex;
    newAjdacentVertexLst->nextAdjacent = nextAdjacent;

    return newAjdacentVertexLst;
}




void deleteVertexLstElem(VertexLst* vertexLstElem){
    adtDestruct(vertexLstElem->vertexInfo->label);
    free(vertexLstElem);
}

void deleteAdjacentLst(AdjacentLst* adjacentLst) {
    while(adjacentLst != NULL) { //Svuota la lista di adiacenti
        AdjacentLst* adjacentElemToRemove = adjacentLst;
        adjacentLst = adjacentLst->nextAdjacent;
        free(adjacentElemToRemove);
    }
}
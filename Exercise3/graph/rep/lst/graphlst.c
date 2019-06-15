
#include "graphlst.h"

#include "graph/graphitrvertex.h"
#include "graph/rep/lst/graphlstitradjacent.h"

/* *************************** FUNZIONI PRINCIPALI **************************** */

void* lstGraphConstruct();
void lstGraphDestruct(void* graph);

bool lstGraphEmpty(void* graph);

void* lstGraphClone(void* graph);

void* lstGraphTranspose(void* graph);

bool lstGraphInsertVertex(void* graph, int name, DataObject* label);
int lstGraphRemoveVertex(void* graph, int name);

bool lstGraphInsertEdge(void* graph, int fromVertexName, int toVertexName);
bool lstGraphRemoveEdge(void* graph, int fromVertexName, int toVertexName);

bool lstGraphExistsVertex(void* graph, int name);
bool lstGraphExistsEdge(void* graph, int fromVertexName, int toVertexName);

DataObject* lstGraphGetVertexData(void* graph, int name);
void lstGraphSetVertexData(void* graph, int name, DataObject* newValue);

/* *************************** FUNZIONI AUSILIARIE **************************** */

AdjacentLst* createAdjacentLstElement(Vertex* vertexPointer, AdjacentLst* nextVertex, AdjacentLst* nextAdjacent);
int deleteAdjacentLst(AdjacentLst* adjacentLst);

/* ************************************************************************** */

void* lstGraphConstruct() {
    GraphLst* newGraphLst = (GraphLst*)malloc(sizeof(GraphLst));

    newGraphLst->vertexLst = NULL;
    newGraphLst->adjacentVertexLst = NULL;

    return newGraphLst;
}

void lstGraphDestruct(void* graph) {
    GraphLst* graphLst = (GraphLst*)graph;

    VertexLst* vertexRef;
    AdjacentLst* adjacentRef;
    while(graphLst->vertexLst != NULL) {
        vertexRef = graphLst->vertexLst;
        adjacentRef = graphLst->adjacentVertexLst;

        graphLst->vertexLst = graphLst->vertexLst->nextVertex;
        graphLst->adjacentVertexLst = graphLst->adjacentVertexLst->nextVertex;

        deleteVertexLstElem(vertexRef);
        deleteAdjacentLst(adjacentRef);
    }

    //TODO: Aggiungere free vertexRef e freeAdhacentRef?
}

bool lstGraphEmpty(void* graph) {
    return ((GraphLst*)graph)->vertexLst == NULL;
}

void* lstGraphClone(void* graph) {
    GraphLst* newGraph = lstGraphConstruct();

    //Copio i vertici appartenenti al grafo da copiare
    VertexLst* vertexLstToClone = ((GraphLst*)graph)->vertexLst;
    if(vertexLstToClone != NULL) { //Il grafo da clonare ha almeno un vertice
        Vertex* newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
        newGraph->vertexLst = createVertexLstElement(newVertex, NULL);
        newGraph->adjacentVertexLst = createAdjacentLstElement(newVertex, NULL, NULL);

        vertexLstToClone = vertexLstToClone->nextVertex;

        VertexLst* newGraphVertexLst = newGraph->vertexLst;
        AdjacentLst* newGraphAdjacentLst = newGraph->adjacentVertexLst;
        while(vertexLstToClone != NULL) {
            newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
            newGraphVertexLst->nextVertex = createVertexLstElement(newVertex, NULL);
            newGraphAdjacentLst->nextVertex = createAdjacentLstElement(newVertex, NULL, NULL);

            newGraphVertexLst = newGraphVertexLst->nextVertex;
            newGraphAdjacentLst = newGraphAdjacentLst->nextVertex;
            vertexLstToClone = vertexLstToClone->nextVertex;
        }
    }

    //Copio gli adiacenti dei vertici
    AdjacentLst* adjacentLstToClone = ((GraphLst*)graph)->adjacentVertexLst;
    while(adjacentLstToClone != NULL) {
        AdjacentLst* currentAdjacent = adjacentLstToClone->nextAdjacent;

        while(currentAdjacent != NULL) {
            lstGraphInsertEdge(newGraph, adjacentLstToClone->vertexPointer->name, currentAdjacent->vertexPointer->name);
            currentAdjacent = currentAdjacent->nextAdjacent;
        }
        adjacentLstToClone = adjacentLstToClone->nextVertex;
    }

    return newGraph;

    /**** NOTA: Copio prima la lista di liste di adiacenza e poi gli adiacenti veri e propri perchè la lista di adiacenza contiene riferimenti ai nodi e, in mancanza di essi, non possono essere creati gli archi ***/
}

void* lstGraphTranspose(void* graph) { //TODO: Rivedi struttura
    GraphLst* newGraph = lstGraphConstruct();

    //Copio i vertici appartenenti al grafo da copiare
    VertexLst* vertexLstToClone = ((GraphLst*)graph)->vertexLst;
    if(vertexLstToClone != NULL) { //Il grafo da clonare ha almeno un vertice
        Vertex* newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
        newGraph->vertexLst = createVertexLstElement(newVertex, NULL);
        newGraph->adjacentVertexLst = createAdjacentLstElement(newVertex, NULL, NULL);

        vertexLstToClone = vertexLstToClone->nextVertex;

        VertexLst* newGraphVertexLst = newGraph->vertexLst;
        AdjacentLst* newGraphAdjacentLst = newGraph->adjacentVertexLst;
        while(vertexLstToClone != NULL) {
            newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
            newGraphVertexLst->nextVertex = createVertexLstElement(newVertex, NULL);
            newGraphAdjacentLst->nextVertex = createAdjacentLstElement(newVertex, NULL, NULL);

            newGraphVertexLst = newGraphVertexLst->nextVertex;
            newGraphAdjacentLst = newGraphAdjacentLst->nextVertex;
            vertexLstToClone = vertexLstToClone->nextVertex;
        }
    }

    //Copio gli adiacenti dei vertici in posizione trasposta
    AdjacentLst* adjacentLstToClone = ((GraphLst*)graph)->adjacentVertexLst;
    while(adjacentLstToClone != NULL) {
        AdjacentLst* currentAdjacent = adjacentLstToClone->nextAdjacent;

        while(currentAdjacent != NULL) {
            lstGraphInsertEdge(newGraph, currentAdjacent->vertexPointer->name, adjacentLstToClone->vertexPointer->name);
            currentAdjacent = currentAdjacent->nextAdjacent;
        }
        adjacentLstToClone = adjacentLstToClone->nextVertex;
    }

    return newGraph;
}

bool lstGraphInsertVertex(void* graph, int name, DataObject* label) {
    GraphLst* graphLst = graph;

    if(graphLst->vertexLst == NULL || graphLst->vertexLst->vertexInfo->name >= name) { //TODO: Togliere l'uguale? //Il grafo è vuoto o il vertice da inserire ha nome più piccolo di tutti gli altri

        if(graphLst->vertexLst != NULL && graphLst->vertexLst->vertexInfo->name == name) { //TODO: Ottimizzare assolutamente codice qui e sotto
            printf("Vertice già presente (%d - %d)\n", graphLst->vertexLst->vertexInfo->name, name);
            return false;
        }

        //Creazione vertice
        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElement = createVertexLstElement(newVertex, graphLst->vertexLst);
        graphLst->vertexLst = newVertexLstElement;

        //Creazione rispettiva lista di adiacenza
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
            return false;
        }

        //Creazione vertice
        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElem = createVertexLstElement(newVertex, currentVertexLstElem->nextVertex);
        currentVertexLstElem->nextVertex = newVertexLstElem;

        //Creazione rispettiva lista di adiacenza
        AdjacentLst* newAjdacentLstElem = createAdjacentLstElement(newVertex, currentAdjacentLstElem->nextVertex, NULL);
        currentAdjacentLstElem->nextVertex = newAjdacentLstElem;
    }

    return true;
}

int lstGraphRemoveVertex(void* graph, int name) {
    if(((GraphLst*)graph)->vertexLst != NULL) {
        int adjacentRemoved = 0;

        if(((GraphLst*)graph)->vertexLst->vertexInfo->name == name) { //Il vertice da rimuovere si trova in cima alla lista
            //Rimozione vertice
            VertexLst* vertexLstElemToRemove = ((GraphLst*)graph)->vertexLst;
            ((GraphLst*)graph)->vertexLst = ((GraphLst*)graph)->vertexLst->nextVertex;
            deleteVertexLstElem(vertexLstElemToRemove);

            //Rimozione lista di adiacenza
            AdjacentLst* adjacentLstElemToRemove = ((GraphLst*)graph)->adjacentVertexLst;
            ((GraphLst*)graph)->adjacentVertexLst = ((GraphLst*)graph)->adjacentVertexLst->nextVertex;

            adjacentRemoved += deleteAdjacentLst(adjacentLstElemToRemove); //TODO: Togliere il +? (inutile)
        } else {
            VertexLst* vertexLst = ((GraphLst*)graph)->vertexLst;
            AdjacentLst* adjacentLst = ((GraphLst*)graph)->adjacentVertexLst;

            //Ricerca del vertice da rimuovere e della rispettiva lista di adiacenza
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

                //Rimozione lista di adiacenza
                AdjacentLst* adjacentLstToRemove = adjacentLst->nextVertex;
                adjacentLst->nextVertex = adjacentLst->nextVertex->nextVertex;

                adjacentRemoved += deleteAdjacentLst(adjacentLstToRemove); //TODO: Togliere il +? (inutile)
            } else {
                return -1;
            }
        }

        //Rimuovo il resto degli archi
        if(adjacentRemoved > 0) { //Il vertice era presente nell'albero quindi è possibile che qualche altro vertice si riferisse ad esso
            AdjacentLst* adjacentLstIndex = ((GraphLst*)graph)->adjacentVertexLst;

            while(adjacentLstIndex != NULL) {
                AdjacentLst* currentAdjacent = adjacentLstIndex;
                while(currentAdjacent->nextAdjacent != NULL && currentAdjacent->nextAdjacent->vertexPointer->name != name) {
                    currentAdjacent = currentAdjacent->nextAdjacent;
                }

                if(currentAdjacent->nextAdjacent != NULL) {
                    AdjacentLst* tmp = currentAdjacent->nextAdjacent;
                    currentAdjacent->nextAdjacent = currentAdjacent->nextAdjacent->nextAdjacent;
                    free(tmp);

                    adjacentRemoved++;
                }
                adjacentLstIndex = adjacentLstIndex->nextVertex;
            }
        }

        return adjacentRemoved;
    }

    return -1; //Vertice non presente
}

bool lstGraphInsertEdge(void* graph, int fromVertexName, int toVertexName) {
    AdjacentLst* currentAdjacentLstElem = ((GraphLst*)graph)->adjacentVertexLst; //Indice della lista di adiacenza
    while(currentAdjacentLstElem != NULL && currentAdjacentLstElem->vertexPointer->name != fromVertexName) { //TODO: Ottimizzare ricerca mettendo limite
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
                return true;
            } else { //La lista di adiacenza ha almeno un vertice
                AdjacentLst* currentAdjacent = currentAdjacentLstElem; //Indice della lista degli adiacenti

                //Localizzazione del riferimento all'adiacente che si trova prima del punto di inserimento
                while(currentAdjacent->nextAdjacent != NULL && currentAdjacent->nextAdjacent->vertexPointer->name < toVertexName) {
                    currentAdjacent = currentAdjacent->nextAdjacent;
                }

                if(currentAdjacent->nextAdjacent != NULL && currentAdjacent->nextAdjacent->vertexPointer->name == toVertexName) { //Controllo se l'arco che si vuole inserire non sia già presente
                    printf("Arco già presente (%d - %d)\n", currentAdjacent->nextAdjacent->vertexPointer->name, toVertexName);
                    return false;
                }

                AdjacentLst* newAjdacentLstElem = createAdjacentLstElement(currentVertexLstElem->vertexInfo, NULL, currentAdjacent->nextAdjacent);
                currentAdjacent->nextAdjacent = newAjdacentLstElem;
                return true;
            }

        }
    }

    return false;
}

bool lstGraphRemoveEdge(void* graph, int fromVertexName, int toVertexName) {
    if(((GraphLst*)graph)->vertexLst != NULL) { //Nel grafo c'è almeno un vertice
        AdjacentLst* adjacentLstElem = ((GraphLst *) graph)->adjacentVertexLst;

        if(adjacentLstElem->vertexPointer->name != fromVertexName) {
            do {
                adjacentLstElem = adjacentLstElem->nextVertex;
            } while (adjacentLstElem != NULL && adjacentLstElem->vertexPointer->name < fromVertexName);
        }

        if(adjacentLstElem != NULL && adjacentLstElem->vertexPointer->name == fromVertexName) { //Il vertice da cui parte l'arco esiste

            if(adjacentLstElem->nextAdjacent != NULL && adjacentLstElem->nextAdjacent->vertexPointer->name != toVertexName) {
                do {
                    adjacentLstElem = adjacentLstElem->nextAdjacent;
                } while(adjacentLstElem->nextAdjacent != NULL && adjacentLstElem->nextAdjacent->vertexPointer->name < toVertexName);
            }

            if (adjacentLstElem->nextAdjacent != NULL && adjacentLstElem->nextAdjacent->vertexPointer->name == toVertexName) { //L'arco da eliminare esiste
                AdjacentLst *adjacentElemToRemove = adjacentLstElem->nextAdjacent;
                adjacentLstElem->nextAdjacent = adjacentLstElem->nextAdjacent->nextAdjacent;
                free(adjacentElemToRemove);

                return true;
            } else {
                printf("\nVertice di arrivo non presente");
            }
        } else {
            printf("\nVertice di partenza non presente");
        }
    }

    return false;
}

bool lstGraphExistsVertex(void* graph, int name) {
    VertexLst* currentVertexLstElem = ((GraphLst*)graph)->vertexLst;

    if(currentVertexLstElem->vertexInfo->name != name) {
        do {
            currentVertexLstElem = currentVertexLstElem->nextVertex;
        } while(currentVertexLstElem != NULL && currentVertexLstElem->vertexInfo->name < name);
    }

    if(currentVertexLstElem != NULL && currentVertexLstElem->vertexInfo->name == name) {
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

DataObject* lstGraphGetVertexData(void* graph, int name) {
    VertexLst* currentVertex = ((GraphLst*)graph)->vertexLst;

    while(currentVertex != NULL && currentVertex->vertexInfo->name < name){
        currentVertex = currentVertex->nextVertex;
    }

    if(currentVertex != NULL && currentVertex->vertexInfo->name == name) {
        DataObject* vertexData = adtClone(currentVertex->vertexInfo->label);
        return vertexData;
    } else {
        return NULL;
    }
}

void lstGraphSetVertexData(void* graph, int name, DataObject* newValue) {
    VertexLst* currentVertex = ((GraphLst*)graph)->vertexLst;

    while(currentVertex != NULL && currentVertex->vertexInfo->name < name){
        currentVertex = currentVertex->nextVertex;
    }

    if(currentVertex != NULL && currentVertex->vertexInfo->name == name) {
        adtSetValue(currentVertex->vertexInfo->label, newValue->value);
    } else {
        printf("Vertice %d non presente\n", name);
    }
}

ITRObject* lstGraphVertices(void* graph) {
    ITRType* iterType = ConstructVertexIterator();
    ITRObject* iterator = itrConstruct(iterType, ((GraphLst*)graph)->vertexLst);

    return iterator;
}

ITRObject* lstGraphVertexEdges(void* graph, int name) {
    LstItrInterface* lstInterface = initializeLstIterator(name, ((GraphLst*)graph)->adjacentVertexLst);

    ITRType* itrType = ConstructLstAdjacentIterator();
    ITRObject* iterator = itrConstruct(itrType, lstInterface);

    free(lstInterface); //TODO: Serve? devo deallocare qualcosa?

    return iterator;
}

GraphRepresentation* ConstructGraphLst() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = lstGraphConstruct;
    type->graphDestruct = lstGraphDestruct;

    type->graphEmpty = lstGraphEmpty;

    type->graphTranspose = lstGraphTranspose;

    type->graphClone = lstGraphClone;

    type->graphInsertVertex = lstGraphInsertVertex;
    type->graphRemoveVertex = lstGraphRemoveVertex;
    type->graphInsertEdge = lstGraphInsertEdge;
    type->graphRemoveEdge = lstGraphRemoveEdge;

    type->graphExistsVertex = lstGraphExistsVertex;
    type->graphExistsEdge = lstGraphExistsEdge;

    type->graphGetVertexData = lstGraphGetVertexData;
    type->graphSetVertexData = lstGraphSetVertexData;

    type->graphVertices = lstGraphVertices;
    type->graphVertexEdges = lstGraphVertexEdges;

    return type;
}

void DestructGraphLst(GraphRepresentation* type) {
    free(type);
}

/* ************************************************************************** */

AdjacentLst* createAdjacentLstElement(Vertex* vertexPointer, AdjacentLst* nextVertex, AdjacentLst* nextAdjacent) {
    AdjacentLst* newAjdacentVertexLst = (AdjacentLst*)malloc(sizeof(AdjacentLst));

    newAjdacentVertexLst->vertexPointer = vertexPointer;
    newAjdacentVertexLst->nextVertex = nextVertex;
    newAjdacentVertexLst->nextAdjacent = nextAdjacent;

    return newAjdacentVertexLst;
}

int deleteAdjacentLst(AdjacentLst* adjacentLst) {
    int numAdjacent = 0;

    while(adjacentLst != NULL) { //Svuota la lista di adiacenti
        AdjacentLst* adjacentElemToRemove = adjacentLst;
        adjacentLst = adjacentLst->nextAdjacent;
        free(adjacentElemToRemove);

        numAdjacent++;
    }

    return numAdjacent-1;
}


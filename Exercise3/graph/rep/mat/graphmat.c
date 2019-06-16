/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "graphmat.h"

#include "graph/graphitrvertex.h"
#include "graph/rep/mat/graphmatitradjacent.h"

/* *************************** FUNZIONI PRINCIPALI **************************** */

void* matGraphConstruct();
void matGraphDestruct(void* graph);

bool matGraphEmpty(void* graph);

void* matGraphClone(void* graph);

void* matGraphTranspose(void* graph);

bool matGraphInsertVertex(void* graph, int name, DataObject* label);
int matGraphRemoveVertex(void* graph, int name);

bool matGraphInsertEdge(void* graph, int fromVertexName, int toVertexName);
bool matGraphRemoveEdge(void* graph, int fromVertexName, int toVertexName);

bool matGraphExistsVertex(void* graph, int name);
bool matGraphExistsEdge(void* graph, int fromVertexName, int toVertexName);

DataObject* matGraphGetVertexData(void* graph, int name);
void matGraphSetVertexData(void* graph, int name, DataObject* newValue);

/* *************************** FUNZIONI AUSILIARIE **************************** */

int deleteAdjacentRowColumn(AdjacentMatrix* adjacentMatrix, int vertexPosition);

/* ************************************************************************** */

void* matGraphConstruct() {
    GraphMat* newGraphMat = (GraphMat*)malloc(sizeof(GraphMat));

    newGraphMat->vertexLst = NULL;
    newGraphMat->adjacentMatrix = NULL;

    return newGraphMat;
}

void matGraphDestruct(void* graph) {
    GraphMat* graphMat = (GraphMat*)graph;

    //Rimozione lista di vertici
    VertexLst* vertexRef;
    while(graphMat->vertexLst != NULL) {
        vertexRef = graphMat->vertexLst;

        graphMat->vertexLst = graphMat->vertexLst->nextVertex;

        deleteVertexLstElem(vertexRef);
    }

    //Rimozione matrice di adiacenza
    for(int i = 0; i < graphMat->adjacentMatrix->slotAllocated; i++) {
        free(graphMat->adjacentMatrix->matrix[i]);
    }
    free(graphMat->adjacentMatrix->matrix);
    free(graphMat->adjacentMatrix);
}

bool matGraphInsertVertex(void* graph, int name, DataObject* label) {
    GraphMat* graphMat = graph;

    if(graphMat->vertexLst == NULL) { //Il grafo è vuoto
        //Creazione del nuovo vertice
        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElement = createVertexLstElement(newVertex, graphMat->vertexLst);
        graphMat->vertexLst = newVertexLstElement;

        //Allocazione matrice di adiacenza
        graphMat->adjacentMatrix = (AdjacentMatrix*)malloc(sizeof(AdjacentMatrix));
        AdjacentMatrix* adjacentMatrix = graphMat->adjacentMatrix;
        adjacentMatrix->numVertex = 1;

        adjacentMatrix->slotAllocated = 2;
        bool** newAdjacentMatrix = (bool**)malloc(sizeof(bool*) * adjacentMatrix->slotAllocated);
        for(int i = 0; i < adjacentMatrix->slotAllocated; i++) {
            newAdjacentMatrix[i] = (bool*)malloc(sizeof(bool) * adjacentMatrix->slotAllocated);
            for(int j = 0; j < adjacentMatrix->slotAllocated; j++) {
                newAdjacentMatrix[i][j] = false; //Inizializzo la matrice a false per ogni campo
            }
        }

        graphMat->adjacentMatrix->matrix = newAdjacentMatrix;
    } else {
        if(graphMat->vertexLst->vertexInfo->name == name) { //Il vertice da inserire è già presente in testa
            return false; //Vertice già presente
        } else { //Cerco se il vertice è già presente nel grafo e, in caso contrario, la posizione dove inserirlo
            Vertex* newVertex;
            VertexLst* newVertexLstElem;

            int newVertexPosition = 0;
            if(graphMat->vertexLst->vertexInfo->name > name) { //Il vertice da inserire va inserito in testa
                newVertex = createVertex(name, label);
                newVertexLstElem = createVertexLstElement(newVertex, graphMat->vertexLst);
                graphMat->vertexLst = newVertexLstElem;
            } else { //Localizzazione del vertice che si trova prima del punto di inserimento
                VertexLst* currentVertexLstElem = graphMat->vertexLst;

                newVertexPosition = 1; //Contatore che identifica la posizione del nuovo vertice nella matrice di adiacenza
                while(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name < name) {
                    currentVertexLstElem = currentVertexLstElem->nextVertex;
                    newVertexPosition++;
                }

                if(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name == name) { //Controllo se il vertice che si vuole inserire non sia già presente
                    return false;//Vertice già presente
                }

                //Creazione del vertice
                newVertex = createVertex(name, label);
                newVertexLstElem = createVertexLstElement(newVertex, currentVertexLstElem->nextVertex);
                currentVertexLstElem->nextVertex = newVertexLstElem;
            }

            //Popolamento della rispettiva zona della  matrice di adiacenza
            AdjacentMatrix* adjacentMatrix = graphMat->adjacentMatrix;
            adjacentMatrix->numVertex++;

            if(adjacentMatrix->numVertex > adjacentMatrix->slotAllocated) { //La matrice di adiacenza va ingrandita
                int newDimension = adjacentMatrix->slotAllocated*2;

                //Aumento il numero di righe
                bool** tmp = realloc(graphMat->adjacentMatrix->matrix, sizeof(*graphMat->adjacentMatrix->matrix) * newDimension); //Aumento il numero di righe
                if(tmp) {
                    graphMat->adjacentMatrix->matrix = tmp;
                    for(int i = 0; i < adjacentMatrix->slotAllocated; i++) {
                        adjacentMatrix->matrix[adjacentMatrix->slotAllocated+i] = malloc(sizeof(*adjacentMatrix->matrix[adjacentMatrix->slotAllocated+i]) * adjacentMatrix->slotAllocated); //Per ogni nuova riga, alloco un vettore con newDimension spazi
                    }
                }

                //Aumento il numero di colonne
                for(int i = 0; i < newDimension; i++) {
                    bool* tmp = realloc(adjacentMatrix->matrix[i], sizeof(*graphMat->adjacentMatrix->matrix) * newDimension); //Per ogni nuova riga, rialloco un vettore con il nuovo numero di locazioni
                    if(tmp) {
                        adjacentMatrix->matrix[i] = tmp;
                    }
                }
                adjacentMatrix->slotAllocated = newDimension;
            }

            //Shift dei valori della matrice
            for (int i = adjacentMatrix->numVertex - 1; i >= 0; i--) {
                for (int j = adjacentMatrix->numVertex - 1; j >= 0; j--) {
                    if (i == newVertexPosition || j == newVertexPosition) { //Nuova riga/colonna
                        adjacentMatrix->matrix[i][j] = false;
                    } else if ((i > newVertexPosition || j > newVertexPosition) && i-1 >= 0 && j-1 >= 0) {
                        adjacentMatrix->matrix[i][j] = adjacentMatrix->matrix[i-1][j-1];
                    }
                }
            }
        }
    }

    return true;
}

int matGraphRemoveVertex(void* graph, int name) {
    if(((GraphMat*)graph)->vertexLst != NULL) {
        int adjacentRemoved = 0;

        if(((GraphMat*)graph)->vertexLst->vertexInfo->name == name) { //Il vertice da rimuovere si trova in cima alla lista
            //Rimozione vertice
            VertexLst* vertexLstElemToRemove = ((GraphMat*)graph)->vertexLst;
            ((GraphMat*)graph)->vertexLst = ((GraphMat*)graph)->vertexLst->nextVertex;
            deleteVertexLstElem(vertexLstElemToRemove);

            //Rimozione adiacenti
            adjacentRemoved = deleteAdjacentRowColumn(((GraphMat*)graph)->adjacentMatrix, 0);

            return adjacentRemoved;
        } else {
            VertexLst* vertexLst = ((GraphMat*)graph)->vertexLst;

            //Ricerca del vertice da rimuovere e della rispettiva lista di adiacenza
            int vertexPosition = 1;
            if(vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name != name) {
                do {
                    vertexLst = vertexLst->nextVertex;
                    vertexPosition++;
                } while (vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name < name);
            }

            if(vertexLst->nextVertex != NULL && vertexLst->nextVertex->vertexInfo->name == name) { //Il vertice da rimuovere esiste
                //Rimozione vertice
                VertexLst* vertexLstElemToRemove = vertexLst->nextVertex;
                vertexLst->nextVertex = vertexLst->nextVertex->nextVertex;
                deleteVertexLstElem(vertexLstElemToRemove);

                //Rimozione adiacenti
                adjacentRemoved = deleteAdjacentRowColumn(((GraphMat*)graph)->adjacentMatrix, vertexPosition);

                return adjacentRemoved;
            } else {
                return -1;
            }
        }
    }

    return -1; //Vertice non presente
}

bool matGraphEmpty(void* graph) {
    return ((GraphMat*)graph)->vertexLst == NULL;
}

void* matGraphClone(void* graph) {
    GraphMat* newGraph = matGraphConstruct();

    //Copio i vertici appartenenti al grafo da copiare
    VertexLst* vertexLstToClone = ((GraphMat*)graph)->vertexLst;

    if(vertexLstToClone != NULL) { //Il grafo da clonare ha almeno un vertice
        Vertex* newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
        newGraph->vertexLst = createVertexLstElement(newVertex, NULL);

        vertexLstToClone = vertexLstToClone->nextVertex;

        VertexLst* newGraphVertexLst = newGraph->vertexLst;
        while(vertexLstToClone != NULL) {
            newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
            newGraphVertexLst->nextVertex = createVertexLstElement(newVertex, NULL);

            newGraphVertexLst = newGraphVertexLst->nextVertex;
            vertexLstToClone = vertexLstToClone->nextVertex;
        }
    }

    //Copio la matrice di adiacenza
    AdjacentMatrix* newAdjacentMatrix = (AdjacentMatrix*)malloc(sizeof(AdjacentMatrix));
    newAdjacentMatrix->numVertex = ((GraphMat*)graph)->adjacentMatrix->numVertex;
    newAdjacentMatrix->slotAllocated = ((GraphMat*)graph)->adjacentMatrix->slotAllocated;

    newAdjacentMatrix->matrix = (bool**)malloc(sizeof(bool*) * newAdjacentMatrix->slotAllocated); //Alloco il vettore di puntatori ai vettori che comporranno la matrice
    for(int i = 0; i < newAdjacentMatrix->slotAllocated; i++) {
        newAdjacentMatrix->matrix[i] = malloc(sizeof(bool) * newAdjacentMatrix->slotAllocated); //Alloco un vettore che conterrà gli archi
        for(int j = 0; j < newAdjacentMatrix->slotAllocated; j++) {
            newAdjacentMatrix->matrix[i][j] = ((GraphMat*)graph)->adjacentMatrix->matrix[i][j];
        }
    }
    newGraph->adjacentMatrix = newAdjacentMatrix;

    return newGraph;
}

void* matGraphTranspose(void* graph) {
    GraphMat* newGraph = matGraphConstruct();

    //Copio i vertici appartenenti al grafo da copiare
    VertexLst* vertexLstToClone = ((GraphMat*)graph)->vertexLst;
    if(vertexLstToClone != NULL) { //Il grafo da clonare ha almeno un vertice
        Vertex* newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
        newGraph->vertexLst = createVertexLstElement(newVertex, NULL);

        vertexLstToClone = vertexLstToClone->nextVertex;

        VertexLst* newGraphVertexLst = newGraph->vertexLst;
        while(vertexLstToClone != NULL) {
            newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
            newGraphVertexLst->nextVertex = createVertexLstElement(newVertex, NULL);

            newGraphVertexLst = newGraphVertexLst->nextVertex;
            vertexLstToClone = vertexLstToClone->nextVertex;
        }

        //Copio la matrice di adiacenza
        AdjacentMatrix* newAdjacentMatrix = (AdjacentMatrix*)malloc(sizeof(AdjacentMatrix));
        newAdjacentMatrix->numVertex = ((GraphMat*)graph)->adjacentMatrix->numVertex;
        newAdjacentMatrix->slotAllocated = ((GraphMat*)graph)->adjacentMatrix->slotAllocated;

        newAdjacentMatrix->matrix = (bool**)malloc(sizeof(bool*) * newAdjacentMatrix->slotAllocated); //Alloco il vettore di puntatori ai vettori che comporranno la matrice
        for(int i = 0; i < newAdjacentMatrix->slotAllocated; i++) {
            newAdjacentMatrix->matrix[i] = malloc(sizeof(bool) * newAdjacentMatrix->slotAllocated); //Alloco un vettore che conterrà gli archi
            for(int j = 0; j < newAdjacentMatrix->slotAllocated; j++) {
                newAdjacentMatrix->matrix[i][j] = ((GraphMat*)graph)->adjacentMatrix->matrix[j][i];
            }
        }
        newGraph->adjacentMatrix = newAdjacentMatrix;
    }

    return newGraph;
}

bool matGraphInsertEdge(void* graph, int fromVertexName, int toVertexName) {
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
        if(vertexLst != NULL && vertexLst->vertexInfo->name == toVertexName) { //Il vertice di arrivo esiste
            if(((GraphMat*)graph)->adjacentMatrix->matrix[fromVertexPos][toVertexPos] != true) {
                ((GraphMat*)graph)->adjacentMatrix->matrix[fromVertexPos][toVertexPos] = true;
                return true;
            }
        }
    }

    return false;
}

bool matGraphRemoveEdge(void* graph, int fromVertexName, int toVertexName) {
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
        if(vertexLst != NULL && vertexLst->vertexInfo->name == toVertexName) { //Il vertice di arrivo esiste
            ((GraphMat*)graph)->adjacentMatrix->matrix[fromVertexPos][toVertexPos] = false;
            return true;
        }
    }

    return false;
}

bool matGraphExistsVertex(void* graph, int name) {
    VertexLst* currentVertexLstElem = ((GraphMat*)graph)->vertexLst;

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

        return ((GraphMat*)graph)->adjacentMatrix->matrix[fromVertexPos][toVertexPos];
    }

    return false;
}

DataObject* matGraphGetVertexData(void* graph, int name) {
    VertexLst* currentVertex = ((GraphMat*)graph)->vertexLst;

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

void matGraphSetVertexData(void* graph, int name, DataObject* newValue) {
    VertexLst* currentVertex = ((GraphMat*)graph)->vertexLst;

    while(currentVertex != NULL && currentVertex->vertexInfo->name < name){
        currentVertex = currentVertex->nextVertex;
    }

    if(currentVertex != NULL && currentVertex->vertexInfo->name == name) {
        adtSetValue(currentVertex->vertexInfo->label, newValue->value);
    }
}

int matGraphVertexFromPointer(ITRObject* iterator) {
    return ((Vertex*)itrElement(iterator))->name;
}

ITRObject* matGraphVertices(void* graph) {
    ITRType* iterType = ConstructVertexIterator();
    ITRObject* iterator = itrConstruct(iterType, ((GraphMat*)graph)->vertexLst);

    return iterator;
}

ITRObject* matGraphVertexEdges(void* graph, int name) {
    MatItrInterface* newIterator = initializeMatIterator(name, graph);

    ITRType* itrType = ConstructMatAdjacentIterator();
    ITRObject* iterator = itrConstruct(itrType, newIterator);

    return iterator;
}

GraphRepresentation* ConstructGraphMat() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = matGraphConstruct;
    type->graphDestruct = matGraphDestruct;

    type->graphEmpty = matGraphEmpty;

    type->graphTranspose = matGraphTranspose;

    type->graphClone = matGraphClone;

    type->graphInsertVertex = matGraphInsertVertex;
    type->graphRemoveVertex = matGraphRemoveVertex;
    type->graphInsertEdge = matGraphInsertEdge;
    type->graphRemoveEdge = matGraphRemoveEdge;

    type->graphExistsVertex = matGraphExistsVertex;
    type->graphExistsEdge = matGraphExistsEdge;

    type->graphGetVertexData = matGraphGetVertexData;
    type->graphSetVertexData = matGraphSetVertexData;

    type->graphVertexFromPointer = matGraphVertexFromPointer;

    type->graphVertices = matGraphVertices;
    type->graphVertexEdges = matGraphVertexEdges;


    return type;
}

void DestructGraphMat(GraphRepresentation* type) {
    free(type);
}

/* ************************************************************************** */

int deleteAdjacentRowColumn(AdjacentMatrix* adjacentMatrix, int vertexPosition) {
    int numAdjacentRemoved = 0;

    for(int i = 0; i < adjacentMatrix->numVertex; i++) {
        for(int j = 0; j < adjacentMatrix->numVertex; j++) {
            if((i == vertexPosition || j == vertexPosition) && adjacentMatrix->matrix[i][j] == true) { //Riga o colonna appartenente al vertice da rimuovere
                numAdjacentRemoved++;
            } else if (i < vertexPosition && j > vertexPosition) { //Zona della matrice a destra della colonna e sopra la riga del vertice da rimuovere
                adjacentMatrix->matrix[i][j-1] = adjacentMatrix->matrix[i][j];
            } else if(i > vertexPosition && j < vertexPosition) { //Zona della matrice  a sinistra della colonna e sotto la riga del vertice da rimuovere
                adjacentMatrix->matrix[i-1][j] = adjacentMatrix->matrix[i][j];
            } else if(i > vertexPosition && j > vertexPosition) { //Zona della matrice a destra della colonna e sotto la riga del vertice da rimuovere
                adjacentMatrix->matrix[i-1][j-1] = adjacentMatrix->matrix[i][j];
            }

            if(i == adjacentMatrix->numVertex-1 || j == adjacentMatrix->numVertex-1) { //Riga rimossa della matrice
                adjacentMatrix->matrix[i][j] = false;
            }
        }
    }

    adjacentMatrix->numVertex--;

    return numAdjacentRemoved;
}
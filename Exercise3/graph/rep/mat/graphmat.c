
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

void matGraphDestruct(void* graph) {
    GraphMat* graphMat = (GraphMat*)graph;

    VertexLst* vertexRef;
    while(graphMat->vertexLst != NULL) {
        vertexRef = graphMat->vertexLst;

        graphMat->vertexLst = graphMat->vertexLst->nextVertex;

        deleteVertexLstElem(vertexRef);
    }

    for(int i = 0; i < graphMat->slotAllocated; i++) {
        free(graphMat->adjacentMatrix[i]);
    }
    free(graphMat->adjacentMatrix);
}

bool matGraphInsertVertex(void* graph, int name, DataObject* label) { //TODO: COntrolla inserimento in testa di duplicati
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
        int cnt = 1;
        while(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name < name) {
            cnt++;
            currentVertexLstElem = currentVertexLstElem->nextVertex;
        }

        if(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name == name) { //Controllo se il vertice che si vuole inserire non sia già presente
            printf("Vertice già presente (%d - %d)\n", currentVertexLstElem->nextVertex->vertexInfo->name, name);
            return false;
        }

        printf("Inserisco vertice in posizione: %d\n", cnt);
        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElem = createVertexLstElement(newVertex, currentVertexLstElem->nextVertex);
        currentVertexLstElem->nextVertex = newVertexLstElem;
        graphMat->numVertex++;

        //Popolamento della rispettiva zona della  matrice di adiacenza
        if(graphMat->numVertex > graphMat->slotAllocated) { //La matrice di adiacenza va ingrandita
            graphMat->slotAllocated *= 2;

            graphMat->adjacentMatrix = realloc(graphMat->adjacentMatrix, sizeof(bool*) * graphMat->slotAllocated);
            for(int i = 0; i < graphMat->slotAllocated; i++) {
                graphMat->adjacentMatrix[i] = realloc(graphMat->adjacentMatrix[i], sizeof(bool) * graphMat->slotAllocated);
                for(int j = graphMat->slotAllocated/2; j < graphMat->slotAllocated; j++) {
                    //graphMat->adjacentMatrix[i][j] = false;
                }
            }
        }

        //Shifto gli elementi
        for(int i = graphMat->numVertex-1; i >= 0; i-- ) {
            for(int j = graphMat->numVertex-1; j >= 0; j--) {
                printf("(%d, %d) - ", i, j);
                if(i == j && (i > cnt || j > cnt)) { //Elemento sulla diagonale
                    printf("DIAGONALE\n");
                    graphMat->adjacentMatrix[i][j] = graphMat->adjacentMatrix[i-1][j-1];
                } else if(i == cnt || j == cnt) { //Nuova riga/colonna
                    printf("NUOVO ELEMENTO\n");
                    graphMat->adjacentMatrix[i][j] = false;
                } else if(i > j  && (i > cnt || j > cnt)) { //Elemento sotto diagonale
                    printf("SOTTO\n");
                    graphMat->adjacentMatrix[i][j] = graphMat->adjacentMatrix[i-1][j];
                } else if(i < j  && (i > cnt || j > cnt)) { //Elemento sopra diagonale
                    printf("SOPRA\n");
                    graphMat->adjacentMatrix[i][j] = graphMat->adjacentMatrix[i][j-1];
                } else {
                    printf("NIENTE\n");
                }
            }
        }
    }

    return true;
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
    newGraph->numVertex = ((GraphMat*)graph)->numVertex;

    //Copio la matrice di adiacenza
    newGraph->slotAllocated = ((GraphMat*)graph)->slotAllocated;
    bool** newAdjacentMatrix = (bool**)malloc(sizeof(bool*) * newGraph->slotAllocated); //Alloco il vettore di puntatori ai vettori che comporranno la matrice
    for(int i = 0; i < newGraph->slotAllocated; i++) {
        newAdjacentMatrix[i] = malloc(sizeof(bool) * newGraph->slotAllocated); //Alloco un vettore che conterrà gli archi //TODO: Sostiuire con calloc
        for(int j = 0; j < newGraph->slotAllocated; j++) {
            newAdjacentMatrix[i][j] = ((GraphMat*)graph)->adjacentMatrix[i][j];
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
        newGraph->numVertex = ((GraphMat*)graph)->numVertex;

        //Copio la matrice di adiacenza
        newGraph->slotAllocated = ((GraphMat*)graph)->slotAllocated;
        bool** newAdjacentMatrix = (bool**)malloc(sizeof(bool*) * newGraph->slotAllocated); //Alloco il vettore di puntatori ai vettori che comporranno la matrice
        for(int i = 0; i < newGraph->slotAllocated; i++) {
            newAdjacentMatrix[i] = malloc(sizeof(bool) * newGraph->slotAllocated); //Alloco un vettore che conterrà gli archi //TODO: Sostiuire con calloc
            for(int j = 0; j < newGraph->slotAllocated; j++) {
                newAdjacentMatrix[i][j] = ((GraphMat*)graph)->adjacentMatrix[j][i];
            }
        }

        newGraph->adjacentMatrix = newAdjacentMatrix;
    }

    return newGraph;
}

bool matGraphInsertEdge(void* graph, int fromVertexName, int toVertexName) { //TODO: Ottimizza sfruttando il fatto di sapere già toVertexName
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
            ((GraphMat*)graph)->adjacentMatrix[fromVertexPos][toVertexPos] = true;
            return true;
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
            ((GraphMat*)graph)->adjacentMatrix[fromVertexPos][toVertexPos] = false;
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

        return ((GraphMat*)graph)->adjacentMatrix[fromVertexPos][toVertexPos];
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
        adtSetValue(currentVertex->vertexInfo->label, newValue->value); //TODO: Si usa così setValue?
    } else {
        printf("Vertice %d non presente\n", name);
    }
}

GraphRepresentation* ConstructGraphMat() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = matGraphConstruct;
    type->graphDestruct = matGraphDestruct;

    type->graphEmpty = matGraphEmpty;

    type->graphTranspose = matGraphTranspose;

    type->graphClone = matGraphClone;

    type->graphInsertVertex = matGraphInsertVertex;
    //type->graphRemoveVertex = matGraphRemoveVertex;
    type->graphInsertEdge = matGraphInsertEdge;
    type->graphRemoveEdge = matGraphRemoveEdge;

    type->graphExistsVertex = matGraphExistsVertex;
    type->graphExistsEdge = matGraphExistsEdge;

    type->graphGetVertexData = matGraphGetVertexData;
    type->graphSetVertexData = matGraphSetVertexData;

    return type;
}

void DestructGraphMat(GraphRepresentation* type) {
    free(type);
}

#include "graphmat.h"

int deleteAdjacentRowColumn(GraphMat* graphMat, int vertexPosition);

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

bool matGraphInsertVertex(void* graph, int name, DataObject* label) {
    GraphMat* graphMat = graph;
    printf("DIMENSIONE ATTUALE MATRICE %dx%d\n", graphMat->slotAllocated, graphMat->slotAllocated);

    if(graphMat->vertexLst == NULL) { //Il grafo è vuoto
        //Creazione del nuovo vertice
        Vertex* newVertex = createVertex(name, label);
        VertexLst* newVertexLstElement = createVertexLstElement(newVertex, graphMat->vertexLst);
        graphMat->vertexLst = newVertexLstElement;
        graphMat->numVertex++;

        //Allocazione matrice di adiacenza
        graphMat->slotAllocated = 2;
        bool** newAdjacentMatrix = (bool**)malloc(sizeof(bool*) * graphMat->slotAllocated);
        for(int i = 0; i < graphMat->slotAllocated; i++) {
            newAdjacentMatrix[i] = (bool*)malloc(sizeof(bool) * graphMat->slotAllocated); //TODO: Sostiuire con calloc
            for(int j = 0; j < graphMat->slotAllocated; j++) {
                newAdjacentMatrix[i][j] = false; //Inizializzo la matrice a false per ogni campo
            }
        }

        graphMat->adjacentMatrix = newAdjacentMatrix;
    } else {
        if(graphMat->vertexLst->vertexInfo->name == name) { //Il vertice da inserire è già presente in testa
            printf("Vertice già presente (%d - %d)\n", graphMat->vertexLst->vertexInfo->name, name);
            return false;
        } else { //Cerco se il vertice è già presente nel grafo e, in caso contrario, la posizione dove inserirlo
            Vertex* newVertex;
            VertexLst* newVertexLstElem;

            int newVertexPosition = 0;
            if(graphMat->vertexLst->vertexInfo->name > name) { //Il vertice da inserire va inserito in testa
                newVertex = createVertex(name, label);
                newVertexLstElem = createVertexLstElement(newVertex, graphMat->vertexLst);
                graphMat->vertexLst = newVertexLstElem;
                graphMat->numVertex++;
            } else { //Localizzazione del vertice che si trova prima del punto di inserimento
                VertexLst* currentVertexLstElem = graphMat->vertexLst;

                newVertexPosition = 1; //Contatore che identifica la posizione del nuovo vertice nella matrice di adiacenza
                while(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name < name) {
                    currentVertexLstElem = currentVertexLstElem->nextVertex;
                    newVertexPosition++;
                }

                if(currentVertexLstElem->nextVertex != NULL && currentVertexLstElem->nextVertex->vertexInfo->name == name) { //Controllo se il vertice che si vuole inserire non sia già presente
                    printf("Vertice già presente (%d - %d)\n", currentVertexLstElem->nextVertex->vertexInfo->name, name);
                    return false;
                }

                //Creazione del vertice
                newVertex = createVertex(name, label);
                newVertexLstElem = createVertexLstElement(newVertex, currentVertexLstElem->nextVertex);
                currentVertexLstElem->nextVertex = newVertexLstElem;
                graphMat->numVertex++;
            }

            //Popolamento della rispettiva zona della  matrice di adiacenza
            if(graphMat->numVertex > graphMat->slotAllocated) { //La matrice di adiacenza va ingrandita
                printf("RIALLOCO MATRICE\n ----------------------");
                int newDimension = graphMat->slotAllocated*2;

                //Aumento il numero di righe
                bool** tmp = realloc(graphMat->adjacentMatrix, sizeof(*graphMat->adjacentMatrix) * newDimension); //Aumento il numero di righe
                if(tmp) {
                    graphMat->adjacentMatrix = tmp;
                    for(int i = 0; i < graphMat->slotAllocated; i++) {
                        graphMat->adjacentMatrix[graphMat->slotAllocated+i] = malloc(sizeof(*graphMat->adjacentMatrix[graphMat->slotAllocated+i]) * graphMat->slotAllocated); //Per ogni nuova riga, alloco un vettore con newDimension spazi
                    }
                }

                //Aumento il numero di colonne
                for(int i = 0; i < newDimension; i++) {
                    bool* tmp = realloc(graphMat->adjacentMatrix[i], sizeof(*graphMat->adjacentMatrix) * newDimension); //Per ogni nuova riga, rialloco un vettore con il nuovo numero di locazioni
                    if(tmp) {
                        graphMat->adjacentMatrix[i] = tmp;
                    }
                }

                graphMat->slotAllocated = newDimension;
            }

            //Shift dei valori della matrice
            for (int i = graphMat->numVertex - 1; i >= 0; i--) {
                for (int j = graphMat->numVertex - 1; j >= 0; j--) {
                    if (i == newVertexPosition || j == newVertexPosition) { //Nuova riga/colonna
                        graphMat->adjacentMatrix[i][j] = false;
                    } else if ((i > newVertexPosition || j > newVertexPosition) && i-1 >= 0 && j-1 >= 0) {
                        graphMat->adjacentMatrix[i][j] = graphMat->adjacentMatrix[i-1][j-1];
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
            adjacentRemoved = deleteAdjacentRowColumn(graph, 0);
            printf("Adiacenti rimossi: %d\n", adjacentRemoved);
            ((GraphMat*)graph)->numVertex--;

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
                adjacentRemoved = deleteAdjacentRowColumn(graph, vertexPosition);
                ((GraphMat*)graph)->numVertex--;

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
            if(((GraphMat*)graph)->adjacentMatrix[fromVertexPos][toVertexPos] != true) {
                ((GraphMat*)graph)->adjacentMatrix[fromVertexPos][toVertexPos] = true;
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
} //TODO: Forse puoi sfruttare l'inizializzazione della matrice per ritornare direttavemnte il valore della matrice contenuto alle coordinate passate come parametro

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
    type->graphRemoveVertex = matGraphRemoveVertex;
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

/* ************************************************************************** */

int deleteAdjacentRowColumn(GraphMat* graphMat, int vertexPosition) {
    int numAdjacentRemoved = 0;

    for(int i = 0; i < graphMat->numVertex; i++) {
        for(int j = 0; j < graphMat->numVertex; j++) {
            if((i == vertexPosition || j == vertexPosition) && graphMat->adjacentMatrix[i][j] == true) { //Riga o colonna appartenente al vertice da rimuovere
                printf("VERTICE RIMOSSO (%i, %d)\n", i, j);
                numAdjacentRemoved++;
            } else if (i < vertexPosition && j > vertexPosition) { //Zona della matrice a destra della colonna e sopra la riga del vertice da rimuovere
                graphMat->adjacentMatrix[i][j-1] = graphMat->adjacentMatrix[i][j];
            } else if(i > vertexPosition && j < vertexPosition) { //Zona della matrice  a sinistra della colonna e sotto la riga del vertice da rimuovere
                graphMat->adjacentMatrix[i-1][j] = graphMat->adjacentMatrix[i][j];
            } else if(i > vertexPosition && j > vertexPosition) { //Zona della matrice a destra della colonna e sotto la riga del vertice da rimuovere
                graphMat->adjacentMatrix[i-1][j-1] = graphMat->adjacentMatrix[i][j];
            }

            if(i == graphMat->numVertex-1 || j == graphMat->numVertex-1) { //Riga rimossa della matrice
                printf("ULTIMA RIGA O COLONNA\n");
                graphMat->adjacentMatrix[i][j] = false;
            }
        }
    }

    return numAdjacentRemoved;
}
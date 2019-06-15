
#include "graphbst.h"
#include "bst/bst.h"
#include "bst/rec/bstrec.h"
#include "adt/int/adtint.h"
#include "itr/itr.h"
#include "bst/bstitrpreord.h"

AdjacentBSTLst* createAdjacentBSTLstElem(Vertex* vertexPointer, AdjacentBSTLst* nextVertex);

/* ************************************************************************** */

void* bstGraphConstruct() {
    GraphBST* newGraphBST = (GraphBST*)malloc(sizeof(GraphBST));

    newGraphBST->vertexLst = NULL;
    newGraphBST->adjacentBSTLst = NULL;

    return newGraphBST;
}

void bstGraphDestruct(void* graph) {
    GraphBST* graphBST = (GraphBST*)graph;

    VertexLst* vertexRef;
    AdjacentBSTLst* adjacentRef;
    while(graphBST->vertexLst != NULL) {
        vertexRef = graphBST->vertexLst;
        adjacentRef = graphBST->adjacentBSTLst;

        graphBST->vertexLst = graphBST->vertexLst->nextVertex;
        graphBST->adjacentBSTLst = graphBST->adjacentBSTLst->nextVertex;

        deleteVertexLstElem(vertexRef);
        bstDestruct(adjacentRef->adjacentTree);
        free(adjacentRef->vertexPointer);
        //TODO: Aggiungere free vertexRef e freeAdhacentRef?
    }
}

bool bstGraphEmpty(void* graph) {
    return ((GraphBST*)graph)->vertexLst == NULL;
}

void* bstGraphTranspose(void* graph) {
    GraphBST* newGraph = bstGraphConstruct();

    VertexLst* vertexLstToClone = ((GraphBST*)graph)->vertexLst;
    AdjacentBSTLst* adjacentBstLstToClone = ((GraphBST*)graph)->adjacentBSTLst;

    if(vertexLstToClone != NULL) { //Il grafo da trasporre ha almeno un vertice
        //Clono il primo vertice
        Vertex* newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
        newGraph->vertexLst = createVertexLstElement(newVertex, NULL);
        newGraph->adjacentBSTLst = createAdjacentBSTLstElem(newVertex, NULL);

        vertexLstToClone = vertexLstToClone->nextVertex;
        adjacentBstLstToClone = adjacentBstLstToClone->nextVertex;

        //Clono il resto dei vertici
        VertexLst* newGraphVertexLst = newGraph->vertexLst;
        AdjacentBSTLst* newGraphAdjacentBSTLst = newGraph->adjacentBSTLst;
        while(vertexLstToClone != NULL) {
            newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
            newGraphVertexLst->nextVertex = createVertexLstElement(newVertex, NULL);

            newGraphAdjacentBSTLst->nextVertex = createAdjacentBSTLstElem(newVertex, NULL);

            newGraphVertexLst = newGraphVertexLst->nextVertex;
            newGraphAdjacentBSTLst = newGraphAdjacentBSTLst->nextVertex;

            vertexLstToClone = vertexLstToClone->nextVertex;
            adjacentBstLstToClone = adjacentBstLstToClone->nextVertex;
        }

        //Traspongo gli adiacenti
        adjacentBstLstToClone = ((GraphBST*)graph)->adjacentBSTLst; //Reinizializzo l'indice della lista di alberi del grafo di partenza
        newGraphAdjacentBSTLst = newGraph->adjacentBSTLst;  //Reinizializzo l'indice della lista di alberi del grafo trasposto

        ITRType* itrType;
        ITRObject* treeIterator;
        AdjacentBSTLst* index;
        DataObject* newAdjacent;
        DataType* intType = ConstructIntDataType();

        while(adjacentBstLstToClone != NULL) {
            itrType = ConstructBSTPreOrderIterator();
            treeIterator = itrConstruct(itrType, adjacentBstLstToClone->adjacentTree->root);

            while(!itrTerminated(treeIterator)) {
                int name = *(int*)((BSTNode*)itrElement(treeIterator))->key->value;

                index = newGraph->adjacentBSTLst; //Indice che scorre tutti gli elementi della lista di alberi per trovare quello in cui mettere il nuovo arco
                while(index != NULL && index->vertexPointer->name != name) {
                    index = index->nextVertex;
                }

                if(index != NULL) {
                    newAdjacent = adtConstruct(intType);
                    adtSetValue(newAdjacent, &adjacentBstLstToClone->vertexPointer->name);
                    bstInsert(index->adjacentTree, newAdjacent);
                    adtDestruct(newAdjacent);
                }

                itrSuccessor(treeIterator);
            }

            itrDestruct(treeIterator);
            DestructBSTPreOrderIterator(itrType);

            adjacentBstLstToClone = adjacentBstLstToClone->nextVertex;
            newGraphAdjacentBSTLst = newGraphAdjacentBSTLst->nextVertex;
        }
        DestructIntDataType(intType);
    }

    return newGraph;
}

void* bstGraphClone(void* graph) {
    GraphBST* newGraph = bstGraphConstruct();

    VertexLst* vertexLstToClone = ((GraphBST*)graph)->vertexLst;
    AdjacentBSTLst* adjacentBstLstToClone = ((GraphBST*)graph)->adjacentBSTLst;

    if(vertexLstToClone != NULL) { //Il grafo da clonare ha almeno un vertice
        //Clono il primo vertice
        Vertex* newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
        newGraph->vertexLst = createVertexLstElement(newVertex, NULL);
        newGraph->adjacentBSTLst = createAdjacentBSTLstElem(newVertex, NULL);
        newGraph->adjacentBSTLst->adjacentTree = bstClone(adjacentBstLstToClone->adjacentTree);

        vertexLstToClone = vertexLstToClone->nextVertex;
        adjacentBstLstToClone = adjacentBstLstToClone->nextVertex;

        //Clono il resto dei vertici
        VertexLst* newGraphVertexLst = newGraph->vertexLst;
        AdjacentBSTLst* newGraphAdjacentBSTLst = newGraph->adjacentBSTLst;
        while(vertexLstToClone != NULL) {
            newVertex = createVertex(vertexLstToClone->vertexInfo->name, vertexLstToClone->vertexInfo->label);
            newGraphVertexLst->nextVertex = createVertexLstElement(newVertex, NULL);

            newGraphAdjacentBSTLst->nextVertex = createAdjacentBSTLstElem(newVertex, NULL);
            newGraphAdjacentBSTLst->nextVertex->adjacentTree= bstClone(adjacentBstLstToClone->adjacentTree);

            newGraphVertexLst = newGraphVertexLst->nextVertex;
            newGraphAdjacentBSTLst = newGraphAdjacentBSTLst->nextVertex;

            vertexLstToClone = vertexLstToClone->nextVertex;
            adjacentBstLstToClone = adjacentBstLstToClone->nextVertex;
        }
    }

    return newGraph;
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

bool bstGraphExistsVertex(void* graph, int name) {
    VertexLst* currentVertexLstElem = ((GraphBST*)graph)->vertexLst;

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

bool bstGraphExistsEdge(void* graph, int fromVertexName, int toVertexName) {
    AdjacentBSTLst* adjacentLst = ((GraphBST*)graph)->adjacentBSTLst;

    while(adjacentLst != NULL && adjacentLst->vertexPointer->name != fromVertexName) { //TODO: Limitare ricerca in base all'ordine
        adjacentLst = adjacentLst->nextVertex;
    }

    if(adjacentLst != NULL) { //Il nodo da cui parte l'arco esiste
        DataObject* nameToFind = adtConstruct(ConstructIntDataType()); //TODO: Cercare di evitare di creare un constructInt ogni volta?
        adtSetValue(nameToFind, &toVertexName);

        return bstExists(adjacentLst->adjacentTree, nameToFind);
    }

    return false;
}

DataObject* bstGraphGetVertexData(void* graph, int name) {
    VertexLst* currentVertex = ((GraphBST*)graph)->vertexLst;

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

void bstGraphSetVertexData(void* graph, int name, DataObject* newValue) {
    VertexLst* currentVertex = ((GraphBST*)graph)->vertexLst;

    while(currentVertex != NULL && currentVertex->vertexInfo->name < name){
        currentVertex = currentVertex->nextVertex;
    }

    if(currentVertex != NULL && currentVertex->vertexInfo->name == name) {
        adtSetValue(currentVertex->vertexInfo->label, newValue->value); //TODO: Si usa così setValue
    } else {
        printf("Vertice %d non presente\n", name);
    }
}

GraphRepresentation* ConstructGraphBST() {
    GraphRepresentation* type = (GraphRepresentation*)malloc(sizeof(GraphRepresentation));

    type->graphConstruct = bstGraphConstruct;
    type->graphDestruct = bstGraphDestruct;

    type->graphEmpty = bstGraphEmpty;

    type->graphTranspose = bstGraphTranspose;

    type->graphClone = bstGraphClone;

    type->graphInsertVertex = bstGraphInsertVertex;
    type->graphRemoveVertex = bstGraphRemoveVertex;
    type->graphInsertEdge = bstGraphInsertEdge;
    type->graphRemoveEdge = bstGraphRemoveEdge;

    type->graphExistsVertex = bstGraphExistsVertex;
    type->graphExistsEdge = bstGraphExistsEdge;

    type->graphGetVertexData = bstGraphGetVertexData;
    type->graphSetVertexData = bstGraphSetVertexData;

    return type;
}

void DestructGraphBST(GraphRepresentation* type) {//TODO: Sicuro prenda graphRepresentation?
    free(type);
}

/* ************************************************************************** */

AdjacentBSTLst* createAdjacentBSTLstElem(Vertex* vertexPointer, AdjacentBSTLst* nextVertex) {
    AdjacentBSTLst* newAdjacentBSTLst = (AdjacentBSTLst*)malloc(sizeof(AdjacentBSTLst));

    newAdjacentBSTLst->vertexPointer = vertexPointer;
    newAdjacentBSTLst->adjacentTree = bstConstruct(ConstructBSTRecursive());
    newAdjacentBSTLst->nextVertex = nextVertex;

    return newAdjacentBSTLst;
}
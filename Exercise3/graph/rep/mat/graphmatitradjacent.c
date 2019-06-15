
#include "graphmatitradjacent.h"

/* ************************************************************************** */

MatItrInterface* initializeMatIterator(int name, void* graphMat) {
    GraphMat* graph = (GraphMat*)graphMat;

    MatItrInterface* interface = (MatItrInterface*)malloc(sizeof(MatItrInterface));

    interface->vertexName = name;
    interface->graphMat = (GraphMat*)graphMat;
    interface->rowVertex = 0;

    VertexLst* index = graph->vertexLst;
    while(index != NULL && index->vertexInfo->name != interface->vertexName) { //Cerca il primo adiacente nella matrice
        index = index->nextVertex;
        interface->rowVertex++;
    }

    if(index == NULL) { //Il vertice di cui si vuole iterare gli adiacenti non è presente
        interface->rowVertex = -1;
    }

    return interface;
}

void* itrMatAdjacentConstruct(void* type, void* matInterface) {
    ITRObject *iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphMatAdjacentIterator*)malloc(sizeof(GraphMatAdjacentIterator));

    ((GraphMatAdjacentIterator*)iterator->iterator)->matInterface = ((MatItrInterface*)matInterface);


    GraphMatAdjacentIterator* itr = (GraphMatAdjacentIterator*)iterator->iterator;
    if(itr->matInterface->rowVertex != -1) { //Il vertice da iterare esiste
        itr->currentElement = 0;
        while(itr->matInterface->graphMat->adjacentMatrix->matrix[itr->matInterface->rowVertex][itr->currentElement] != true) {
            itr->currentElement++;
        }

        if(itr->currentElement >= itr->matInterface->graphMat->adjacentMatrix->numVertex) { //Il vertice da iterare non ha adiacenti
            itr->currentElement = -1;
        }
    } else {
        itr->currentElement = -1; //Il vertice da iterare non esiste
    }

    return iterator;
}

void itrMatAdjacentDestruct(void* iterator) {
    free(iterator);
}

bool itrMatAdjacentTerminated(void* iterator) {
    GraphMatAdjacentIterator* itr = ((GraphMatAdjacentIterator*)iterator);
    return itr->currentElement == -1;
}

void* itrMatAdjacentGetElement(void* iterator) {
    GraphMatAdjacentIterator* itr = ((GraphMatAdjacentIterator*)iterator);

    int index = 0;
    VertexLst* vertexLst = itr->matInterface->graphMat->vertexLst;
    while(vertexLst != NULL && index != itr->currentElement) {
        vertexLst = vertexLst->nextVertex;
        index++;
    }

    if(vertexLst != NULL) {
        return vertexLst->vertexInfo;
    } else {
        printf("Vertice non trovato\n");
    }

    return NULL;
}

void itrMatAdjacentSuccessor(void *iterator) {
    GraphMatAdjacentIterator *itr = (GraphMatAdjacentIterator*)iterator;

    do {
        itr->currentElement++;
    } while (itr->currentElement < itr->matInterface->graphMat->adjacentMatrix->numVertex && itr->matInterface->graphMat->adjacentMatrix->matrix[itr->matInterface->rowVertex][itr->currentElement] != true);

    if(itr->currentElement >= itr->matInterface->graphMat->adjacentMatrix->numVertex) {
        itr->currentElement = -1; //Gli adiacenti sono terminati
    }
}

ITRType* ConstructMatAdjacentIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = itrMatAdjacentConstruct;
    type->destruct = itrMatAdjacentDestruct;

    type->terminated = itrMatAdjacentTerminated;

    type->getElement = itrMatAdjacentGetElement;

    type->successor = itrMatAdjacentSuccessor;

    return type;
}

void DestructMatAdjacentIterator(ITRType* type) {
    free(type);
}
/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "graphlstitradjacent.h"

/* ************************************************************************** */

LstItrInterface* initializeLstIterator(int name, void* adjacentLst) {
    LstItrInterface* interface = (LstItrInterface*)malloc(sizeof(LstItrInterface));

    interface->vertexName = name;

    AdjacentLst* index = (AdjacentLst*)adjacentLst;
    while(index != NULL && index->vertexPointer->name != interface->vertexName) {
        index = index->nextVertex;
    }

    if(index != NULL) {
        interface->adjacent = index->nextAdjacent; //Supero il riferimento del vertice di apaprtenenza nella lista
    } else { //Iteratore vuoto
        interface->adjacent = NULL;
    }

    return interface;
}

void* itrLstAdjacentConstruct(void* type, void* lstInterface) {
    ITRObject *iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphLstAdjacentIterator*)malloc(sizeof(GraphLstAdjacentIterator));

    ((GraphLstAdjacentIterator*)iterator->iterator)->element = ((LstItrInterface*)lstInterface);

    return iterator;
}

void itrLstAdjacentDestruct(void* iterator) {
    free(iterator);
}

bool itrLstAdjacentTerminated(void* iterator) {
    return ((GraphLstAdjacentIterator*)iterator)->element->adjacent == NULL ? true : false;
}

void* itrLstAdjacentGetElement(void* iterator) {
    return ((GraphLstAdjacentIterator*)iterator)->element->adjacent->vertexPointer;
}

void itrLstAdjacentSuccessor(void *iterator) {
    GraphLstAdjacentIterator *itr = (GraphLstAdjacentIterator*)iterator;

    if (itr->element->adjacent != NULL) {
        itr->element->adjacent = itr->element->adjacent->nextAdjacent;
    }
}

ITRType* ConstructLstAdjacentIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = itrLstAdjacentConstruct;
    type->destruct = itrLstAdjacentDestruct;

    type->terminated = itrLstAdjacentTerminated;

    type->getElement = itrLstAdjacentGetElement;

    type->successor = itrLstAdjacentSuccessor;

    return type;
}

void DestructLstAdjacentIterator(ITRType* type) {
    free(type);
}
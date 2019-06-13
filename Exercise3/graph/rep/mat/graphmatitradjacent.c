
#include "graphmatitradjacent.h"

/* ************************************************************************** */

void* itrMatAdjacentConstruct(void* type, void* adjacentVector) {
    ITRObject *iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphMatAdjacentIterator*)malloc(sizeof(GraphMatAdjacentIterator));

    ((GraphMatAdjacentIterator*)iterator->iterator)->element = ((AdjacentLst*)adjacentLst)->nextAdjacent; //NextAdjacent per "saltare" il vertice di riferimento
    ((GraphMatAdjacentIterator*)iterator->iterator)->numVertex =

    return iterator;
}

void itrMatAdjacentDestruct(void* iterator) {
    free(iterator);
}

bool itrMatAdjacentTerminated(void* iterator) {
    return ((GraphLstAdjacentIterator*)iterator)->element == NULL ? true : false;
}

void* itrMatAdjacentGetElement(void* iterator) {
    return ((GraphLstAdjacentIterator*)iterator)->element;
}

void itrMatAdjacentSuccessor(void *iterator) {
    GraphLstAdjacentIterator *itr = (GraphLstAdjacentIterator*)iterator;

    if (itr->element != NULL) {
        itr->element = itr->element->nextAdjacent;
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
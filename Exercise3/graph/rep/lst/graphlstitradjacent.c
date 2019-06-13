
#include "graphlstitradjacent.h"

/* ************************************************************************** */

void* itrLstAdjacentConstruct(void* type, void* adjacentLst) {
    ITRObject *iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphLstAdjacentIterator*)malloc(sizeof(GraphLstAdjacentIterator));

    ((GraphLstAdjacentIterator*)iterator->iterator)->element = ((AdjacentLst*)adjacentLst)->nextAdjacent; //NextAdjacent per "saltare" il vertice di riferimento

    return iterator;
}

void itrLstAdjacentDestruct(void* iterator) {
    free(iterator);
}

bool itrLstAdjacentTerminated(void* iterator) {
    return ((GraphLstAdjacentIterator*)iterator)->element == NULL ? true : false;
}

void* itrLstAdjacentGetElement(void* iterator) {
    return ((GraphLstAdjacentIterator*)iterator)->element;
}

void itrLstAdjacentSuccessor(void *iterator) {
    GraphLstAdjacentIterator *itr = (GraphLstAdjacentIterator*)iterator;

    if (itr->element != NULL) {
        itr->element = itr->element->nextAdjacent;
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
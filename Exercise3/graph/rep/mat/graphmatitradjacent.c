
#include "graphmatitradjacent.h"

/* ************************************************************************** */

void* itrMatAdjacentConstruct(void* type, void* adjacentMatrix) {
    ITRObject *iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphMatAdjacentIterator*)malloc(sizeof(GraphMatAdjacentIterator));

    ((GraphMatAdjacentIterator*)iterator->iterator)->adjacentMatrix = ((AdjacentMatrix*)adjacentMatrix);
    ((GraphMatAdjacentIterator*)iterator->iterator)->currentRow = 0;
    ((GraphMatAdjacentIterator*)iterator->iterator)->currentColumn = 0;

    return iterator;
}

void itrMatAdjacentDestruct(void* iterator) {
    free(iterator);
}

bool itrMatAdjacentTerminated(void* iterator) {
    GraphMatAdjacentIterator* itr = ((GraphMatAdjacentIterator*)iterator);

    printf("TERMINATO? ");
    if(itr->currentRow == itr->adjacentMatrix->numVertex && itr->currentRow == itr->adjacentMatrix->numVertex) {
        printf("SI\n");
        return true;
    } else {
        printf("NO\n");
        return false;
    }
}

void* itrMatAdjacentGetElement(void* iterator) {
    GraphMatAdjacentIterator* itr = ((GraphMatAdjacentIterator*)iterator);
    printf("ELEMENTO: (%d, %d)", itr->currentRow, itr->currentColumn);
    if(itr->adjacentMatrix->matrix[itr->currentRow][itr->currentColumn]) {
        printf(" T ");
    } else {
        printf(" F ");
    }

    return itr->adjacentMatrix->matrix[itr->currentRow][itr->currentColumn];
}

void itrMatAdjacentSuccessor(void *iterator) {
    GraphMatAdjacentIterator *itr = (GraphMatAdjacentIterator*)iterator;

    if (itr->currentColumn < itr->adjacentMatrix->numVertex) {
        itr->currentColumn += 1;
    } else if(itr->currentRow < itr->adjacentMatrix->numVertex) {
        itr->currentRow +=1;
        itr->currentColumn = 0;
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
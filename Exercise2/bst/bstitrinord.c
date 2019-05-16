
#include "bstitrinord.h"

#include "../stack/vec/stackvec.h"

/* ************************************************************************** */

void itrInOrderDestruct(void* iterator) {
    stkDestruct(((BSTInOrderIterator*)iterator)->stack);
    free(iterator);
}

bool itrInOrderTerminated(void* iterator) {
    return ((BSTInOrderIterator*)((ITRObject*)iterator)->iterator)->element == NULL ? true : false;
}

void* itrInOrderGetElement(void* iterator) {
    return ((BSTInOrderIterator*)((ITRObject*)iterator)->iterator)->element;
}

ITRType* ConstructBSTInOrderIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    //type->construct = itrInOrderConstruct;
    type->destruct = itrInOrderDestruct;

    type->terminated = itrInOrderTerminated;

    type->getElement = itrInOrderGetElement;

    //type->successor = itrInOrderSuccessor;

    return type;
}

void DestructBSTInOrderIterator(ITRType* type) {
    free(type); //TODO: Per ogni chiamata di free, aggiungere = NULL?
}
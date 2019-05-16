
#include "bstitrpostord.h"

#include "../stack/vec/stackvec.h"

/* ************************************************************************** */

void itrPostOrderDestruct(void* iterator) {
    stkDestruct(((BSTPostOrderIterator*)iterator)->stack);
    free(iterator);
}

bool itrPostOrderTerminated(void* iterator) {
    return ((BSTPostOrderIterator*)((ITRObject*)iterator)->iterator)->element == NULL ? true : false;
}

void* itrPostOrderGetElement(void* iterator) {
    return ((BSTPostOrderIterator*)((ITRObject*)iterator)->iterator)->element;
}

ITRType* ConstructBSTPostOrderIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    //type->construct = itrPostOrderConstruct;
    type->destruct = itrPostOrderDestruct;

    type->terminated = itrPostOrderTerminated;

    type->getElement = itrPostOrderGetElement;

    //type->successor = itrPostOrderSuccessor;

    return type;
}

void DestructBSTPostOrderIterator(ITRType* type) {
    free(type);
}
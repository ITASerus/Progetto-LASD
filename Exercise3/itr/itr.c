
#include <bst/bst.h>
#include "itr.h"

/* ************************************************************************** */

ITRObject* itrConstruct(ITRType* type, void* source) {
    return type->construct(type, source); //TODO: Tolto cast a bstNode. Ritestare
}

void itrDestruct(ITRObject* iterator) {
    iterator->type->destruct(iterator->iterator);
}


bool itrTerminated(ITRObject* iterator) {
    return iterator->type->terminated(iterator->iterator);
}


void* itrElement(ITRObject* iterator) {
    return iterator->type->getElement(iterator->iterator);
}


void itrSuccessor(ITRObject* iterator) {
    return iterator->type->successor(iterator->iterator);
}
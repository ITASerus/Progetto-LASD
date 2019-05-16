
#include <bst/bst.h>
#include "itr.h"

/* ************************************************************************** */

ITRObject* itrConstruct(ITRType* type, void* tree) {
    return type->construct(type, (BSTNode*)tree);
}

void itrDestruct(ITRObject* iterator) {
    iterator->type->destruct(iterator);
}


bool itrTerminated(ITRObject* iterator) {
    return iterator->type->terminated(iterator);
}


void* itrElement(ITRObject* iterator) {
    return iterator->type->getElement(iterator);
}


void itrSuccessor(ITRObject* iterator) {
    return iterator->type->successor(iterator);
}
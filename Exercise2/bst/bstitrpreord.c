
#include "bstitrpreord.h"

#include "../stack/vec/stackvec.h"

/* ************************************************************************** */

void* itrPreOrderConstruct(void* type, void* tree) {
    ITRObject* iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*) type;
    iterator->iterator = (BSTPreOrderIterator*)malloc(sizeof(BSTPreOrderIterator));
    ((BSTPreOrderIterator*)iterator->iterator)->stack = stkConstruct(ConstructStackVecType());
    ((BSTPreOrderIterator*)iterator->iterator)->element = (BSTNode*) tree;

    return iterator;
}

void itrPreOrderDestruct(void* iterator) {
    stkDestruct(((BSTPreOrderIterator*)iterator)->stack);
    free(iterator);
}

bool itrPreOrderTerminated(void* iterator) {
    return ((BSTPreOrderIterator*)((ITRObject*)iterator)->iterator)->element == NULL ? true : false;
}

void* itrPreOrderGetElement(void* iterator) {
    return ((BSTPreOrderIterator*)((ITRObject*)iterator)->iterator)->element;
}

void itrPreOrderSuccessor(void* iterator) {
    //stkPush(((BSTPreOrderIterator*)((ITRObject*)iterator)->iterator)->stack, ((BSTPreOrderIterator*)((ITRObject*)iterator)->iterator)->element->key);
}

ITRType* ConstructBSTPreOrderIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = itrPreOrderConstruct;
    type->destruct = itrPreOrderDestruct;

    type->terminated = itrPreOrderTerminated;

    type->getElement = itrPreOrderGetElement;

    type->successor = itrPreOrderSuccessor;

    return type;
}

void DestructBSTPreOrderIterator(ITRType* type) { //TODO: Aggiungi controlli?
    free(type); //TODO: Per ogni chiamata di free, aggiungere = NULL?
}
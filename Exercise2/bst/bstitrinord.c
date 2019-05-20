
#include "bstitrinord.h"

#include "../stack/vec/stackvec.h"
#include "../adt/ptr/adtptr.h"

/* ************************************************************************** */

BSTNode* minTree(BSTInOrderIterator *iterator)
{
    if (iterator->element != NULL) {
        DataObject* node = adtConstruct(ConstructPointerDataType());

        while ((iterator->element)->left != NULL) {
            adtSetValue(node, iterator->element);
            stkPush(iterator->stack, node);
            iterator->element = (iterator->element)->left;
        }
        adtDestruct(node);
    }

    return iterator->element;
}


void* itrInOrderConstruct(void* type, void* tree) {
    ITRObject* iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*) type;
    iterator->iterator = (BSTInOrderIterator*)malloc(sizeof(BSTInOrderIterator));

    ((BSTInOrderIterator*)(iterator->iterator))->stack = stkConstruct(ConstructStackVecType());
    ((BSTInOrderIterator*)(iterator->iterator))->element = (BSTNode*)tree;
    ((BSTInOrderIterator*)(iterator->iterator))->element = minTree((BSTInOrderIterator*)(iterator->iterator));

    return iterator;
}

void itrInOrderDestruct(void* iterator) {
    stkDestruct(((BSTInOrderIterator*)iterator)->stack);
    free(iterator);
}

bool itrInOrderTerminated(void* iterator) {
    return ((BSTInOrderIterator*)iterator)->element == NULL ? true : false;
}

void* itrInOrderGetElement(void* iterator) {
    return ((BSTInOrderIterator*)iterator)->element;
}

void itrInOrderSuccessor(void *iterator) {
    BSTInOrderIterator *itr = (BSTInOrderIterator*)iterator;

    if (itr->element != NULL) {
        if ((itr->element)->right != NULL) {
            itr->element = (itr->element)->right;
            itr->element = minTree(itr);
        } else {
            if (!stkEmpty(itr->stack)) {
                itr->element = (BSTNode*)adtGetValue(stkTopNPop(itr->stack));
            } else {
                itr->element = NULL;
            }
        }
    }
}

ITRType* ConstructBSTInOrderIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = itrInOrderConstruct;
    type->destruct = itrInOrderDestruct;

    type->terminated = itrInOrderTerminated;

    type->getElement = itrInOrderGetElement;

    type->successor = itrInOrderSuccessor;

    return type;
}

void DestructBSTInOrderIterator(ITRType* type) {
    free(type);
}

#include "bstitrbreadth.h"

#include "../queue/vec/queuevec.h"
#include "../adt/ptr/adtptr.h"

/* ************************************************************************** */

void* itrBreadthConstruct(void* type, void* tree) {
    ITRObject* iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*) type;
    iterator->iterator = (BSTBreadthIterator*)malloc(sizeof(BSTBreadthIterator));
    ((BSTBreadthIterator*)iterator->iterator)->queue = queConstruct(ConstructQueueVecType());
    ((BSTBreadthIterator*)iterator->iterator)->element = (BSTNode*) tree;

    return iterator;
}

void itrBreadthDestruct(void* iterator) {
    queDestruct( ((BSTBreadthIterator*)iterator)->queue );
    free(iterator);
}


bool itrBreadthTerminated(void* iterator) {
    return ((BSTBreadthIterator*)((ITRObject*)iterator)->iterator)->element == NULL ? true : false;
}

void* itrBreadthGetElement(void* iterator) {
    return ((BSTBreadthIterator*)((ITRObject*)iterator)->iterator)->element;
}

void itrBreadthSuccessor(void* iterator) {
    BSTBreadthIterator *itr = (BSTBreadthIterator*)((ITRObject*)iterator)->iterator;

    if(itr->element != NULL) {
        if(itr->element->left != NULL) {
            DataObject *sx = adtConstruct(ConstructPointerDataType());
            adtSetValue(sx, itr->element->left);
            queEnqueue(itr->queue, sx);
        }

        if(itr->element->right != NULL) {
            DataObject *dx = adtConstruct(ConstructPointerDataType());
            adtSetValue(dx, itr->element->right);
            queEnqueue(itr->queue, dx);
        }

        if(!queEmpty(itr->queue)) {
            itr->element = (BSTNode*)adtGetValue(queHeadNDequeue(itr->queue));
        } else {
            itr->element = NULL;
        }
    }
}


ITRType* ConstructBSTBreadthIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = itrBreadthConstruct;
    type->destruct = itrBreadthDestruct;

    type->terminated = itrBreadthTerminated;

    type->getElement = itrBreadthGetElement;

    type->successor = itrBreadthSuccessor;

    return type;
}

void DestructBSTBreadthIterator(ITRType* type) {
    free(type);
}
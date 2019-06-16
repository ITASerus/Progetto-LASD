/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "bstitrpreord.h"

#include "../stack/vec/stackvec.h"
#include "../adt/ptr/adtptr.h"

/* ************************************************************************** */

void* itrPreOrderConstruct(void* type, void* tree) {
    ITRObject* iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
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
    return ((BSTPreOrderIterator*)iterator)->element == NULL ? true : false;
}

void* itrPreOrderGetElement(void* iterator) {
    return ((BSTPreOrderIterator*)iterator)->element;
}

void itrPreOrderSuccessor(void* iterator) {
    BSTPreOrderIterator *itr = (BSTPreOrderIterator*)iterator;

    if (itr->element != NULL) {
        DataObject *node = adtConstruct(ConstructPointerDataType());
        adtSetValue(node, itr->element);
        stkPush(itr->stack, node);

        itr->element = (itr->element)->left;

        while (itr->element == NULL && !stkEmpty(itr->stack)) {
            itr->element = (BSTNode*)adtGetValue(stkTopNPop(itr->stack));

            itr->element = (itr->element)->right;
        }
        adtDestruct(node);
    }
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

void DestructBSTPreOrderIterator(ITRType* type) {
    free(type);
}
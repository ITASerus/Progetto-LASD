/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "bstitrpostord.h"

#include "../stack/vec/stackvec.h"
#include "../adt/ptr/adtptr.h"

/* ************************************************************************** */

BSTNode *firstNode(BSTPostOrderIterator *iter) {
    if (iter->element != NULL) {
        DataObject *nodo = adtConstruct(ConstructPointerDataType());

        while ((iter->element->left != NULL) || (iter->element->right != NULL)) {
            adtSetValue(nodo, iter->element);
            stkPush(iter->stack, nodo);

            if (iter->element->left != NULL) {
                iter->element = iter->element->left;
            } else {
                iter->element = iter->element->right;
            }
        }

        //DestructPointerDataType(ptrType);
        adtDestruct(nodo);
    }

    return iter->element;
}


void* itrPostOrderConstruct(void* type, void* tree) {
    ITRObject *iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (BSTPostOrderIterator*)malloc(sizeof(BSTPostOrderIterator));

    ((BSTPostOrderIterator*)iterator->iterator)->stack = stkConstruct(ConstructStackVecType());
    ((BSTPostOrderIterator*)iterator->iterator)->element = (BSTNode*)tree;
    ((BSTPostOrderIterator*)iterator->iterator)->element = firstNode((BSTPostOrderIterator*)iterator->iterator);

    return iterator;
}

void itrPostOrderDestruct(void* iterator) {
    stkDestruct(((BSTPostOrderIterator*)iterator)->stack);
    free(iterator);
}

bool itrPostOrderTerminated(void* iterator) {
    return ((BSTPostOrderIterator*)iterator)->element == NULL ? true : false;
}

void* itrPostOrderGetElement(void* iterator) {
    return ((BSTPostOrderIterator*)iterator)->element;
}

void itrPostOrderSuccessor(void *iterator) {
    BSTPostOrderIterator *itr = (BSTPostOrderIterator*)iterator;

    if (!stkEmpty(itr->stack)) {
        BSTNode *last = itr->element;
        itr->element = (BSTNode*)adtGetValue(stkTop(itr->stack));

        if ((itr->element)->right && last != (itr->element)->right) {
            itr->element = (itr->element)->right;
            itr->element = firstNode(itr);
        } else {
            stkPop(itr->stack);
        }
    } else {
        itr->element = NULL;
    }
}

ITRType* ConstructBSTPostOrderIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = itrPostOrderConstruct;
    type->destruct = itrPostOrderDestruct;

    type->terminated = itrPostOrderTerminated;

    type->getElement = itrPostOrderGetElement;

    type->successor = itrPostOrderSuccessor;

    return type;
}

void DestructBSTPostOrderIterator(ITRType* type) {
    free(type);
}
/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "graphbstitradjacent.h"
#include "../../../bst/bstitrinord.h"
/* ************************************************************************** */

BSTItrInterface* initializeBSTIterator(int name, void* graphBST) {
    BSTItrInterface* interface = (BSTItrInterface*)malloc(sizeof(BSTItrInterface));

    interface->vertexName = name;
    interface->graphBST = graphBST;

    interface->adjacentTree = ((GraphBST*)graphBST)->adjacentBSTLst;
    while(interface->adjacentTree != NULL && interface->adjacentTree->vertexPointer->name != interface->vertexName) {
        interface->adjacentTree = interface->adjacentTree->nextVertex;
    }

    return interface;
}

void* itrBSTAdjacentConstruct(void* type, void* bstInterface) {
    ITRObject *iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphBSTAdjacentIterator*)malloc(sizeof(GraphBSTAdjacentIterator));

    ((GraphBSTAdjacentIterator*)iterator->iterator)->bstInterface = bstInterface;

    GraphBSTAdjacentIterator* itr = (GraphBSTAdjacentIterator*)iterator->iterator;
    if( itr->bstInterface->adjacentTree != NULL) { //Nel grafo è presente il vertice che si vuole iterare
        itr->treeIterator = itrConstruct(ConstructBSTInOrderIterator(), itr->bstInterface->adjacentTree->adjacentTree->root);
    } else {
        itr->treeIterator = NULL;
    }

    return iterator;
}

void itrBSTAdjacentDestruct(void* iterator) {
    itrDestruct(((GraphBSTAdjacentIterator*)iterator)->treeIterator);
    free(iterator);
}

bool itrBSTAdjacentTerminated(void* iterator) {
    if(((GraphBSTAdjacentIterator*)iterator)->treeIterator) {
        return itrTerminated(((GraphBSTAdjacentIterator*)iterator)->treeIterator);
    } else {
        return true;
    }

}

void* itrBSTAdjacentGetElement(void* iterator) {
    int name = *(int*)((BSTNode*)itrElement(((GraphBSTAdjacentIterator*)iterator)->treeIterator))->key->value;

    VertexLst* index = ((GraphBSTAdjacentIterator*)iterator)->bstInterface->graphBST->vertexLst;
    while(index->vertexInfo->name != name) {
        index = index->nextVertex;
    }

    if(index != NULL) {
        return index->vertexInfo;
    } else {
        return NULL;
    }
}

void itrBSTAdjacentSuccessor(void *iterator) {
    itrSuccessor(((GraphBSTAdjacentIterator*)iterator)->treeIterator);
}

ITRType* ConstructBSTAdjacentIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = itrBSTAdjacentConstruct;
    type->destruct = itrBSTAdjacentDestruct;

    type->terminated = itrBSTAdjacentTerminated;

    type->getElement = itrBSTAdjacentGetElement;

    type->successor = itrBSTAdjacentSuccessor;

    return type;
}

void DestructBSTAdjacentIterator(ITRType* type) {
    free(type);
}
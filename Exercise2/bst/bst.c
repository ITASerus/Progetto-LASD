
#include "bst.h"

/* ************************************************************************** */

BSTObject* bstConstruct(BSTType* bstType) {
    BSTObject* newTree = (BSTObject*)malloc(sizeof(BSTObject));

    newTree->type = bstType;
    newTree->root = NULL;
    newTree->numberOfNodes = 0;

    return newTree;
}


void bstDestruct(BSTObject* tree) {
    tree->type->destruct(tree->root);
    free(tree);
}


bool bstEmpty(BSTObject* tree) {
    return (tree->root == NULL);
}


int bstSize(BSTObject* tree) {
    return tree->numberOfNodes;
}


void bstClear(BSTObject* tree) {
    tree->type->destruct(tree->root);
    tree->root = NULL;
    tree->numberOfNodes = 0;
}


BSTObject* bstClone(BSTObject* tree) {
    BSTObject* clonedTree = (BSTObject*)malloc(sizeof(BSTObject));

    clonedTree->type = tree->type;
    clonedTree->root = clonedTree->type->clone(tree->root);
    clonedTree->numberOfNodes = tree->numberOfNodes;

    return clonedTree;
}


bool bstEqual(BSTObject* firstTree, BSTObject* secondTree) {
    return firstTree->type->equal(firstTree->root, secondTree->root); //TODO: Rivedi confronto tipi
}


bool bstExists(BSTObject* tree, DataObject* keyToFind) {
    return tree->type->exists(tree->root, keyToFind);
}


void bstInsert(BSTObject* tree, DataObject* newKey) {
    if(tree->type->insert(&(tree->root), newKey)) {
        tree->numberOfNodes++;
    }
}

void bstRemove(BSTObject* tree, DataObject* keyToRemove) {
    if(tree->numberOfNodes > 0) {
        if(tree->type->remove(&(tree->root), keyToRemove)) {
            tree->numberOfNodes--;
        }
    }
}

DataObject* bstGetMin(BSTObject* tree) {
    return tree->type->getMin(tree->root);
}

DataObject* bstGetNRemoveMin(BSTObject* tree) {
    DataObject* minValue = tree->type->getNRemoveMin(&(tree->root));

    if(minValue != NULL) {
        tree->numberOfNodes--;
    }
    return minValue;
}

void bstRemoveMin(BSTObject* tree) {
    if(tree->type->removeMin(&tree->root)){
        tree->numberOfNodes--;
    }
}

DataObject* bstGetMax(BSTObject* tree) {
    return tree->type->getMax(tree->root);
}

DataObject* bstGetNRemoveMax(BSTObject* tree) {
    DataObject* maxValue = tree->type->getNRemoveMax(&(tree->root));

    if(maxValue != NULL) {
        tree->numberOfNodes--;
    }
    return maxValue;
}

void bstRemoveMax(BSTObject* tree) {
    if(tree->type->removeMax(&tree->root)){
        tree->numberOfNodes--;
    }
}


DataObject* bstGetPredecessor(BSTObject* tree, DataObject* key) {
    return tree->type->getPredecessor(tree->root, key);
}

DataObject* bstGetNRemovePredecessor(BSTObject* tree, DataObject* key) {
    DataObject* predecessor = tree->type->getNRemovePredecessor(&tree->root, key);

    if(predecessor != NULL) {
        tree->numberOfNodes--;
    }
    return predecessor;
}

void bstRemovePredecessor(BSTObject* tree, DataObject* key) {
    if(tree->type->removePredecessor(&tree->root, key)){
        tree->numberOfNodes--;
    }
}

DataObject* bstGetSuccessor(BSTObject* tree, DataObject* key) {
    return tree->type->getSuccessor(tree->root, key);
}

DataObject* bstGetNRemoveSuccessor(BSTObject* tree, DataObject* key) {
    DataObject* successor = tree->type->getNRemoveSuccessor(&tree->root, key);

    if(successor != NULL) {
        tree->numberOfNodes--;
    }
    return successor;
}

void bstRemoveSuccessor(BSTObject* tree, DataObject* key) {
    if(tree->type->removeSuccessor(&tree->root, key)){
        tree->numberOfNodes--;
    }
}


void bstPreOrderMap(BSTObject* tree, MapFun mapFunction, void* param) {
    tree->type->preOrderMap(tree->root, mapFunction, param);
}

void bstInOrderMap(BSTObject* tree, MapFun mapFunction, void* param) {
    tree->type->inOrderMap(tree->root, mapFunction, param);
}

void bstPostOrderMap(BSTObject* tree, MapFun mapFunction, void* param) {
    tree->type->postOrderMap(tree->root, mapFunction, param);
}

void bstBreadthMap(BSTObject* tree, MapFun mapFunction, void* param) {
    tree->type->breadthMap(tree->root, mapFunction, param);
}

void bstPreOrderFold(BSTObject* tree, FoldFun foldFunction, void* accumulator, void* param) {
    tree->type->preOrderFold(tree->root, foldFunction, accumulator, param);
}

void bstInOrderFold(BSTObject* tree, FoldFun foldFunction, void* accumulator, void* param) {
    tree->type->inOrderFold(tree->root, foldFunction, accumulator, param);
}

void bstPostOrderFold(BSTObject* tree, FoldFun foldFunction, void* accumulator, void* param) {
    tree->type->postOrderFold(tree->root, foldFunction, accumulator, param);
}

void bstBreadthFold(BSTObject* tree, FoldFun foldFunction, void* accumulator, void* param) {
    tree->type->breadthFold(tree->root, foldFunction, accumulator, param);
}
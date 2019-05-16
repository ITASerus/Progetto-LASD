
#include "bstitr.h"

#include "../bstitrpreord.h"
#include "../bstitrinord.h"
#include "../bstitrpostord.h"
#include "../bstitrbreadth.h"
#include "../../stack/vec/stackvec.h"
#include "../../adt/ptr/adtptr.h"

/* ************************************************************************** */

void itrBSTDestruct(BSTObject* tree) { //TODO: Sostituire BSTObject con BSTNode
    ITRType* itrType = ConstructBSTPostOrderIterator();
    ITRObject* iterator = itrConstruct(itrType, tree->root);
    BSTNode* curr;

    while(!itrTerminated(iterator)) {
        curr = (BSTNode*)itrElement(iterator);
        adtDestruct(curr->key); //TODO: Sostituire tutto con una macrofunzione?
        free(curr);
        itrSuccessor(iterator);
    }
    DestructBSTPostOrderIterator(itrType);
    itrDestruct(iterator);

    free(tree); //TODO: Controlla che non si debba liberare anche l'albero manualmente. E' stato già liberato nel while però non ne sei sicuro
}

BSTNode* itrBSTClone(BSTNode* tree) {
    BSTNode *ret = NULL, *clonedTree = NULL;
    BSTNode *curr = tree, *last = NULL;

    StackType *stktype = ConstructStackVecType();
    StackObject *stack = stkConstruct(stktype), *stackClonedTree = stkConstruct(stktype);

    DataType *ptrType = ConstructPointerDataType();
    DataObject *elem = adtConstruct(ptrType);

    while (curr != NULL || !stkEmpty(stack)) {
        if (curr != NULL) {
            adtSetValue(elem, curr);
            stkPush(stack, elem);

            clonedTree = (BSTNode*)malloc(sizeof(BSTNode));
            adtSetValue(elem, clonedTree);
            stkPush(stackClonedTree, elem);

            curr = curr->left;
            clonedTree = clonedTree->left;
            ret = NULL;
        } else {
            curr = (BSTNode*)adtGetValue(stkTop(stack));
            clonedTree = (BSTNode*)adtGetValue(stkTop(stackClonedTree));
            if (curr->right && last != (curr->right)) {
                clonedTree->left = ret;
                curr = curr->right;
                clonedTree = clonedTree->right;
            } else {
                if (curr->right == NULL) {
                    clonedTree->left = ret;
                    clonedTree->right = NULL;
                } else {
                    clonedTree->right = ret;
                }
                clonedTree->key = adtClone(curr->key);
                ret = clonedTree;
                last = curr;
                curr = NULL;
                stkPop(stack);
                stkPop(stackClonedTree);
            }
        }
    }

    DestructPointerDataType(ptrType);
    adtDestruct(elem);
    DestructStackVecType(stktype);
    stkDestruct(stack);
    stkDestruct(stackClonedTree);

    return clonedTree;
}

bool itrBSTEqual(BSTNode* firstTree, BSTNode* secondTree) {
    if (firstTree == NULL && secondTree == NULL) {
        return true;
    } else if (firstTree != NULL && secondTree != NULL) {
        ITRType *itrType = ConstructBSTPostOrderIterator();
        ITRObject *itrFirstTree = itrConstruct(itrType, firstTree);
        ITRObject *itrSecondTree = itrConstruct(itrType, secondTree);

        BSTNode* currFirstTree = (BSTNode*)itrElement(itrFirstTree);
        BSTNode* currSecondTree = (BSTNode*)itrElement(itrSecondTree);

        while (!(itrTerminated(itrFirstTree) && itrTerminated(itrSecondTree)) && (adtCompare(currFirstTree->key, currSecondTree->key) == 0) ) {
            itrSuccessor(itrFirstTree);
            currFirstTree = (BSTNode*)itrElement(itrFirstTree);

            currSecondTree = (BSTNode*)itrElement(itrSecondTree);
            itrSuccessor(itrSecondTree);
        }

        DestructBSTPostOrderIterator(itrType);
        itrDestruct(itrFirstTree);
        itrDestruct(itrSecondTree);

        return currFirstTree == NULL && currSecondTree == NULL;
    } else {
        return false;
    }
}

bool itrBSTExists(BSTNode *tree, DataObject *elem) { //TODO: Tolto clone radice...
    while (tree != NULL && adtCompare(tree->key, elem) != 0) {
        if (adtCompare(tree->key, elem) < 0) {
            tree = tree->right;
        } else if (adtCompare(tree->key, elem) > 0) {
            tree = tree->left;
        } else {
            return true;
        }
    }

    return false;
}

BSTNode* _itrCreateNode(DataObject *elem) {
    BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->key = adtClone(elem);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool itrBSTInsert(BSTNode** tree, DataObject *elem) {
    if (*tree != NULL) { //L'albero è vuoto, il nodo viene inserito come radice
        *tree = _itrCreateNode(elem);
        return true;
    } else {
        BSTNode* curr = *tree, *last = curr; //TODO: Serve last? no
        while (curr != NULL && adtCompare(curr->key, elem) != 0) {
            last = curr;
            if (adtCompare(curr->key, elem) < 0) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        if (curr == NULL) {
            if (adtCompare(last->key, elem) < 0) {
                last->right = _itrCreateNode(elem);
            } else {
                last->left = _itrCreateNode(elem);
            }
            return true;
        } else {
            return false;
        }
    }
}

DataObject* itrBSTGetMin(BSTNode* tree) {

    if(tree != NULL) {
        while (tree->left != NULL) {
            tree = tree->left;
        }
        return adtClone(tree->key);
    } else {
        return NULL;
    }
}

DataObject* itrBSTGetMax(BSTNode* tree) {

    if(tree != NULL) {
        while (tree->right != NULL) {
            tree = tree->right;
        }
        return adtClone(tree->key);
    } else {
        return NULL;
    }
}


//TODO: Rivedile perchè non sono convito che si facciano così
void itrBSTPreOrderMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    ITRType *itrType = ConstructBSTPreOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    while (!itrTerminated(iterator)) {
        tree = (BSTNode*)itrElement(iterator);
        mapFunction(tree->key, parameter);
        itrSuccessor(iterator);
    }
    DestructBSTPreOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTInOrderMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    ITRType *itrType = ConstructBSTInOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    while (!itrTerminated(iterator)) {
        tree = (BSTNode*)itrElement(iterator);
        mapFunction(tree->key, parameter);
        itrSuccessor(iterator);
    }
    DestructBSTInOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTPostOrderMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    ITRType *itrType = ConstructBSTPostOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    while (!itrTerminated(iterator)) {
        tree = (BSTNode*)itrElement(iterator);
        mapFunction(tree->key, parameter);
        itrSuccessor(iterator);
    }
    DestructBSTPostOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTBreadthMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    ITRType *itrType = ConstructBSTBreadthIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    while (!itrTerminated(iterator)) {
        tree = (BSTNode*)itrElement(iterator);
        mapFunction(tree->key, parameter);
        itrSuccessor(iterator);
    }
    DestructBSTBreadthIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTPreOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter) {
    ITRType *itrType = ConstructBSTPreOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    while (!itrTerminated(iterator)) {
        tree = (BSTNode*)itrElement(iterator);
        foldFunction(tree->key, accumulator, parameter);
        itrSuccessor(iterator);
    }
    DestructBSTPreOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTInOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter) {
    ITRType *itrType = ConstructBSTInOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    while (!itrTerminated(iterator)) {
        tree = (BSTNode*)itrElement(iterator);
        foldFunction(tree->key, accumulator, parameter);
        itrSuccessor(iterator);
    }
    DestructBSTInOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTPostOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter) {
    ITRType *itrType = ConstructBSTPostOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    while (!itrTerminated(iterator)) {
        tree = (BSTNode*)itrElement(iterator);
        foldFunction(tree->key, accumulator, parameter);
        itrSuccessor(iterator);
    }
    DestructBSTPostOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTBreadthFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter) {
    ITRType *itrType = ConstructBSTBreadthIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    while (!itrTerminated(iterator)) {
        tree = (BSTNode*)itrElement(iterator);
        foldFunction(tree->key, accumulator, parameter);
        itrSuccessor(iterator);
    }
    DestructBSTBreadthIterator(itrType);
    itrDestruct(iterator);
}

BSTType* ConstructBSTIterative() {
    BSTType* type = (BSTType*)malloc(sizeof(BSTType));

    //type->destruct = itrBSTDestruct;

    type->clone = itrBSTClone;

    type->equal = itrBSTEqual;

    type->exists = itrBSTExists;

    type->insert = itrBSTInsert;
    //type->remove = itrBSTRemove;

    type->getMin = itrBSTGetMin;
    //type->getNRemoveMin = itrBSTGetNRemoveMin;
    //type->removeMin = itrBSTRemoveMin;
    type->getMax = itrBSTGetMax;
    //type->getNRemoveMax = itrBSTGetNRemoveMax;
    //type->removeMax = itrBSTRemoveMax;

    //type->getPredecessor = itrBSTGetPrecedessor;
    //type->getNRemovePredecessor = itrBSTGetNRemovePredecessor;
    //type->removePredecessor = itrBSTRemovePredecessor;
    //type->getSuccessor = itrBSTGetSuccessor;
    //type->getNRemoveSuccessor = itrBSTGetNRemoveSuccessor;
    //type-> removeSuccessor = itrBSTRemoveSuccessor;

    type->preOrderMap = itrBSTPreOrderMap;
    type->inOrderMap = itrBSTInOrderMap;
    type->postOrderMap = itrBSTPostOrderMap;
    type->breadthMap = itrBSTBreadthMap;
    type->preOrderFold = itrBSTPreOrderFold;
    type->inOrderFold = itrBSTInOrderFold;
    type->postOrderFold = itrBSTPostOrderFold;
    type->breadthFold = itrBSTBreadthFold;

    return type;
}

void DestructBSTIterative(BSTType* type) {
    free(type);
}

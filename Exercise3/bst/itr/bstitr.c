
#include "bstitr.h"

#include "../bstitrpreord.h"
#include "../bstitrinord.h"
#include "../bstitrpostord.h"
#include "../bstitrbreadth.h"
#include "../../stack/vec/stackvec.h"
#include "../../adt/ptr/adtptr.h"

/* ************************************************************************** */

BSTNode* _itrCreateNode(DataObject* elem) {
    BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->key = adtClone(elem);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTNode *_itrBSTUnplugMin(BSTNode* tree, BSTNode* father) {
    if(tree != NULL) {
        while (tree->left != NULL) {
            father = tree;
            tree = tree->left;
        }

        if (father->left == tree) {
            father->left = tree->right;
        } else {
            father->right = tree->right;
        }
    }
    return tree;
}

BSTNode *_itrBSTDeleteRoot(BSTNode* tree) {
    if (tree != NULL) {
        BSTNode *temp = NULL;

        if (tree->left == NULL || tree->right == NULL) {
            if (tree->left == NULL) {
                temp = tree->right;
            } else {
                temp = tree->left;
            }

            adtDestruct(tree->key);
            free(tree);
            tree = temp;
        } else {
            temp = _itrBSTUnplugMin(tree->right, tree);
            tree->key = adtClone(temp->key);
            adtDestruct(temp->key);
            free(temp);
        }
    }
    return tree;
}


void itrBSTDestruct(BSTNode* tree) {
    ITRType* itrType = ConstructBSTPostOrderIterator();
    ITRObject* iterator = itrConstruct(itrType, tree);
    BSTNode* curr;

    while(!itrTerminated(iterator)) {
        curr = (BSTNode*)itrElement(iterator);
        adtDestruct(curr->key);
        free(curr);
        itrSuccessor(iterator);
    }
    DestructBSTPostOrderIterator(itrType);
    itrDestruct(iterator);
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

    return clonedTree;
}


bool itrBSTEqual(BSTNode* firstTree, BSTNode* secondTree) {
    if (firstTree == NULL && secondTree == NULL) {
        return true;
    } else if (firstTree != NULL && secondTree != NULL) {
        ITRType* itrType = ConstructBSTPostOrderIterator();

        ITRObject* itrFirstTree = itrConstruct(itrType, firstTree);
        ITRObject* itrSecondTree = itrConstruct(itrType, secondTree);

        BSTNode* currFirstTree = (BSTNode*)itrElement(itrFirstTree);
        BSTNode* currSecondTree = (BSTNode*)itrElement(itrSecondTree);

        while (!(itrTerminated(itrFirstTree) && itrTerminated(itrSecondTree)) && (adtCompare(currFirstTree->key, currSecondTree->key) == 0) ) {
            itrSuccessor(itrFirstTree);
            currFirstTree = (BSTNode*)itrElement(itrFirstTree);
            itrSuccessor(itrSecondTree);
            currSecondTree = (BSTNode*)itrElement(itrSecondTree);
        }

        itrDestruct(itrFirstTree);
        itrDestruct(itrSecondTree);

        return currFirstTree == NULL && currSecondTree == NULL;
    } else {
        return false;
    }
}


bool itrBSTExists(BSTNode* tree, DataObject* elem) {
    if(tree != NULL) {
        BSTNode *curr = tree;

        while (curr != NULL && (adtCompare(curr->key, elem) != 0)) {

            printf("Confronto ");
            adtWriteToMonitor(curr->key);
            printf(" con ");
            adtWriteToMonitor(elem);
            printf("\n");

            if (adtCompare(curr->key, elem) < 0) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return curr != NULL;
    }
    return false;
}


bool itrBSTInsert(BSTNode** tree, DataObject* elem) {
    if (*tree == NULL) { //L'albero è vuoto, il nodo viene inserito come radice
        *tree = _itrCreateNode(elem);
        return true;
    } else {
        BSTNode* curr = *tree, *last = curr;
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

bool itrBSTRemove(BSTNode** tree, DataObject* elem){
    if (tree != NULL) {
        BSTNode *curr = *tree, *last = NULL;

        while (curr && adtCompare(curr->key, elem) != 0) {
            last = curr;
            if (adtCompare(curr->key, elem) < 0) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        if (curr) {
            if (last) {
                if (curr == last->right) {
                    curr = _itrBSTDeleteRoot(curr);
                    last->right = curr;
                } else {
                    curr = _itrBSTDeleteRoot(curr);
                    last->left = curr;
                }
            } else {
                *tree = _itrBSTDeleteRoot(*tree);
            }
            return true;
        }
    }

    return false;
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

DataObject* itrBSTGetNRemoveMin(BSTNode** tree) {
    if (*tree != NULL) {
        BSTNode* curr = *tree;

        while (curr->left != NULL) {
            curr = curr->left;
        }

        DataObject* min = adtClone(curr->key);
        itrBSTRemove(&(*tree), min);
        return min;
    } else {
        return NULL;
    }
}

bool itrBSTRemoveMin(BSTNode** tree) {
    if (*tree) {
        BSTNode *curr = *tree;

        while(curr->left != NULL) {
            curr = curr->left;
        }
        itrBSTRemove(&(*tree), curr->key);
        return true;
    }
    return false;
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

DataObject* itrBSTGetNRemoveMax(BSTNode** tree) {
    if (*tree != NULL) {
        BSTNode* curr = *tree;

        while (curr->right != NULL) {
            curr = curr->right;
        }

        DataObject* max = adtClone(curr->key);

        itrBSTRemove(&(*tree), max);
        return max;
    } else {
        return NULL;
    }
}

bool itrBSTRemoveMax(BSTNode** tree) {
    if (*tree != NULL) {
        BSTNode *curr = *tree;

        while (curr->right != NULL) {
            curr = curr->right;
        }
        itrBSTRemove(&(*tree), curr->key);
        return true;
    }
    return false;
}


DataObject* itrBSTGetPrecedessor(BSTNode* tree, DataObject* elem) {
    DataObject *pred = NULL;

    if (tree != NULL) {
        BSTNode *curr = tree, *cand = NULL;

        while (curr != NULL && adtCompare(curr->key, elem) != 0) {
            if (adtCompare(curr->key, elem) < 0) {
                cand = curr;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        if (curr != NULL && curr->left != NULL) {
            curr = curr->left;

            while (curr->right != NULL) {
                curr = curr->right;
            }

            pred = adtClone(curr->key);
        } else {
            if (cand != NULL) {
                pred = adtClone(cand->key);
            }
        }
    }
    return pred;
}

DataObject* itrBSTGetNRemovePredecessor(BSTNode** tree, DataObject* elem) {
    DataObject *pred = NULL;

    if (tree != NULL) {
        BSTNode *curr = *tree, *cand = NULL;

        while (curr != NULL && adtCompare(curr->key, elem) != 0) {
            if (adtCompare(curr->key, elem) < 0) {
                cand = curr;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        if (curr != NULL && curr->left != NULL) {
            curr = curr->left;

            while (curr->right) {
                curr = curr->right;
            }

            pred = adtClone(curr->key);
            itrBSTRemove(&(*tree), curr->key);
        } else {
            if (cand) {
                pred = adtClone(cand->key);
                itrBSTRemove(&(*tree), cand->key);
            }
        }
    }
    return pred;
}

bool itrBSTRemovePredecessor(BSTNode** tree, DataObject* elem) {
    if (*tree != NULL) {
        BSTNode *curr = *tree, *cand = NULL;

        while (curr != NULL && adtCompare(curr->key, elem) != 0) {
            if (adtCompare(curr->key, elem) < 0) {
                cand = curr;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        if (curr != NULL && curr->left != NULL) {
            curr = curr->left;

            while (curr->right) {
                curr = curr->right;
            }

            itrBSTRemove(&(*tree), curr->key);
            return true;
        } else {
            if (cand != NULL) {
                itrBSTRemove(&(*tree), cand->key);
                return true;
            }
        }
    }
    return false;
}


DataObject* itrBSTGetSuccessor(BSTNode* tree, DataObject* elem) {
    DataObject *succ = NULL;

    if (tree != NULL) {
        BSTNode *curr = tree, *cand = NULL;

        while (curr != NULL && adtCompare(curr->key, elem) != 0) {
            if (adtCompare(curr->key, elem) < 0) {
                curr = curr->right;
            } else {
                cand = curr;
                curr = curr->left;
            }
        }
        if (curr != NULL && curr->right != NULL) {
            curr = curr->right;

            while (curr->left != NULL) {
                curr = curr->left;
            }

            succ = adtClone(curr->key);
        } else {
            if (cand != NULL) {
                succ = adtClone(cand->key);
            }
        }
    }
    return succ;
}

DataObject* itrBSTGetNRemoveSuccessor(BSTNode** tree, DataObject* elem) { //TODO: Ottimizza assolutamente, complessità quadratica
    DataObject *succ = NULL;

    if (tree != NULL) {
        BSTNode *curr = *tree, *cand = NULL;

        while (curr != NULL && adtCompare(curr->key, elem) != 0) {
            if (adtCompare(curr->key, elem) < 0) {
                curr = curr->right;
            } else {
                cand = curr;
                curr = curr->left;
            }
        }
        if (curr && curr->right) {
            curr = curr->right;

            while (curr->left) {
                curr = curr->left;
            }

            succ = adtClone(curr->key);
            itrBSTRemove(&(*tree), curr->key);
        } else {
            if (cand) {
                succ = adtClone(cand->key);
                itrBSTRemove(&(*tree), cand->key);
            }
        }
    }
    return succ;
}

bool itrBSTRemoveSuccessor(BSTNode** tree, DataObject* elem) {
    if (*tree != NULL) {
        BSTNode *curr = *tree, *cand = NULL;

        while (curr != NULL && adtCompare(curr->key, elem) != 0) {
            if (adtCompare(curr->key, elem) < 0) {
                curr = curr->right;
            } else {
                cand = curr;
                curr = curr->left;
            }
        }
        if (curr != NULL && curr->right != NULL) {
            curr = curr->right;
            while (curr->left != NULL) {
                curr = curr->left;
            }
            itrBSTRemove(&(*tree), curr->key);
            return true;
        } else {
            if (cand) {
                itrBSTRemove(&(*tree), cand->key);
                return true;
            }
        }
    }
    return false;
}


void itrBSTPreOrderMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    ITRType *itrType = ConstructBSTPreOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    BSTNode* curr;
    while (!itrTerminated(iterator)) {
        curr = (BSTNode*)itrElement(iterator);

        mapFunction(curr->key, parameter);
        itrSuccessor(iterator);
    }

    DestructBSTPreOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTInOrderMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    ITRType *itrType = ConstructBSTInOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    BSTNode* curr;
    while (!itrTerminated(iterator)) {
        curr = (BSTNode*)itrElement(iterator);

        mapFunction(curr->key, parameter);
        itrSuccessor(iterator);
    }

    DestructBSTInOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTPostOrderMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    ITRType *itrType = ConstructBSTPostOrderIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    BSTNode* curr;
    while (!itrTerminated(iterator)) {
        curr = (BSTNode*)itrElement(iterator);

        mapFunction(curr->key, parameter);
        itrSuccessor(iterator);
    }

    DestructBSTPostOrderIterator(itrType);
    itrDestruct(iterator);
}

void itrBSTBreadthMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    ITRType *itrType = ConstructBSTBreadthIterator();
    ITRObject *iterator = itrConstruct(itrType, tree);

    BSTNode* curr;
    while (!itrTerminated(iterator)) {
        curr = (BSTNode*)itrElement(iterator);

        mapFunction(curr->key, parameter);
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

    type->destruct = itrBSTDestruct;

    type->clone = itrBSTClone;

    type->equal = itrBSTEqual;

    type->exists = itrBSTExists;

    type->insert = itrBSTInsert;
    type->remove = itrBSTRemove;

    type->getMin = itrBSTGetMin;
    type->getNRemoveMin = itrBSTGetNRemoveMin;
    type->removeMin = itrBSTRemoveMin;

    type->getMax = itrBSTGetMax;
    type->getNRemoveMax = itrBSTGetNRemoveMax;
    type->removeMax = itrBSTRemoveMax;

    type->getPredecessor = itrBSTGetPrecedessor;
    type->getNRemovePredecessor = itrBSTGetNRemovePredecessor;
    type->removePredecessor = itrBSTRemovePredecessor;

    type->getSuccessor = itrBSTGetSuccessor;
    type->getNRemoveSuccessor = itrBSTGetNRemoveSuccessor;
    type->removeSuccessor = itrBSTRemoveSuccessor;

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

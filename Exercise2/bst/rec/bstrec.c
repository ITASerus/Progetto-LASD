
#include "bstrec.h"

/* ************************************************************************** */

//TODO: Controlla se vicino ad adtCOmpare ci va lo == 0

void recBSTDestruct(BSTNode* tree) { //TODO: Sostituire void* con BSTNode?
    if (tree == NULL) {
        return;
    }

    recBSTDestruct(tree->left);
    recBSTDestruct(tree->right);
    free (tree);
}


bool recBSTEqual(BSTNode* firstTree, BSTNode* secondTree) {
    if( firstTree == NULL || secondTree == NULL) {
        return firstTree == secondTree;
    }
    if( !adtCompare(firstTree->key, secondTree->key)) {
        return false;
    }

    return recBSTEqual(firstTree->left, firstTree->right) && recBSTEqual(firstTree->right, secondTree->right);
}

bool recBSTExists(BSTNode* tree, DataObject* elem) {
    return tree != NULL && (adtCompare(tree->key, elem) || recBSTExists(tree->left, elem) || recBSTExists(tree->right, elem));
}

void recBSTInsert(BSTNode* tree, DataObject* elem) {
    if (tree != NULL) {
        if (adtCompare(elem, tree->key) < 0) {
            printf("vado a sx\n");
            recBSTInsert(tree->left, elem);
        } else {
            printf("vado a dx\n");
            recBSTInsert(tree->right, elem);
        }
    } else {
        printf("foglia\n");
        tree = (BSTNode*)malloc(sizeof(BSTNode));
        tree->right = tree->left = NULL;
        tree->key = adtClone(elem);
    }

    /*
    if (tree == NULL) {
        printf("foglia\n");
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->right = newNode->left = NULL;
        newNode->key = adtClone(elem);
        tree = newNode;
    }

    if (adtCompare(elem, tree->key) < 0) {
        printf("vado a sx\n");
        recBSTInsert(tree->left, elem);
    } else {
        printf("vado a dx\n");
        recBSTInsert(tree->right, elem);
    }
    */
}

void recBSTPreOrderMap( BSTNode* tree, MapFun mapFunction, void* parameter) {
    if (tree == NULL) {
        return;
    }
    printf("nodo\n");
    mapFunction(tree->key, parameter);

    recBSTPreOrderMap(tree->left, mapFunction, parameter);
    recBSTPreOrderMap(tree->right, mapFunction, parameter);
    printf("nodo\n");
}

BSTType* ConstructBSTRecursive() {
    BSTType* type = (BSTType*)malloc(sizeof(BSTType));

    type->destruct = recBSTDestruct;

    //type->clone = recBSTClone;

    type->equal = recBSTEqual;

    type->exists = recBSTExists;

    type->insert = recBSTInsert;
    //type->remove = recBSTRemove;

    /*type->getMin = recBSTGetMin;
    type->getNRemoveMin = recBSTGetNRemoveMin;
    type->removeMin = recBSTRemoveMin;
    type->getMax = recBSTGetMax;
    type->getNRemoveMax = recBSTGetNRemoveMax;
    type->removeMax = recBSTRemoveMax;

    type->getPredecessor = recBSTGetPrecedessor;
    type->getNRemovePredecessor = recBSTGetNRemovePredecessor;
    type->removePredecessor = recBSTRemovePredecessor;
    type->getSuccessor = recBSTGetSuccessor;
    type->getNRemoveSuccessor = recBSTGetNRemoveSuccessor;
    type-> removeSuccessor = recBSTRemoveSuccessor;
*/
    type->preOrderMap = recBSTPreOrderMap;
    //type->inOrderMap = recBSTInOrderMap;
    //type->postOrderMap = recBSTPostOrderMap;
    //type->breadthMap = recBSTBreadthMap;
    //type->preOrderFold = recBSTPreOrderFold;
    //type->inOrderFold = recBSTInOrderFold;
    //type->postOrderFold = recBSTPostOrderFold;
    //type->breadthFold = recBSTBreadthFold;

    return type;
}

void DestructBSTRecursive(BSTType* type) {
    free(type);
}

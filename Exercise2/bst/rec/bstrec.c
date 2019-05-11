
#include "bstrec.h"

//*** FUNZIONI ***
void recBSTDestruct(BSTNode* tree);
BSTNode* recBSTClone(BSTNode* tree);
bool recBSTEqual(BSTNode* firstTree, BSTNode* secondTree);
bool recBSTExists(BSTNode* tree, DataObject* elem);
void recBSTInsert(BSTNode** tree, DataObject* elem);
BSTNode* recBSTRemove(BSTNode* tree, DataObject* elem);
DataObject* recBSTGetMin(BSTNode* tree);
BSTNode* recBSTGetNRemoveMin(BSTNode* tree, DataObject** min);
BSTNode* recBSTRemoveMin(BSTNode* tree);
DataObject* recBSTGetMax(BSTNode* tree);
BSTNode* recBSTGetNRemoveMax(BSTNode* tree, DataObject** min);
BSTNode* recBSTRemoveMax(BSTNode* tree);
//
//
//
//
//
//
void recBSTPreOrderMap(BSTNode* tree, MapFun mapFunction, void* parameter);
void recBSTInOrderMap (BSTNode* tree, MapFun mapFunction, void* parameter);
void recBSTPostOrderMap (BSTNode* tree, MapFun mapFunction, void* parameter);
//
void recBSTPreOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter);
void recBSTInOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter);
void recBSTPostOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter);
//

//*** FUNZIONI AUSILIARIE ***
void recBSTDestructNode(BSTNode* node);
BSTNode* _recBSTUnplugMin(BSTNode* tree, BSTNode* father);
BSTNode* _recBSTDeleteRoot(BSTNode* tree);


/* ************************************************************************** */

void recBSTDestruct(BSTNode* tree) {
    if (tree == NULL) {
        return;
    }

    recBSTDestruct(tree->left);
    recBSTDestruct(tree->right);
    free (tree);
}


BSTNode* recBSTClone(BSTNode* tree) {
    BSTNode* newTree = NULL;

    if(tree != NULL) {
        recBSTInsert(&newTree, tree->key);
        newTree->left = recBSTClone(tree->left);
        newTree->right = recBSTClone(tree->right);
        return newTree;
    } else {
        return NULL;
    }
}


bool recBSTEqual(BSTNode* firstTree, BSTNode* secondTree) {
    if( firstTree == NULL || secondTree == NULL) {
        return firstTree == secondTree;
    }

    if( adtCompare(firstTree->key, secondTree->key) != 0) {
        return false;
    }

    return recBSTEqual(firstTree->left, secondTree->left) && recBSTEqual(firstTree->right, secondTree->right);
}


bool recBSTExists(BSTNode* tree, DataObject* elem) {
    return tree != NULL && (adtCompare(tree->key, elem) == 0 || recBSTExists(tree->left, elem) || recBSTExists(tree->right, elem));
}


void recBSTInsert(BSTNode** tree, DataObject* elem) { //TODO: Gestisci duplicati
    if (*tree != NULL) {
        if (adtCompare(elem, (*tree)->key) < 0) {
            recBSTInsert(&(*tree)->left, elem);
        } else {
            recBSTInsert(&(*tree)->right, elem);
        }
    } else {
        *tree = (BSTNode*)malloc(sizeof(BSTNode));
        (*tree)->right = (*tree)->left = NULL;
        (*tree)->key = adtClone(elem);
    }
}

BSTNode* recBSTRemove(BSTNode* tree, DataObject* elem) {
    if(tree != NULL) {
        if(adtCompare(tree->key, elem) > 0) { //L'elemento da elminare si trova nel sottoalbero sinistro
            tree->left = recBSTRemove(tree->left, elem);
        } else if(adtCompare(tree->key, elem) < 0) { //L'elemento da eliminare si trova nel sottoalbero destro
            tree->right = recBSTRemove(tree->right, elem);
        } else if(adtCompare(tree->key, elem) == 0) { //L'elemento da eliminare è stato trovato
            tree = _recBSTDeleteRoot(tree);
        }
    }
    return tree;
}


DataObject* recBSTGetMin(BSTNode* tree) {
    if(tree->left == NULL) {
        return tree->key;
    } else {
        return recBSTGetMin(tree->left);
    }
}

BSTNode* recBSTGetNRemoveMin(BSTNode* tree, DataObject** min) {
    if (tree != NULL) {
        if (tree->left == NULL) {
            *min = tree->key;

            BSTNode *tmp = tree;
            tree = tree->right;
            free(tmp);

            return tree;
        } else {
        tree->left = recBSTGetNRemoveMin(tree->left, &(*min));
        }
    }
    return tree;
}

BSTNode* recBSTRemoveMin(BSTNode* tree) {
    if (tree != NULL) {
        if (tree->left == NULL) {
            BSTNode *tmp = tree;

            tree = tree->right;

            recBSTDestructNode(tmp);

            return tree;
        } else {
            tree->left = recBSTRemoveMin(tree->left);
        }
    }
    return tree;
}

DataObject* recBSTGetMax(BSTNode* tree) {
    if(tree->right == NULL) {
        return tree->key; //TODO: Aggiungere qua adtClone?
    } else {
        return recBSTGetMax(tree->right);
    }
}

BSTNode* recBSTGetNRemoveMax(BSTNode* tree, DataObject** min) {
    if (tree != NULL) {
        if (tree->right == NULL) {
            *min = tree->key;

            BSTNode *tmp = tree;
            tree = tree->left;
            free(tmp);

            return tree;
        } else {
            tree->right = recBSTGetNRemoveMax(tree->right, &(*min));
        }
    }
    return tree;
}

BSTNode* recBSTRemoveMax(BSTNode* tree) {
    if (tree != NULL) {
        if (tree->right == NULL) {
            BSTNode *tmp = tree;

            tree = tree->left;

            recBSTDestructNode(tmp);

            return tree;
        } else {
            tree->right = recBSTRemoveMax(tree->right);
        }
    }
    return tree;
}

void recBSTPreOrderMap(BSTNode* tree, MapFun mapFunction, void* parameter) {
    if (tree != NULL) {
        mapFunction(tree->key, parameter);
        recBSTPreOrderMap(tree->left, mapFunction, parameter);
        recBSTPreOrderMap(tree->right, mapFunction, parameter);
    }
}

void recBSTInOrderMap (BSTNode* tree, MapFun mapFunction, void* parameter) {
    if (tree != NULL) {
        recBSTInOrderMap(tree->left, mapFunction, parameter);
        mapFunction(tree->key, parameter);
        recBSTInOrderMap(tree->right, mapFunction, parameter);
    }
}

void recBSTPostOrderMap (BSTNode* tree, MapFun mapFunction, void* parameter)  {
    if (tree != NULL) {
        recBSTPostOrderMap(tree->left, mapFunction, parameter);
        recBSTPostOrderMap(tree->right, mapFunction, parameter);
        mapFunction(tree->key, parameter);
    }
}

void recBSTPreOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter) {
    if (tree != NULL) {
        foldFunction(tree->key, accumulator, parameter);
        recBSTPreOrderFold(tree->left, foldFunction, accumulator, parameter);
        recBSTPreOrderFold(tree->right, foldFunction, accumulator, parameter);
    }
}

void recBSTInOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter) {
    if (tree == NULL) {
        recBSTInOrderFold(tree->left, foldFunction, accumulator, parameter);
        foldFunction(tree->key, accumulator, parameter);
        recBSTInOrderFold(tree->right, foldFunction, accumulator, parameter);
    }
}

void recBSTPostOrderFold(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter) {
    if (tree != NULL) {
        recBSTPostOrderFold(tree->left, foldFunction, accumulator, parameter);
        recBSTPostOrderFold(tree->right, foldFunction, accumulator, parameter);
        foldFunction(tree->key, accumulator, parameter);
    }
}


BSTType* ConstructBSTRecursive() {
    BSTType* type = (BSTType*)malloc(sizeof(BSTType));

    type->destruct = recBSTDestruct;

    type->clone = recBSTClone;

    type->equal = recBSTEqual;

    type->exists = recBSTExists;

    type->insert = recBSTInsert;
    type->remove = recBSTRemove;

    type->getMin = recBSTGetMin;
    type->getNRemoveMin = recBSTGetNRemoveMin;
    type->removeMin = recBSTRemoveMin;
    type->getMax = recBSTGetMax;
    type->getNRemoveMax = recBSTGetNRemoveMax;
    type->removeMax = recBSTRemoveMax;

    //type->getPredecessor = recBSTGetPrecedessor;
    //type->getNRemovePredecessor = recBSTGetNRemovePredecessor;
    //type->removePredecessor = recBSTRemovePredecessor;
    //type->getSuccessor = recBSTGetSuccessor;
    //type->getNRemoveSuccessor = recBSTGetNRemoveSuccessor;
    //type-> removeSuccessor = recBSTRemoveSuccessor;

    type->preOrderMap = recBSTPreOrderMap;
    type->inOrderMap = recBSTInOrderMap;
    type->postOrderMap = recBSTPostOrderMap;
    //type->breadthMap = recBSTBreadthMap;
    type->preOrderFold = recBSTPreOrderFold;
    type->inOrderFold = recBSTInOrderFold;
    type->postOrderFold = recBSTPostOrderFold;
    //type->breadthFold = recBSTBreadthFold;

    return type;
}

void DestructBSTRecursive(BSTType* type) {
    free(type);
}

//*** FUNZIONI AUSILIARIE ***
void recBSTDestructNode(BSTNode* node) {
    adtDestruct(node->key);
    free(node);
}

BSTNode* _recBSTUnplugMin(BSTNode* tree, BSTNode* father) {
    if(tree != NULL) {
        if (tree->left != NULL){
            return _recBSTUnplugMin(tree, tree->left);
        } else {
            if(father->left == tree) {
                father->left = tree->right;
            } else {
                father->right = tree->right;
            }
        }
    }
    return tree;
}

BSTNode* _recBSTDeleteRoot(BSTNode* tree) {
    if(tree != NULL) {
        BSTNode* tmp = NULL;

        if(tree->left == NULL) { //Il nodo da eliminare ha solo il figlio destro o è una foglia
            tmp = tree;
            tree = tree->right;
        } else if(tree->right == NULL) { //Il nodo da eliminare ha solo il figlio sinistro
            tmp = tree;
            tree = tree->left;
        } else {
            tmp = _recBSTUnplugMin(tree, tree->right); //Il nodo da eliminare ha figlio sinistro e destro
            DataObject* scambio = tmp->key;
            tmp->key = tree->key;
            tree->key = scambio;
        }
        recBSTDestructNode(tmp); //Dealloco la vecchia radice
    }
    return tree; //Ritorno la nuova radice
}
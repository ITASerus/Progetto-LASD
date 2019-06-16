/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef BST_H
#define BST_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

/* ************************************************************************** */

typedef struct BSTNode BSTNode;
struct BSTNode {
    DataObject* key;

    BSTNode* left;
    BSTNode* right;
};

/* ************************************************************************** */

typedef void (*BSTDestruct)(BSTNode* tree);

typedef BSTNode* (*BSTClone)(BSTNode* tree);

typedef bool (*BSTEqual)(BSTNode* firstTree, BSTNode* secondTree);

typedef bool (*BSTExists)(BSTNode* tree, DataObject* elem);

typedef bool (*BSTInsert)(BSTNode** tree, DataObject* elem);
typedef bool (*BSTRemove)(BSTNode** tree, DataObject* elem);

typedef DataObject* (*BSTGetMin)(BSTNode* tree);
typedef DataObject* (*BSTGetNRemoveMin)(BSTNode** tree);
typedef bool (*BSTRemoveMin)(BSTNode** tree);
typedef DataObject* (*BSTGetMax)(BSTNode* tree);
typedef DataObject* (*BSTGetNRemoveMax)(BSTNode** tree);
typedef bool (*BSTRemoveMax)(BSTNode** tree);

typedef DataObject* (*BSTGetPredecessor)(BSTNode* tree, DataObject* elem);
typedef DataObject* (*BSTGetNRemovePredecessor)(BSTNode** tree, DataObject* elem);
typedef bool (*BSTRemovePredecessor)(BSTNode** tree, DataObject* elem);
typedef DataObject* (*BSTGetSuccessor)(BSTNode* tree, DataObject* elem);
typedef DataObject* (*BSTGetNRemoveSuccessor)(BSTNode** tree, DataObject* elem);
typedef bool (*BSTRemoveSuccessor)(BSTNode** tree, DataObject* elem);

typedef void (*BSTPreOrderMap)(BSTNode* tree, MapFun mapFunction, void* parameter);
typedef void (*BSTInOrderMap)(BSTNode* tree, MapFun mapFunction, void* parameter);
typedef void (*BSTPostOrderMap)(BSTNode* tree, MapFun mapFunction, void* parameter);
typedef void (*BSTBreadthMap)(BSTNode* tree, MapFun mapFunction, void* parameter);
typedef void (*BSTPreOrderFold)(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter);
typedef void (*BSTInOrderFold)(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter);
typedef void (*BSTPostOrderFold)(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter);
typedef void (*BSTBreadthFold)(BSTNode* tree, FoldFun foldFunction, void* accumulator, void* parameter);

/* ************************************************************************** */

typedef struct BSTType {
    BSTDestruct destruct;

    BSTClone clone;

    BSTEqual equal;

    BSTExists exists;

    BSTInsert insert;
    BSTRemove remove;

    BSTGetMin getMin;
    BSTGetNRemoveMin getNRemoveMin;
    BSTRemoveMin removeMin;
    BSTGetMax getMax;
    BSTGetNRemoveMax getNRemoveMax;
    BSTRemoveMax removeMax;

    BSTGetPredecessor getPredecessor;
    BSTGetNRemovePredecessor getNRemovePredecessor;
    BSTRemovePredecessor removePredecessor;
    BSTGetSuccessor getSuccessor;
    BSTGetNRemoveSuccessor getNRemoveSuccessor;
    BSTRemoveSuccessor removeSuccessor;

    BSTPreOrderMap preOrderMap;
    BSTInOrderMap inOrderMap;
    BSTPostOrderMap postOrderMap;
    BSTBreadthMap breadthMap;
    BSTPreOrderFold preOrderFold;
    BSTInOrderFold inOrderFold;
    BSTPostOrderFold postOrderFold;
    BSTBreadthFold breadthFold;
} BSTType;

typedef struct BSTObject {
    BSTType* type;
    BSTNode* root;
    int numberOfNodes;
} BSTObject;

/* ************************************************************************** */

BSTObject* bstConstruct(BSTType* bstType);
void bstDestruct(BSTObject* tree);

bool bstEmpty(BSTObject* tree);

int bstSize(BSTObject* tree);

void bstClear(BSTObject* tree);

BSTObject* bstClone(BSTObject* tree);

bool bstEqual(BSTObject* firstTree, BSTObject* secondTree);

bool bstExists(BSTObject* tree, DataObject* keyToFind);

void bstInsert(BSTObject* tree, DataObject* newKey);
void bstRemove(BSTObject* tree, DataObject* keyToRemove);

DataObject* bstGetMin(BSTObject* tree);
DataObject* bstGetNRemoveMin(BSTObject* tree);
void bstRemoveMin(BSTObject* tree);
DataObject* bstGetMax(BSTObject* tree);
DataObject* bstGetNRemoveMax(BSTObject* tree);
void bstRemoveMax(BSTObject* tree);

DataObject* bstGetPredecessor(BSTObject* tree, DataObject* key);
DataObject* bstGetNRemovePredecessor(BSTObject* tree, DataObject* key);
void bstRemovePredecessor(BSTObject* tree, DataObject* key);
DataObject* bstGetSuccessor(BSTObject* tree, DataObject* key);
DataObject* bstGetNRemoveSuccessor(BSTObject* tree, DataObject* key);
void bstRemoveSuccessor(BSTObject* tree, DataObject* key);

void bstPreOrderMap(BSTObject* tree, MapFun mapFunction, void* param);
void bstInOrderMap(BSTObject* tree, MapFun mapFunction, void* param);
void bstPostOrderMap(BSTObject* tree, MapFun mapFunction, void* param);
void bstBreadthMap(BSTObject* tree, MapFun mapFunction, void* param);
void bstPreOrderFold(BSTObject* tree, FoldFun foldFunction, void* accumulator, void* param);
void bstInOrderFold(BSTObject* tree, FoldFun foldFunction, void* accumulator, void* param);
void bstPostOrderFold(BSTObject* tree, FoldFun foldFunction, void* accumulator, void* param);
void bstBreadthFold(BSTObject* tree, FoldFun foldFunction, void* accumulator, void* param);

/* ************************************************************************** */

#endif

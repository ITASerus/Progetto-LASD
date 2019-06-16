/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef BSTITRINORD_H
#define BSTITRINORD_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../stack/stack.h"

#include "bst.h"

/* ************************************************************************** */

typedef struct BSTInOrderIterator {
    StackObject* stack;
    BSTNode* element;
} BSTInOrderIterator;

/* ************************************************************************** */

ITRType* ConstructBSTInOrderIterator();
void DestructBSTInOrderIterator(ITRType* typ);

/* ************************************************************************** */

#endif

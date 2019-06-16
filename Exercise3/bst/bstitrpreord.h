/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef BSTITRPREORD_H
#define BSTITRPREORD_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../stack/stack.h"

#include "bst.h"

/* ************************************************************************** */

typedef struct BSTPreOrderIterator {
    StackObject* stack;
    BSTNode* element;
} BSTPreOrderIterator;

/* ************************************************************************** */

ITRType* ConstructBSTPreOrderIterator();
void DestructBSTPreOrderIterator(ITRType* type);

/* ************************************************************************** */

#endif

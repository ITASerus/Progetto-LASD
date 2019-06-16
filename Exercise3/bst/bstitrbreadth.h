/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef BSTITRBREADTH_H
#define BSTITRBREADTH_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../queue/queue.h"

#include "bst.h"

/* ************************************************************************** */

typedef struct BSTBreadthIterator {
    QueueObject* queue;
    BSTNode* element;
} BSTBreadthIterator;

/* ************************************************************************** */

ITRType* ConstructBSTBreadthIterator();
void DestructBSTBreadthIterator(ITRType* type);

/* ************************************************************************** */

#endif


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

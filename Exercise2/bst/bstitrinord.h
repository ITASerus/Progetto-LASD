
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


#ifndef BSTITRPOSTORD_H
#define BSTITRPOSTORD_H

/* ************************************************************************** */

#include "../itr/itr.h"

#include "../stack/stack.h"

#include "bst.h"

/* ************************************************************************** */

typedef struct BSTPostOrderIterator {
    StackObject* stack;
    BSTNode* element;
} BSTPostOrderIterator;

/* ************************************************************************** */

ITRType* ConstructBSTPostOrderIterator();
void DestructBSTPostOrderIterator(ITRType* type);

/* ************************************************************************** */

#endif

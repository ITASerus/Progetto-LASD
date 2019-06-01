
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

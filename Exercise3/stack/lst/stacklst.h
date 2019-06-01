
#ifndef STACKLST_H
#define STACKLST_H

/* ************************************************************************** */

#include "../stack.h"

/* ************************************************************************** */

typedef struct StackLst StackLst;
struct StackLst
{
    DataObject* element;
    StackLst* next;
};

/* ************************************************************************** */

StackType* ConstructStackLstType();
void DestructStackLstType(StackType* stackType);

/* ************************************************************************** */

#endif

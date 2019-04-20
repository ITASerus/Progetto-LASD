
#ifndef STACK_H
#define STACK_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

/* ************************************************************************** */

typedef struct StackObject
{
  DataObject** elements;
  uint index;
  uint size;
} StackObject;

/* ************************************************************************** */

StackObject* stkConstruct();
void stkDestruct(StackObject* stack);

bool stkEmpty(StackObject* stack);
DataObject* stkTop(StackObject* stack);
void stkPop(StackObject* stack);
DataObject* stkTopNPop(StackObject* stack);
void stkPush(StackObject* top, DataObject* elem);
int stkSize(StackObject* stack);

StackObject* stkClone(StackObject* stack);
bool stkEqual(StackObject* stack1, StackObject* stack2);
bool stkExists(StackObject* stack, DataObject* object);
void stkMap(StackObject* stack, MapFun function, void* param);
void stkFold(StackObject* stack, FoldFun function, void* accumulator, void* param);

/* ************************************************************************** */

#endif

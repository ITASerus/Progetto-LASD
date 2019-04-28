
#ifndef STACK_H
#define STACK_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

/* ************************************************************************** */

typedef void* (*StkConstruct)(void*);
typedef void (*StkDestruct)(void*);

typedef bool (*StkEmpty)(void*);
typedef void* (*StkTop)(void*);
typedef void (*StkPop)(void*);
typedef void* (*StkTopNPop)(void*);
typedef void (*StkPush)(void*, void*);
typedef void (*StkClear)(void*);

typedef void* (*StkClone)(void*);
typedef bool (*StkEqual)(void*, void*);
typedef void (*StkMap)(void*, MapFun, void* );
typedef void (*StkFold)(void*, FoldFun, void*, void*);

/* ************************************************************************** */

typedef struct StackType
{
    StkConstruct construct;
    StkDestruct destruct;

    StkEmpty isEmpty;
    StkTop top;
    StkPop pop;
    StkTopNPop topNPop;
    StkPush push;
    StkClear clear;

    StkClone clone;
    StkEqual equal;
    StkMap map;
    StkFold fold;
} StackType;

typedef struct StackObject
{
  StackType* type;
  void* stack;
  int numberOfElements;
} StackObject;

/* ************************************************************************** */

StackObject* stkConstruct(StackType* type);
void stkDestruct(StackObject* stack);

bool stkEmpty(StackObject* stack);
void* stkTop(StackObject* stack);
void stkPop(StackObject* stack);
void* stkTopNPop(StackObject* stack);
void stkPush(StackObject* stack, DataObject* object);
void stkClear(StackObject* stack);

StackObject* stkClone(StackObject* stack);
bool stkEqual(StackObject* firstStack, StackObject* secondStack);
void stkMap(StackObject* stack, MapFun mapFunction, void* param);
void stkFold(StackObject* stack, FoldFun foldFunction, void* accumulator, void* param);

int stkSize(StackObject* stack);
bool stkExists(StackObject* stack, DataObject* object);

/* ************************************************************************** */

#endif

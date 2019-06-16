/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "stack.h"

void existElem(DataObject* objectToCompare, void * val, void * elem) {
    if(adtCompare(objectToCompare, elem) == 0) {
        *(bool*)val = true;
    }
}

/* ************************************************************************** */

StackObject* stkConstruct(StackType* type) {
    StackObject* object = (StackObject*)malloc(sizeof(StackObject));

    object->type = type;
    object->stack = object->type->construct(type);
    object->numberOfElements = 0;

    return object;
}

void stkDestruct(StackObject* stack) {
    stack->type->destruct(stack->stack);
    free(stack);
}


bool stkEmpty(StackObject* stack) {
    return stack->type->isEmpty(stack->stack);
}

void* stkTop(StackObject* stack) {
    return stack->type->top(stack->stack);
}

void stkPop(StackObject* stack) {
    if( stack->numberOfElements > 0) {
        stack->type->pop(stack->stack);
        stack->numberOfElements--;
    }
}

void* stkTopNPop(StackObject* stack) {
    if( stack->numberOfElements > 0) {
        stack->numberOfElements--;
        return stack->type->topNPop(stack->stack);
    } else {
        return NULL;
    }
}

void stkPush(StackObject* stack, DataObject* object) {
    stack->type->push(stack->stack, object);
    stack->numberOfElements++;
}

void stkClear(StackObject* stack) {
    stack->type->clear(stack->stack);
    stack->numberOfElements = 0;
}


StackObject* stkClone(StackObject* stack) {
    StackObject* clonedStack = (StackObject*)malloc(sizeof(StackObject));

    clonedStack->type = stack->type;
    clonedStack->stack = stack->type->clone(stack->stack);
    clonedStack->numberOfElements = stack->numberOfElements;

    return clonedStack;
}

bool stkEqual(StackObject* firstStack, StackObject* secondStack) {
    if(firstStack->type == secondStack->type) {
        return firstStack->type->equal(firstStack->stack, secondStack->stack);
    } else {
        return false;
    }
}

void stkMap(StackObject* stack, MapFun mapFunction, void* param) {
    stack->type->map(stack->stack, mapFunction, param);
}

void stkFold(StackObject* stack, FoldFun foldFunction, void* accumulator, void* param) {
    stack->type->fold(stack->stack, foldFunction, accumulator, param);
}


int stkSize(StackObject* stack) {
    return stack->numberOfElements;
}

bool stkExists(StackObject* stack, DataObject* object) {
    bool* result = (bool*)malloc(sizeof(bool));
    *result = false;
    stkFold(stack, existElem, result, object);
    return *result;
}
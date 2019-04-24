
#include "stack.h"

void sizeIncrement(DataObject* dat, void * val, void * _) { //TODO: Rivedi
    *(int*)val = *(int*)val +1;
} //TODO: Non si fa con la fold

void existElem(DataObject* objectToCompare, void * val, void * elem) { //TODO: Rivedi
    if(adtCompare(objectToCompare, elem) == 0) {
        *(bool*)val = true;
    }
}

/* ************************************************************************** */

StackObject* stkConstruct(StackType* type) {
    StackObject* object = (StackObject*)malloc(sizeof(StackObject));

    object->type = type;
    object->stack = object->type->construct(type);

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
    stack->type->pop(stack->stack);
}

void* stkTopNPop(StackObject* stack) {
    return stack->type->topNPop(stack->stack);
}

void stkPush(StackObject* stack, DataObject* object) {
    stack->type->push(stack->stack, object);
}

void stkClear(StackObject* stack) {
    stack->type->clear(stack->stack);
}


StackObject* stkClone(StackObject* stack) {
    StackObject* clonedStack = (StackObject*)malloc(sizeof(StackObject));

    clonedStack->type = stack->type;
    clonedStack->stack = stack->type->clone(stack->stack);

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


int stkSize(StackObject* stack) { //TODO: Memory leak
    int* size = (int*)malloc(sizeof(int));
    *size = 0;
    stkFold(stack, sizeIncrement, size, NULL);
    return *size;
}

bool stkExists(StackObject* stack, DataObject* object) {
    bool* result = (bool*)malloc(sizeof(bool));
    *result = false;
    stkFold(stack, existElem, result, object);
    return result;
}
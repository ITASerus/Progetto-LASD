
#include "stack.h"

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
    return stack->type->topNPop(stack);
}

void stkPush(StackObject* stack, DataObject* object) {
    stack->type->push(stack->stack, object);
}

void stkClear(StackObject* stack) {
    stack->type->clear(stack->stack);
}


StackObject* stkClone(StackObject* stack) {
    return stack->type->clone(stack->stack);
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
    int size = (int*)malloc(sizeof(int));
    size = 10;
    //stkFold(stack, , &size, NULL);
    return size;
}

bool stkExists(StackObject* stack, DataObject* object) {
    //TODO: Sfrutta funzione fold
    return false;
}
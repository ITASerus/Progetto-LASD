
#ifndef STACK_H
#define STACK_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

typedef struct StackObject {
    char** elements; //Array di stringhe
    uint index; //Posizione dell'ultimo elemento inserito nell'array
    uint size; //Dimensione dell'array, comprese le locazioni non utilizzate
} StackObject;

/* ************************************************************************** */

StackObject* stkConstruct();
void stkDestruct(StackObject* stack);

// type stkEmpty(arguments);
char* stkTop(StackObject* stack);
void stkPop(StackObject* stack);
char* stkTopNPop(StackObject* stack);
void stkPush(StackObject* top, char* elem);
int stkSize(StackObject* stack);

StackObject* stkClone(StackObject* stack);
bool stkEqual(StackObject* stack1, StackObject* stack2);
bool stkExists(StackObject* stack, char* value);
void stkMap(StackObject* stack, void* function, void* param);
// type stkFold(arguments);

/* ************************************************************************** */

void printInfoStack(StackObject* stack);
void printStack(StackObject * stack);
char* rndStr(int numChar);

#endif

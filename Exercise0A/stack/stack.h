
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
// type stkTop(arguments);
// type stkPop(arguments);
char* stkTopNPop(StackObject* stack);
void stkPush(StackObject* top, char* elem);
int stkSize(StackObject* stack);

// type stkClone(arguments);
// type stkEqual(arguments);
// type stkExists(arguments);
// type stkMap(arguments);
// type stkFold(arguments);

/* ************************************************************************** */

void printInfoStack(StackObject* stack);
void printStack(StackObject * stack);
char* rndStr(int numChar);

#endif

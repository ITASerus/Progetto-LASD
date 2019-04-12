
#ifndef STACK_H
#define STACK_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

typedef struct StackObject {
    char** elements; //Array di stringhe
    uint index; //Posizione dell'ultimo elemento inserito nell'array
    uint size; //Dimensione dell'array, comprese le locazioni non utilizzate TODO: Cambiare size in altro (dimension?) perchè nelle librerie reali con size indicano il num di elementi presenti
} StackObject;

/* ************************************************************************** */

StackObject* stkConstruct();
void stkDestruct(StackObject* stack);

bool stkEmpty(StackObject* stack);
char* stkTop(StackObject* stack);
void stkPop(StackObject* stack);
char* stkTopNPop(StackObject* stack);
void stkPush(StackObject* top, char* elem);
int stkSize(StackObject* stack);

StackObject* stkClone(StackObject* stack);
bool stkEqual(StackObject* stack1, StackObject* stack2);
bool stkExists(StackObject* stack, char* value);
void stkMap(StackObject* stack, MapFun function, void* param);
void stkFold(StackObject* stack, FoldFun function, void* accumulator, void* param);

/* ************************************************************************** */
void turnToChar(void * elm, void* character);
void strConcat(void* elm, void* accumulator, void* param);

#endif

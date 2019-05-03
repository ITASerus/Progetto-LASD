
#ifndef STACKVEC_H
#define STACKVEC_H

/* ************************************************************************** */

#include "../stack.h"

/* ************************************************************************** */

typedef struct StackVec
{
    DataObject** elements; //Array di DataObject
    uint index; //Testa dello stack
    uint size; //Dimensione dello stack, comprese le locazioni non utilizzate
} StackVec;

/* ************************************************************************** */

StackType* ConstructStackVecType();
void DestructStackVecType(StackType* stackType);

/* ************************************************************************** */

#endif

/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

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

/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef STACKLST_H
#define STACKLST_H

/* ************************************************************************** */

#include "../stack.h"

/* ************************************************************************** */

typedef struct StackLst StackLst;
struct StackLst
{
    DataObject* element;
    StackLst* next;
};

/* ************************************************************************** */

StackType* ConstructStackLstType();
void DestructStackLstType(StackType* stackType);

/* ************************************************************************** */

#endif

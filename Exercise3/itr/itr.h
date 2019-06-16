/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef ITR_H
#define ITR_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

typedef void* (*ITRConstruct)(void*, void*);
typedef void (*ITRDestruct)(void*);

typedef bool (*ITRTerminated)(void*);

typedef void* (*ITRElement)(void*);

typedef void (*ITRSuccessor)(void*);

/* ************************************************************************** */

typedef struct ITRType {
    ITRConstruct construct;
    ITRDestruct destruct;

    ITRTerminated terminated;

    ITRElement getElement;

    ITRSuccessor successor;
} ITRType;

typedef struct ITRObject {
    ITRType* type;
    void* iterator;
} ITRObject;

/* ************************************************************************** */

ITRObject* itrConstruct(ITRType* type, void* source);
void itrDestruct(ITRObject* iterator);

bool itrTerminated(ITRObject* iterator);

void* itrElement(ITRObject* iterator);

void itrSuccessor(ITRObject* iterator);

/* ************************************************************************** */

#endif

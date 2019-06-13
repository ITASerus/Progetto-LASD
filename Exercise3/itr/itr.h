
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

/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef ADT_H
#define ADT_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

typedef void* (*ADTConstruct)();
typedef void (*ADTDestruct)(void* value);

typedef void* (*ADTGetValue)(void* value);
typedef void (*ADTSetValue)(void** value, void* newValue);

typedef void* (*ADTRandomValue)();
typedef void* (*ADTReadFromKeyboard)();
typedef void (*ADTWriteToMonitor)(void* value);

typedef void* (*ADTClone)(void* value);
typedef int (*ADTCompare)(void* firstValue, void* seconValue);

/* ************************************************************************** */

typedef struct DataType {
    ADTConstruct  construct;
    ADTDestruct destruct;

    ADTGetValue getValue;
    ADTSetValue setValue;

    ADTRandomValue randomValue;
    ADTReadFromKeyboard readFromKeyboard;
    ADTWriteToMonitor writeToMonitor;

    ADTClone clone;
    ADTCompare compare;
} DataType;

typedef struct DataObject {
    DataType* type;
    void* value;
} DataObject;

/* ************************************************************************** */

DataObject* adtConstruct(DataType* dataType);
void adtDestruct(DataObject* object);

void* adtGetValue(DataObject* object);
void adtSetValue(DataObject* object, void* elem);

void adtRandomValue(DataObject* object);
void adtReadFromKeyboard(DataObject* object);
void adtWriteToMonitor(DataObject* object);

DataObject* adtClone(DataObject* object);
int adtCompare(DataObject* firstObject, DataObject* secondObject);

/* ************************************************************************** */

typedef void (*MapFun)(DataObject *, void *);
typedef void (*FoldFun)(DataObject *, void *, void *);

#endif


#ifndef ADT_H
#define ADT_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

typedef void* (*ADTConstruct)();
typedef void (*ADTDestruct)(void*);

typedef void* (*ADTGetValue)(void*);
typedef void (*ADTSetValue)(void*, void*);

typedef void* (*ADTRandomValue)();
typedef void* (*ADTReadFromKeyboard)();
typedef void (*ADTWriteToMonitor)(void*);

typedef void* (*ADTClone)(void*); // ??
typedef int (*ADTCompare)(void*, void*);

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

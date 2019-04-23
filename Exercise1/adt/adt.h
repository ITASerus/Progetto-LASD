
#ifndef ADT_H
#define ADT_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

// typedef type (*ADTConstruct)(arguments);
// typedef type (*ADTDestruct)(arguments);

// typedef type (*ADTGetValue)(arguments);
// typedef type (*ADTSetValue)(arguments);

// typedef type (*ADTRandomValue)(arguments);
// typedef type (*ADTReadFromKeyboard)(arguments);
// typedef type (*ADTWriteToMonitor)(arguments);

// typedef type (*ADTClone)(arguments);
// typedef type (*ADTCompare)(arguments);

/* ************************************************************************** */

typedef struct DataType
{
  // Struct da completare!
} DataType;

typedef struct DataObject
{
  // Struct da completare!
} DataObject;

/* ************************************************************************** */

// type adtConstruct(arguments);
// type adtDestruct(arguments);

// type adtGetValue(arguments);
// type adtSetValue(arguments);

// type adtRandomValue(arguments);
// type adtReadFromKeyboard(arguments);
// type adtWriteToMonitor(arguments);

// type adtClone(arguments);
// type adtCompare(arguments);

/* ************************************************************************** */

typedef void (*MapFun)(DataObject *, void *);
typedef void (*FoldFun)(DataObject *, void *, void *);

#endif

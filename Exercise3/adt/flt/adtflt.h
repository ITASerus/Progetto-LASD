
#ifndef ADTFLT_H
#define ADTFLT_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

#define MaxFltAbsRndVal 250
#define MaxFltPrcRndVal 1000

/* ************************************************************************** */

DataType* ConstructFloatDataType();
void DestructFloatDataType(DataType* type);

/* ************************************************************************** */

#endif


#ifndef ADTREC_H
#define ADTREC_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

typedef struct Record {
    char* name;
    char* surname;
} Record;

DataType* ConstructRecordDataType();
void DestructRecordDataType(DataType* type);

/* ************************************************************************** */

#endif

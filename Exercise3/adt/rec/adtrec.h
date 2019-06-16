/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef ADTREC_H
#define ADTREC_H

/* ************************************************************************** */

#include "../adt.h"

/* ************************************************************************** */

#define MaxStrLen 25

/* ************************************************************************** */

typedef struct Record {
    char* name;
    char* surname;
} Record;

DataType* ConstructRecordDataType();
void DestructRecordDataType(DataType* type);

/* ************************************************************************** */

#endif

/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "adtptr.h"

/* ************************************************************************** */

void* adtConstructPtr() {
    void* ptr = NULL;
    return ptr;
}

void adtDestructPtr(void* value) {
    //Niente, non si può deallocare un puntatore
}

void* adtGetValuePtr(void* value) {
    return value;
}

void adtSetValuePtr(void** oldValue, void* newValue) {
    *oldValue = newValue;
}

void* adtClonePtr(void* value) {
    return value;
}

DataType* ConstructPointerDataType() {
    DataType* type = (DataType*) malloc(sizeof(DataType));

    type->construct = adtConstructPtr;
    type->destruct = adtDestructPtr;
    type->getValue = adtGetValuePtr;
    type->setValue = adtSetValuePtr;
    type->randomValue = NULL;
    type->readFromKeyboard = NULL;
    type->writeToMonitor = NULL;
    type->clone = adtClonePtr;
    type->compare = NULL;

    return type;
}

void DestructPointerDataType(DataType* type) {
    free(type);
}
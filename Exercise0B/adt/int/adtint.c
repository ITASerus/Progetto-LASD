
#include "adtint.h"

/* ************************************************************************** */ //TODO: Assicurati che non ci stanno riferimenti a "obj->" in quanto questa è la libreria degli interi, deve funzionare con gli interi e non deve esserci necessità di passare per forza un DataObject!

void* intConstruct() {
    int* value = (int*)malloc(sizeof(int));
    return value;
}

void intDestruct(void* value) {
    free(value);
}

void* intGetValue(void* value) { //TODO: Usa intClone - COPIA DI INTCLONE?
    int* valueCopy = (int*)malloc(sizeof(int));
    *valueCopy = *(int*) value;
    return valueCopy;
}

void intSetValue(void* value, void* newValue) {
    *(int*)value = *(int*)newValue;
}

void* intRandomValue() { //TODO: Rivedi struttura
    int* rndValue = (int*)malloc(sizeof(int));
    *rndValue = rndNum(-MaxIntAbsRndVal, MaxIntAbsRndVal);
    return rndValue;
}

void* intReadFromKeyboard() { //TODO: Rivedi struttura, non suare scanf
    int* value = (int*)malloc(sizeof(int));
    scanf("%d", value);
    return value;
}

void intWriteToMonitor(void* value) {
    printf("%d", *(int*)value);
}

bool intCompare(void* firstValue, void* secondValue) { //TODO: Distingui casi 1, -1, 0
    return *(int*)firstValue == *(int*)secondValue;
}

void* intClone(void* value) { //TODO: COPIA DI INTGETVALUE?
    int* clonedValue = (int*)malloc(sizeof(int)); //TODO: Usa intConstruct?
    *clonedValue = *(int*)value;
    return clonedValue;
}

DataType* ConstructIntDataType() {
    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construct = intConstruct;
    type->destruct = intDestruct;

    type->getValue = intGetValue;
    type->setValue = intSetValue;

    type->randomValue = intRandomValue;
    type->readFromKeyboard = intReadFromKeyboard;
    type->writeToMonitor = intWriteToMonitor;

    type->clone = intClone;
    type->compare = intCompare;

    return type;
}

void DestructIntDataType(DataType* type) { //TODO: Vuole questo?
    free(type);
}
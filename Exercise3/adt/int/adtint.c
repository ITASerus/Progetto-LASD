
#include "adtint.h"

/* ************************************************************************** */

void* intConstruct() {
    return (int*)malloc(sizeof(int));
}

void intDestruct(void* value) {
    free(value);
}

void* intGetValue(void* value) {
    int* valueCopy = (int*)malloc(sizeof(int));
    *valueCopy = *(int*) value;
    return valueCopy;
}

void intSetValue(void** value, void* newValue) {
    *((int*) *value)  = *(int*)newValue;
}

void* intRandomValue() {
    int* rndValue = (int*)malloc(sizeof(int));
    *rndValue = rndNum(-MaxIntAbsRndVal, MaxIntAbsRndVal);
    return rndValue;
}

void* intReadFromKeyboard() {
    int* value = (int*)malloc(sizeof(int));

    char* buffer = (char*)malloc(sizeof(char) * 25);
    getStr(buffer, 25);
    *value = strtol(buffer, NULL, 10);

    return value;
}

void intWriteToMonitor(void* value) {
    printf("%d", *(int*)value);
}

int intCompare(void* firstValue, void* secondValue) {
    if(*(int*)firstValue < *(int*)secondValue) {
        return -1;
    } else if (*(int*)firstValue > *(int*)secondValue) {
        return 1;
    } else {
        return 0;
    }
}

void* intClone(void* value) {
    int* clonedValue = (int*)malloc(sizeof(int));
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

void DestructIntDataType(DataType* type) {
    free(type);
}
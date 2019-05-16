
#include "adtptr.h"

void* ptrConstruct() {
    void* pointer = NULL;
    return pointer;
}

void ptrDestruct(void* value) {
   //NIENTE
}

void* ptrGetValue(void* value) {
    return value;
}

void ptrSetValue(void** value, void* newValue) {
    *value = newValue;
}

void* ptrClone(void* value) {
    return value;
}

DataType* ConstructPointerDataType() {
    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construct = ptrConstruct;
    type->destruct = ptrDestruct;

    type->getValue = ptrGetValue;
    //type->setValue = ptrSetValue;

    type->randomValue = NULL;
    type->readFromKeyboard = NULL;
    type->writeToMonitor = NULL;

    type->clone = ptrClone;
    type->compare = NULL;

    return type;
}

void DestructPointerDataType(DataType* type) {
    free(type);
}
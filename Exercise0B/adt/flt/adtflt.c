
#include "adtflt.h"

/* ************************************************************************** */

void* floatConstruct() {
    float* value = (float*)malloc(sizeof(float));
    return value;
}

void floatDestruct(void* value) {
    free(value);
}

void* floatGetValue(void* value) { //TODO: Usa floatClone
    float* valueCopy = (float*)malloc(sizeof(float));
    *valueCopy = *(float*) value;
    return valueCopy;
}

void floatSetValue(void* value, void* newValue) {
    *(float*)value = *(float*)newValue;
}

void* floatRandomValue() { //TODO: Rivedi struttura
    float* rndValue = (float*)malloc(sizeof(float));
    *rndValue = ((float)rndNum(-MaxFltAbsRndVal, MaxFltAbsRndVal)/(float)(MaxFltPrcRndVal)) * MaxFltAbsRndVal; //TODO: Si genera così? NO, trova altro modo
    return rndValue;
}

void* floatReadFromKeyboard() { //TODO: Rivedi struttura, non suare scanf
    float* value = (float*)malloc(sizeof(float));
    scanf("%f", value);
    return value;
}

void floatWriteToMonitor(void* value) {
    printf("%f", *(float*)value);
}

bool floatCompare(void* firstValue, void* secondValue) { //TODO: Distingui casi 1, -1, 0, NON SI COMPARANO COSì DUE FLOAT!
    return *(float*)firstValue == *(float*)secondValue;
}

void* floatClone(void* value) {
    float* clonedValue = (float*)malloc(sizeof(float));
    *clonedValue = *(float*)value;
    return clonedValue;
}

DataType* ConstructFloatDataType() {
    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construct = floatConstruct;
    type->destruct = floatDestruct;

    type->getValue = floatGetValue;
    type->setValue = floatSetValue;

    type->randomValue = floatRandomValue;
    type->readFromKeyboard = floatReadFromKeyboard;
    type->writeToMonitor = floatWriteToMonitor;

    type->clone = floatClone;
    type->compare = floatCompare;

    return type;
}

void DestructFloatDataType(DataType* type) { //TODO: Vuole questo?
    free(type);
}
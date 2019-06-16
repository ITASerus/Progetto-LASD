
#include "adtflt.h"

/* ************************************************************************** */

void* floatConstruct() {
    return (float*)malloc(sizeof(float));
}

void floatDestruct(void* value) {
    free(value);
}

void* floatGetValue(void* value) {
    float* valueCopy = (float*)malloc(sizeof(float));
    *valueCopy = *(float*) value;
    return valueCopy;
}

void floatSetValue(void** value, void* newValue) {
    *((float*) *value) = *(float*)newValue;
}

void* floatRandomValue() {
    float* rndValue = (float*)malloc(sizeof(float));
    *rndValue = ((float)rndNum(-MaxFltAbsRndVal, MaxFltAbsRndVal)/(float)(MaxFltPrcRndVal)) * MaxFltAbsRndVal;
    return rndValue;
}

void* floatReadFromKeyboard() {
    float* value = (float*)malloc(sizeof(float));

    char* buffer = (char*)malloc(sizeof(char) * 25);
    getStr(buffer, 25);
    *value = strtof(buffer, NULL);

    return value;
}

void floatWriteToMonitor(void* value) {
    printf("%f", *(float*)value);
}

int floatCompare(void* firstValue, void* secondValue) {
    if(*(float*)firstValue < *(float*)secondValue) {
        return -1;
    } else if (*(float*)firstValue > *(float*)secondValue) {
        return 1;
    } else {
        return 0;
    }
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

void DestructFloatDataType(DataType* type) {
    free(type);
}
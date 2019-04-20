
#include "adtstr.h"

void* stringClone(void*);
char* rndStr(int numChar);
/* ************************************************************************** */

void* stringConstruct() {
    char* value = (char*)malloc(sizeof(char)* MaxStrLen);
    return value; //Ritorno NULL. Inutile allocare una stringa grande a piacere che poi avrà quasi sicuramente necessità di realloc
}

void stringDestruct(void* value) {
    free(value);
}

void* stringGetValue(void* value) {
    char* valueCopy = stringClone(value);
    return valueCopy;
}

void stringSetValue(void* value, void* newValue) { //TODO: Ragionare in modo opposto? alloco prima la memoria in stringConstruct e poi qua faccio ciò che devo
    //value = (char*)malloc(sizeof(char)* (strlen(newValue)+1));
    strcpy((char*)value, (char*)newValue);
}


void* stringRandomValue() { //TODO: Rivedi struttura
    char* rndString = rndStr(rndNum(1, MaxStrLen));
    return rndString;
}

void stringWriteToMonitor(void* value) {
    printf("%s", (char*)value);
}


int stringCompare(void* firstValue, void* secondValue) {
    return strcmp((char*)firstValue, (char*)secondValue);
}

void* stringClone(void* value) {
    char* clonedValue = (char*)malloc(sizeof(char)*(strlen(value)+1));
    strcpy(clonedValue, value);
    return clonedValue;
}

DataType* ConstructStringDataType() {
    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construct = stringConstruct;
    type->destruct = stringDestruct;

    type->getValue = stringGetValue;
    type->setValue = stringSetValue;

    type->randomValue = stringRandomValue;
    //type->readFromKeyboard = stringReadFromKeyboard; //TODO: Da implementare
    type->writeToMonitor = stringWriteToMonitor;

    type->clone = stringClone;
    type->compare = stringCompare;

    return type;
}

void DestructStringDataType(DataType* type) {
    free(type);
}

/* ************************************************************************** */

char* rndStr(int numChar) {
    char* newString = (char*)malloc(sizeof(char)*(numChar+1));

    for(uint i = 0; i<numChar; ++i) {
        newString[i] = (char)rndNum(65, 90);
    }
    newString[numChar] = '\0';

    return newString;
}
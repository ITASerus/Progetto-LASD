/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "adtstr.h"

void* stringClone(void*);
char* rndStr(int numChar);
/* ************************************************************************** */

void* stringConstruct() {
    char* value = (char*)malloc(sizeof(char) * (MaxStrLen + 1));
    strcpy(value, "");
    return value;
}

void stringDestruct(void* value) {
    free(value);
}

void* stringGetValue(void* value) {
    char* valueCopy = (char*)malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(valueCopy, value);
    return valueCopy;
}

void stringSetValue(void** value, void* newValue) {
    strcpy((char*) *value, (char*) newValue);
}


void* stringRandomValue() {
    return rndStr(rndNum(1, MaxStrLen));
}

void* stringReadFromKeyboard() {
    char* string = (char*)malloc(sizeof(char) * (MaxStrLen + 1));

    getStr(string, MaxStrLen);

    return string;
}

void stringWriteToMonitor(void* value) {
    printf("%s", (char*)value);
}


int stringCompare(void* firstValue, void* secondValue) {
    return strcmp((char*)firstValue, (char*)secondValue);
}

void* stringClone(void* value) {
    char* clonedValue = (char*)malloc(sizeof(char) * (strlen(value) + 1));
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
    type->readFromKeyboard = stringReadFromKeyboard;
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
    char* newString = (char*)malloc(sizeof(char) * (numChar + 1));

    for(uint i = 0; i < numChar; ++i) {
        newString[i] = (char)rndNum(65, 90);
    }
    newString[numChar] = '\0';

    return newString;
}

#include "adtstr.h"

void* stringClone(void*);
char* rndStr(int numChar);
/* ************************************************************************** */

void* stringConstruct() {
    char* value = (char*)malloc(sizeof(char) * (MaxStrLen + 1)); //TODO: Sostituire con calloc?
    strcpy(value, "");//o
    //value[0] = '\0';
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

void stringSetValue(void* value, void* newValue) {
    if (strlen((char*) newValue) > strlen(value)) { //TODO: Scegli
    //if (strlen((char*) value) != strlen((char*) newValue)) {
        value = (char *)realloc(value, sizeof(char) * (strlen((char *) newValue) + 1));
        strcpy(value, ""); //o ((char*)value)[0] = '\0';
        if (value == NULL) {
            printf("REALLOC FALLITA\n"); //TODO: Gestisci
        }
    }

    strcpy((char*)value, (char*)newValue);
}


void* stringRandomValue() {
    return rndStr(rndNum(1, MaxStrLen));
}

void* stringReadFromKeyboard() {
    char* string = (char*)malloc(sizeof(char));
    scanf("%s", string);
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
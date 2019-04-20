
#include "adtrec.h"

char* rndStr(int numChar);

/* ************************************************************************** */ //TODO: Rivedi le allocazioni di memoira

void* recordConstruct() {
    Record* record = (Record*)malloc(sizeof(Record));
    record->name = NULL;
    record->surname = NULL;

    return record;
}

void recordDestruct(void* value) {
    free(((Record*)value)->name);
    free(((Record*)value)->surname);
    free(value); //TODO: Necessita di cast?
}

void* recordGetValue(void* value) { //TODO: Usa recordClone
    Record* recordCopy = (Record*)malloc(sizeof(Record));

    recordCopy->name = (char*)malloc(sizeof(char)* strlen(((Record*)value)->name)+1 );
    strcpy(recordCopy->name, ((Record*)value)->name);

    recordCopy->surname = (char*)malloc(sizeof(char)* strlen(((Record*)value)->surname)+1 );
    strcpy(recordCopy->surname, ((Record*)value)->surname);

    return recordCopy;
}

void recordSetValue(void* value, void* newValue) {
    ((Record*)value)->name = ((Record*)newValue)->name;
    ((Record*)value)->surname = ((Record*)newValue)->surname;
}

void* recordRandomValue() { //TODO: Rivedi struttura
    Record* rndValue = recordConstruct();

    rndValue->name = rndStr(5);
    rndValue->surname = rndStr(10);

    return rndValue;
}

void* recordReadFromKeyboard() { //TODO: DA IMPLEMENTARE - Rivedi struttura, non usare scanf
    /*int* value = (int*)malloc(sizeof(int));
    scanf("%d", value);
    return value;*/
}

void recordWriteToMonitor(void* value) {
    printf("(name) %s\n(surname) %s", ((Record*)value)->name, ((Record*)value)->surname);
}

bool recordCompare(void* firstValue, void* secondValue) { //TODO: Distingui casi 1, -1, 0
    return ((strcmp(((Record*)firstValue)->name, ((Record*)secondValue)->name) == 0) &&
    (strcmp(((Record*)firstValue)->surname, ((Record*)secondValue)->surname) == 0));
}

void* recordClone(void* value) { //TODO: COPIA DI GETVALUE?
    Record* clonedValue = (Record*)malloc(sizeof(int)); //TODO: Usa recordConstruct?

    clonedValue->name = (char*)malloc(sizeof(char)* strlen(((Record*)value)->name)+1 );
    strcpy(clonedValue->name, ((Record*)value)->name);

    clonedValue->surname = (char*)malloc(sizeof(char)* strlen(((Record*)value)->surname)+1 );
    strcpy(clonedValue->surname, ((Record*)value)->surname);

    return clonedValue;
}

DataType* ConstructRecordDataType() {
    DataType* type = (DataType*)malloc(sizeof(DataType));

    type->construct = recordConstruct;
    type->destruct = recordDestruct;

    type->getValue = recordGetValue;
    type->setValue = recordSetValue;

    type->randomValue = recordRandomValue;
    type->readFromKeyboard = recordReadFromKeyboard;
    type->writeToMonitor = recordWriteToMonitor;

    type->clone = recordClone;
    type->compare = recordCompare;

    return type;
}

void DestructRecordDataType(DataType* type) { //TODO: Vuole questo?
    free(type);
}

/* ************************************************************************** */
/* //TODO: Vedi dove devi mettere questa funzione che sta pure in adtString
char* rndStr(int numChar) {
    char* newString = (char*)malloc(sizeof(char)*(numChar+1));

    for(uint i = 0; i<numChar; ++i) {
        newString[i] = (char)rndNum(65, 90);
    }
    newString[numChar] = '\0';

    return newString;
}
*/
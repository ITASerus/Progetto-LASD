
#include "adtrec.h"

char* rndStr(int numChar);

/* ************************************************************************** */

void* recordConstruct() {
    Record* record = (Record*)malloc(sizeof(Record));
    record->name = NULL;
    record->surname = NULL;

    return record;
}

void recordDestruct(void* value) {
    free(((Record*)value)->name);
    free(((Record*)value)->surname);
    free((Record*)value);
}

void* recordGetValue(void* value) {
    Record* recordCopy = (Record*)malloc(sizeof(Record));

    recordCopy->name = (char*)malloc(sizeof(char)* strlen(((Record*)value)->name)+1);
    strcpy(recordCopy->name, ((Record*)value)->name);

    recordCopy->surname = (char*)malloc(sizeof(char)* strlen(((Record*)value)->surname)+1);
    strcpy(recordCopy->surname, ((Record*)value)->surname);

    return recordCopy;
}

void recordSetValue(void** value, void* newValue) {
    if( (((Record*) *value)->name) != NULL && (((Record*) *value)->surname) != NULL) {
        if (strlen((((Record *) *value)->name)) != strlen((((Record *) newValue)->name))) {
            ((Record *) *value)->name = realloc((((Record *) *value)->name), sizeof(char) * (strlen((((Record *) newValue)->name)) + 1));
        }
        if (strlen((((Record *) *value)->surname)) != strlen((((Record *) newValue)->surname))) {
            ((Record *) *value)->surname = realloc((((Record *) *value)->surname), sizeof(char) * (strlen((((Record *) newValue)->surname)) + 1));
        }
    } else {
        (((Record*) *value)->name) = (char*)malloc(sizeof(char)*strlen((((Record*)newValue)->name))+1);
        (((Record*) *value)->surname) = (char*)malloc(sizeof(char)*strlen((((Record*)newValue)->surname))+1);
    }

    strcpy(((Record *) *value)->name, ((Record *) newValue)->name);
    strcpy(((Record *) *value)->surname, ((Record *) newValue)->surname);
}

void* recordRandomValue() {
    Record* rndValue = (Record*)malloc(sizeof(Record));

    rndValue->name = rndStr(5);
    rndValue->surname = rndStr(10);

    return rndValue;
}

void* recordReadFromKeyboard() {
    Record* record = (Record*)malloc(sizeof(Record));
    record->name = (char*)malloc(sizeof(char)*20);
    record->surname = (char*)malloc(sizeof(char)*20);

    printf("Inserire nome: ");
    scanf("%s", record->name);

    printf("Inserire cognome: ");
    scanf("%s", record->surname);

    return record;
}

void recordWriteToMonitor(void* value) {
    printf("(name) %s (surname) %s", ((Record*)value)->name, ((Record*)value)->surname);
}

int recordCompare(void* firstValue, void* secondValue) {
    if ((strcmp(((Record*)firstValue)->name, ((Record*)secondValue)->name) == 0) &&
        (strcmp(((Record*)firstValue)->surname, ((Record*)secondValue)->surname) == 0)) {
        return 0; //I due record sono uguali
    } else {
        return -1; //I due record NON sono uguali
    }
}

void* recordClone(void* value) {
    Record* clonedValue = (Record*)malloc(sizeof(Record));

    clonedValue->name = (char*)malloc(sizeof(char)* strlen(((Record*)value)->name) + 1);
    strcpy(clonedValue->name, ((Record*)value)->name);

    clonedValue->surname = (char*)malloc(sizeof(char)* strlen(((Record*)value)->surname) + 1);
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

void DestructRecordDataType(DataType* type) {
    free(type);
}
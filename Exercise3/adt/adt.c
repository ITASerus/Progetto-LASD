/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "adt.h"

/* ************************************************************************** */


DataObject* adtConstruct(DataType* dataType) {
    DataObject* object = (DataObject*)malloc(sizeof(DataObject));

    object->type = dataType;
    object->value = object->type->construct();

    return object;
}

void adtDestruct(DataObject* object) {
    object->type->destruct(object->value);
    free(object);
}


void* adtGetValue(DataObject* object) {
    return object->type->getValue(object->value);
}

void adtSetValue(DataObject* object, void* elem) {
    object->type->setValue(&object->value, elem);
}

void adtRandomValue(DataObject* object) {
    object->type->destruct(object->value); //Libero la memoria occupata in precedenza
    object->value = object->type->randomValue();
}

void adtReadFromKeyboard(DataObject* object) {
    adtSetValue(object, object->type->readFromKeyboard());
}

void adtWriteToMonitor(DataObject* object) {
    object->type->writeToMonitor(object->value);
}


//Prende in input un oggetto astratto e ne restituisce un clone
DataObject* adtClone(DataObject* object) {
    //Crea l'oggetto clone e ne inizializza i campi
    DataObject* clonedObject = (DataObject*)malloc(sizeof(DataObject));

    clonedObject->type = object->type;
    clonedObject->value = object->type->clone(object->value); //Assegna all'oggetto clone lo stesso valore dell'oggetto clonato

    return clonedObject;
}

int adtCompare(DataObject* firstObject, DataObject* secondObject) {
        return firstObject->type->compare(firstObject->value, secondObject->value);
}
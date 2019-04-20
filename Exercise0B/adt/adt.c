
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
    object->type->setValue(object->value, elem);
}

void adtRandomValue(DataObject* object) {
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
    DataObject* clonedObejct = adtConstruct(object->type); //Crea l'oggetto clone
    clonedObejct->value = object->type->clone(object->value); //Assegna all'oggetto clone lo stesso valore dell'oggetto clonato

    return clonedObejct;
}

bool adtCompare(DataObject* firstObject, DataObject* secondObject) { //TODO: Ritorna -1, 0 o +1 ecc?
    if(firstObject->type == secondObject->type) {
        return firstObject->type->compare(firstObject->value, secondObject->value);
    } else {
        return false;
    }
}
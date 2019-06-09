
#include "stackvec.h"

/* ************************************************************************** */

void* stkVecConstruct() {
    StackVec* obj = (StackVec*)malloc(sizeof(StackVec));

    obj->index = 0;
    obj->size = 0;
    obj->elements = NULL;

    return obj;
}

void* stkVecConstructWSize(int size) {
    StackVec * obj = (StackVec *) malloc(sizeof(StackVec));

    obj->index = 0;
    obj->size = size;
    obj->elements = (DataObject**)malloc(sizeof(DataObject*)*size);

    return obj;
}

void stkVecDestruct(void* stack) {
    StackVec* stackVector = stack;

    for (uint i = 0; i<stackVector->index; ++i) {
        adtDestruct(stackVector->elements[i]);
    }

    free(stackVector->elements);
    free(stack);
}


bool stkVecEmpty(void* stack) {
    if (((StackVec*)stack)->index == 0) {
        return true;
    } else {
        return false;
    }
}

void* stkVecTop(void* stack) {
    StackVec* stackVector = stack;

    if(!stkVecEmpty(stackVector)) {
        return adtClone(stackVector->elements[stackVector->index-1]);
    } else {
        return NULL;
    }
}

void stkVecPop(void* stack) {
    StackVec* stackVector = stack;

    if(!stkVecEmpty(stackVector)) { //Se lo stack è vuoto non è possibile rimuovere elementi
        adtDestruct(stackVector->elements[stackVector->index-1]);
        stackVector->elements[stackVector->index - 1] = NULL; //Per precauzione assegno la posizione non più utilizzata a NULL

        stackVector->index--;

        if(stackVector->index < stackVector->size/4) { //Lo stack ha troppa memoria libera //TODO: Zona decommentata, ritesta
            stackVector->size /= 2;
            stackVector->elements = realloc(stackVector->elements, sizeof(DataObject*) * stackVector->size); //Rimuovo la memoria in eccesso

            assert(stackVector->elements != NULL);
        }
    }
}

void* stkVecTopNPop(void* stack) {
    StackVec* stackVector = stack;

    if(!stkVecEmpty(stackVector)) {
        DataObject *poppedElement = adtClone(stackVector->elements[stackVector->index - 1]);
        stkVecPop(stackVector);

        return poppedElement;
    } else {
        return NULL; //Lo stack è vuoto
    }
}

void stkVecPush(void* stack, void* elem) {
    StackVec* stackVector = stack;

    //Controllo memoria disponibile
    if(stackVector->index == stackVector->size) { //Non ci sono slot liberi
        if (stackVector->elements == NULL) { //Lo stack non è stato ancora inizializzato
            stackVector->size = 4;
            stackVector->elements = (DataObject**)malloc(sizeof(DataObject*) * stackVector->size);
        } else { //La memoria dello stack è stata allocata almeno una volta
            stackVector->size *= 2; //Raddoppio la sua dimensione
            stackVector->elements = realloc(stackVector->elements, sizeof(DataObject*) * stackVector->size); //Alloco nuova memoria
        }
    }

    //Inserimento effettivo della stringa nello stack
    stackVector->elements[stackVector->index] = adtClone(elem);
    stackVector->index++;
}

void stkVecClear(void* stack) {
    StackVec* stackVector = stack;

    for (uint i = 0; i<stackVector->index; ++i) {
        adtDestruct(stackVector->elements[i]);
    }

    free(stackVector->elements);
    stackVector->elements = NULL;
    stackVector->index = 0;
    stackVector->size = 0;
}


void* stkVecClone(void* stack) {
    StackVec* stackVector = stack;

    StackVec* clonedStack = stkVecConstructWSize(stackVector->size);

    while(clonedStack->index < stackVector->index) {
        clonedStack->elements[clonedStack->index] = adtClone(stackVector->elements[clonedStack->index]);
        clonedStack->index++;
    }

    return clonedStack;
}

bool stkVecEqual(void* firstStack, void* secondStack) {
    StackVec* firstStackVector = firstStack;
    StackVec* secondStackVector = secondStack;

    if(firstStackVector->index != secondStackVector->index) //Se gli index delle due stack non coincidono, una delle due stack è più corta dell'altra quindi sono diverse ed inutile procedere con il confronto
        return false;

    uint i = 0;
    while(i < firstStackVector->index) {
        if(adtCompare(firstStackVector->elements[i], secondStackVector->elements[i]) != 0) {
            return false;
        }
        i++;
    }
    return true;
}

void stkVecMap(void* stack, MapFun function, void* param) {
    StackVec* stackVector = stack;

    for(int i = stackVector->index-1; i >=0; --i) {
        function(stackVector->elements[i], param);
    }
}

void stkVecFold(void* stack, FoldFun function, void* accumulator, void* param) {
    StackVec* stackVector = stack;

    for(int i = stackVector->index-1; i >= 0; --i) {
        function(stackVector->elements[i], accumulator, param);
    }
}


StackType* ConstructStackVecType() {
    StackType* type = (StackType*)malloc(sizeof(StackType));

    type->construct = stkVecConstruct;
    type->destruct = stkVecDestruct;

    type->isEmpty = stkVecEmpty;
    type->top = stkVecTop;
    type->pop = stkVecPop;
    type->topNPop = stkVecTopNPop;
    type->push = stkVecPush;
    type->clear = stkVecClear;

    type->clone = stkVecClone;
    type->equal = stkVecEqual;
    type->map  = stkVecMap;
    type->fold = stkVecFold;

    return type;
}

void DestructStackVecType(StackType* stackType) {
    free(stackType);
}
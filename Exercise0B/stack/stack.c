
#include "stack.h"

/* ************************************************************************** */

StackObject* stkConstruct() {
    StackObject * obj = (StackObject *) malloc(sizeof(StackObject));

    obj->index = 0;
    obj->size = 0;
    obj->elements = NULL;

    return obj;
}

StackObject* stkConstructWSize(int size) {
    StackObject * obj = (StackObject *) malloc(sizeof(StackObject));

    obj->index = 0;
    obj->size = size;
    obj->elements = (DataObject**)malloc(sizeof(DataObject*)*size);

    return obj;
}

void stkDestruct(StackObject* stack) {
    for (uint i = 0; i<stack->index; ++i) {
        adtDestruct(stack->elements[i]);
    }

    free(stack->elements);
    free(stack);
}


bool stkEmpty(StackObject* stack) {
    if (stack->index == 0) {
        return true;
    } else {
        return false;
    }
}

DataObject* stkTop(StackObject* stack) {
    return adtClone(stack->elements[stack->index-1]);
}

void stkPop(StackObject* stack) {
    if(!stkEmpty(stack)) { //Se lo stack è vuoto non è possibile rimuovere elementi
        adtDestruct(stack->elements[stack->index-1]);
        stack->elements[stack->index - 1] = NULL; //Per precauzione assegno la posizione non più utilizzata a NULL

        stack->index--;

        if(stack->index < stack->size/4) { //Lo stack ha troppa memoria libera
            stack->size /= 2;
            stack->elements = realloc(stack->elements, sizeof(DataObject*) * stack->size); //Rimuovo la memoria in eccesso

            if(stack->elements == NULL) {
                printf("ERRORE REALLOC -----------------\n"); //TODO: Gestisci
            }
        }
    }
}

DataObject* stkTopNPop(StackObject* stack) {
    if(!stkEmpty(stack)) {
        DataObject *poppedElement = adtClone(stack->elements[stack->index - 1]);

        stkPop(stack);

        return poppedElement;
    } else {
        return NULL; //Lo stack è vuoto
    }
}

void stkPush(StackObject* stack, DataObject* elem) {
    //Controllo memoria disponibile
    if(stack->index == stack->size) { //Non ci sono slot liberi
        if (stack->elements == NULL) { //Lo stack non è stato ancora inizializzato
            stack->size = 4;
            stack->elements = (DataObject**)malloc(sizeof(DataObject*)*stack->size);
        } else { //La memoria dello stack è stata allocata almeno una volta
            stack->size *= 2; //Raddoppio la sua dimensione
            stack->elements = realloc(stack->elements, sizeof(DataObject*) * stack->size); //Alloco nuova memoria
        }
    }

    //Inserimento effettivo della stringa nello stack
    stack->elements[stack->index] = adtClone(elem);
    stack->index++;
}

int stkSize(StackObject* stack) {
    return stack->index;
}

StackObject* stkClone(StackObject* stack) {
    /*StackObject* clonedStack = stkConstruct();

    for(uint i = 0; i<stack->index; ++i) {
        stkPush(clonedStack, stack->elements[i]);
    }

    return clonedStack;*/
    StackObject* clonedStack = stkConstructWSize(stack->size);

    while(clonedStack->index < stack->index) {
        printf("Clono: ");
        adtWriteToMonitor(stack->elements[clonedStack->index]);
        printf("\n");
        clonedStack->elements[clonedStack->index] = adtClone(stack->elements[clonedStack->index]);
        clonedStack->index++;
    }

    return clonedStack;
}

bool stkEqual(StackObject* firstStack, StackObject* secondStack) {
    if(firstStack->index != secondStack->index) //Se gli index delle due stack non coincidono, una delle due stack è più corta dell'altra quindi sono diverse ed inutile procedere con il confronto
        return false;

    uint i = 0;
    while(i < firstStack->index) {
        if(adtCompare(firstStack->elements[i], secondStack->elements[i]) != 0) {
            return false;
        }
        i++;
    }
    return true;
}

bool stkExists(StackObject* stack, DataObject* object) {
    uint i = 0;
    while(i < stack->index) {
        if(adtCompare(stack->elements[i], object) == 0) {
            return true;
        }
        ++i;
    }
    return false;
}

void stkMap(StackObject* stack, MapFun function, void* param) {
    for(uint i = 0; i<stack->index; ++i) {
        function(stack->elements[i], param);
    }
}

void stkFold(StackObject* stack, FoldFun function, void* accumulator, void* param) {
    for(uint i = 0; i<stack->index; ++i) {
        function(stack->elements[i], accumulator, param);
    }
}
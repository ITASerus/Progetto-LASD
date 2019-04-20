
#include "stack.h"

/* ************************************************************************** */

struct StackObject* stkConstruct() {
    StackObject * obj = (StackObject *) malloc(sizeof(StackObject));

    obj->size = 0;
    obj->index = 0;
    obj->elements = NULL;

    return obj;
}

void stkDestruct(StackObject* stack) {
    for (uint i = 0; i<stack->index; ++i) {
        free(stack->elements[i]);
    }
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

void stkPop(StackObject* stack) { //TODO: Realloca spazio quando numero di elementi è <=1/3 della dimensione, Controlla logica
    adtDestruct(stack->elements[stack->index-1]);
    stack->elements[stack->index - 1] = NULL; //Per precauzione assegno la posizione non più utilizzata a NULL

    stack->index--;
}

DataObject* stkTopNPop(StackObject* stack) { //TODO: Realloca spazio quando numero di elementi è <=1/3 della dimensione
    DataObject* poppedElement = adtClone(stack->elements[stack->index-1]);

    free(stack->elements[stack->index-1]);
    stack->index--;

    return poppedElement;
}

void stkPush(StackObject* stack, DataObject* elem) { //TODO: Usare stkEmpty per controllo se stack vuoto?
    DataObject* elemCopy = adtClone(elem);

    //Controllo memoria disponibile
    if(stack->index == stack->size) { //Non ci sono slot liberi
        if (stack->elements == NULL) { //Lo stack non è stato ancora inizializzato
            stack->size = 4;
            stack->elements = (DataObject**)malloc(sizeof(DataObject*)*stack->size);
        } else { //Lo stack è stato allocato almeno una volta
            stack->size *= 2; //Raddoppio la sua dimensione
            stack->elements = realloc(stack->elements, sizeof(DataObject*) * stack->size); //Alloco nuova memoria
        }
    }

    //Inserimento effettivo della stringa nello stack
    stack->elements[stack->index] = elemCopy;
    stack->index++;
}

int stkSize(StackObject* stack) {
    return stack->index;
}

StackObject* stkClone(StackObject* stack) {
    StackObject* clonedStack = stkConstruct(); //TODO: Creare un costruttore che alloca direttamente ciò che serve per allocare tutto stack, per questioni di efficienza

    for(uint i = 0; i<stack->index; ++i) {
        stkPush(clonedStack, stack->elements[i]);
    }

    return clonedStack;
}

bool stkEqual(StackObject* firstStack, StackObject* secondStack) { //TODO: RIVEDI STRUTTURA - Trattare come strcmp? (restituire <0 se stk1>stk2, 0 se stk1 == stk2 e >1 se stk1<stk2)

    if(firstStack->index != secondStack->index)
        return false;

    uint i = 0;
    while(i < firstStack->index) {
        if(!adtCompare(firstStack->elements[i], firstStack->elements[i])) {
            return false;
        }
        ++i;
    }

    return true;
}

bool stkExists(StackObject* stack, DataObject* object) { //TODO: Far scorrere lo stack da index a 0 e non da 0 a index, Si può togliere valueExists (vedi queue)
    uint i = 0;
    while(i < stack->index) { //TODO: Assicurati che non serve -1
        if(adtCompare(stack->elements[i], object)) {
            return true;
        }
        ++i;
    }
    return false;
}

void stkMap(StackObject* stack,MapFun function, void* param) { //TODO: Ragionacii meglio sopra. Aggiungere concetto di funzione parametrica?
    for(uint i = 0; i<stack->index; ++i) {
        function(stack->elements[i], param);
    }
}

void stkFold(StackObject* stack, FoldFun function, void* accumulator, void* param) { //TODO: NON FUNZIONA BENE?, Aggiungere concetto di funzione parametrica?, Far scorrere lo stack da index a 0 e non da 0 a index
    for(uint i = 0; i<stack->index; ++i) {
        function(stack->elements[i], accumulator, param);
    }
}
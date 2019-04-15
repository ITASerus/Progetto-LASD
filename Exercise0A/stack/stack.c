#include "stack.h"

/* ************************************************************************** */

struct StackObject* stkConstruct() {
	struct StackObject * obj = (struct StackObject *) malloc(sizeof(StackObject)); //TODO: Togliere riferimenti a struct

    obj->size = 0;
    obj->index = 0;
	obj->elements = NULL; //(char**)malloc(sizeof(char*)*obj->size);

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

char* stkTop(StackObject* stack) {
    char* elemCopy = (char*)malloc(sizeof(char)*(strlen(stack->elements[stack->index-1])+1));
    strcpy(elemCopy, stack->elements[stack->index-1]);

    return elemCopy;
}

void stkPop(StackObject* stack) { //TODO: Realloca spazio quando numero di elementi è <=1/3 della dimensione, Controlla logica
    free(stack->elements[stack->index-1]);
    stack->elements[stack->index - 1] = NULL;

    stack->index--;
}

char* stkTopNPop(StackObject* stack) { //TODO: Realloca spazio quando numero di elementi è <=1/3 della dimensione
    char* poppedElement = stack->elements[stack->index-1]; //TODO: SBAGLIATA! Devo copiare l'elemento, restituire la copia e poi fare la free dell'elemento nello stack!
    stack->elements[stack->index-1] = NULL;

    free(stack->elements[stack->index-1]);
    stack->index--;

    return poppedElement;
}

void stkPush(StackObject* stack, char* elem) { //TODO: Usare stkEmpty per controllo se stack vuoto?
    char* elemCopy = (char*)malloc(sizeof(char)*(strlen(elem)+1));
    strcpy(elemCopy, elem);

    //Controllo memoria disponibile
    if(stack->index == stack->size) { //Non ci sono slot liberi
        if (stack->elements == NULL) { //Lo stack non è stato ancora inizializzato
            stack->size = 4;
            stack->elements = (char**)malloc(sizeof(char*)*stack->size);
        } else { //Lo stack è stato allocato almeno una volta
            stack->size *= 2; //Raddoppio la sua dimensione
            stack->elements = realloc(stack->elements, sizeof(char*) * stack->size); //Alloco nuova memoria
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

bool stkEqual(StackObject* stack1, StackObject* stack2) { //TODO: Trattare come strcmp? (restituire <0 se stk1>stk2, 0 se stk1 == stk2 e >1 se stk1<stk2)
    bool areEqual = true;
    uint i = 0;

    while(i < stack1->index-1) {
        if(strcmp(stack1->elements[i], stack2->elements[i]) != 0) {
            areEqual = false;
            break;
        }
        ++i;
    }

    return areEqual;
}

bool stkExists(StackObject* stack, char* value) { //TODO: Far scorrere lo stack da index a 0 e non da 0 a index, Si può togliere valueExists (vedi queue)
    bool valueExists = false;
    uint i = 0;
    while(i < stack->index-1) {
        if(strcmp(stack->elements[i], value) == 0) {
            valueExists = true;
            break;
        }
        ++i;
    }

    return valueExists;
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

/* ************************************************************************** */

void turnToChar(void* elm, void* character) {
    assert(elm != NULL); //TODO: Studia istruzione assert
    strcpy(elm, character);
}

void strConcat(void* elm, void* accumulator, void* param) {
    sprintf("val elm: %s - val acc: %s", elm, accumulator);
    char* resultString = (char*)malloc(sizeof(char)*(strlen(accumulator)+strlen(elm)));
    strcpy(resultString, strcat(accumulator, elm));
    printf("result str: %s\n", resultString);
}

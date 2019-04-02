#include "stack.h"

/* ************************************************************************** */

struct StackObject* stkConstruct() {
	struct StackObject * obj = (struct StackObject *) malloc(sizeof(StackObject));

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


char* stkTop(StackObject* stack) {
    char* elemCopy = (char*)malloc(sizeof(char)*(strlen(stack->elements[stack->index-1])));
    strcpy(elemCopy, stack->elements[stack->index-1]);

    return elemCopy;
}

void stkPop(StackObject* stack) {
    free(stack->elements[stack->index-1]);
    stack->elements[stack->index - 1] = NULL;

    stack->index--;
}

char* stkTopNPop(StackObject* stack) {
    char* poppedElement = stack->elements[stack->index-1];
    stack->elements[stack->index-1] = NULL;

    free(stack->elements[stack->index-1]);
    stack->index--;

    return poppedElement;
}

void stkPush(StackObject* stack, char* elem) {
    char* elemCopy = (char*)malloc(sizeof(char)*strlen(elem));
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

   uint i = 0;
   while(i < stack->index-1) {
       stkPush(clonedStack, stack->elements[i]);
       ++i;
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

bool stkExists(StackObject* stack, char* value) { //TODO: Far scorrere lo stack da index a 0 e non da 0 a index
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

void stkMap(StackObject* stack, void* function, void* param) {

}

/* ************************************************************************** */

void printInfoStack(StackObject* stack) {
    printf("-- Dimensione allocata stack: %d\n-- Elementi contenuti nello stack: %d\n", stack->size, stack->index);
}

void printStack(StackObject * stack) {
    for( uint i = 0; i<stack->index; ++i) {
        printf("- %s\n", stack->elements[i]);
    }
}

char* rndStr(int numChar) { //TODO: rndStr - Il prof non vuole charset ma generazione tramite ASCII
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* newString = (char*)malloc(sizeof(char)*(numChar+1));

    for(uint i = 0; i<numChar; ++i) {
        newString[i] = charset[rndNum(0, 61)];
    }
    newString[numChar] = '\0';

    return newString;
}

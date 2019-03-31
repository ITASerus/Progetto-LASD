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


char* stkTopNPop(StackObject* stack) {
    char* poppedElement = stack->elements[stack->index];
    stack->elements[stack->index] = NULL;

    free(stack->elements[stack->index]);
    stack->index--;

    return poppedElement;
}

void stkPush(StackObject* stack, char* elem) {
    printf("\n");
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

/* ************************************************************************** */

void printInfoStack(StackObject* stack) {
    printf("-- Dimensione allocata stack: %d\n-- Elementi contenuti nello stack: %d\n", stack->size, stack->index);
}

void printStack(StackObject * stack) {
    for( uint i = 0; i<stack->index; ++i) {
        printf("- %s\n", stack->elements[i]);
    }
}

char* rndStr(int numChar) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* newString = (char*)malloc(sizeof(char)*(numChar+1));

    for(uint i = 0; i<numChar; ++i) {
        newString[i] = charset[rndNum(0, 61)];
    }
    newString[numChar] = '\0';

    return newString;
}

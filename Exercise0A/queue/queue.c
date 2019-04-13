
#include "queue.h"

/* ************************************************************************** */

QueueObject* queConstruct() {
    QueueObject * obj = (QueueObject *) malloc(sizeof(QueueObject));

    obj->front = -1;
    obj->rear = -1;
    obj->size = 0;
    obj->numElem = 0;
    obj->elements = NULL;

    return obj;
}

// type queDestruct(arguments);


bool queEmpty(QueueObject* queue) {
    return ((queue->front == -1) && (queue->rear == -1));
}

char* queHead(QueueObject* queue) {
    printf("HEAD) %s\n", queue->elements[17]);
    return queue->elements[queue->front];
}

void queDequeue(QueueObject* queue) {
    if(!queEmpty(queue)) {
        free(queue->elements[queue->front]);

        if (queue->front == queue->rear) { //La queue aveva un solo elemento
            queue->front = -1;
            queue->rear = -1;
        } else if (queue->front == queue->size-1) {  //La queue ha almeno un elemento e front si trova all'ultimo indice disponibile prima di ricominciare
            queue->front = 0;
        } else {
            queue->front++;
        }
        queue->numElem--;
    }
}

char* queHeadNDequeue(QueueObject* queue) { //TODO: Sostituire parte dell'algoritmo con queDequeue?
    if(!queEmpty(queue)) {
        char *dequeuedElement = (char *) malloc(sizeof(char) * strlen(queue->elements[queue->front]));
        strcpy(dequeuedElement, queue->elements[queue->front]);

        free(queue->elements[queue->front]);
        if (queue->front == queue->rear) { //La queue aveva un solo elemento
            queue->front = -1;
            queue->rear = -1;
        } else if (queue->front == queue->size-1) {  //La queue ha almeno un elemento e front si trova all'ultimo indice disponibile prima di ricominciare
            queue->front = 0;
        } else {
            queue->front++;
        }
        queue->numElem--;

        return dequeuedElement;
    } else { //La queue è vuota
        return NULL;
    }
}

void queEnqueue(QueueObject* queue, char* elem) {
    char* elemCopy = (char*)malloc(sizeof(char)*strlen(elem));
    strcpy(elemCopy, elem);

    //Controllo memoria disponibile
    if(queue->elements == NULL) { //Queue non ancora inizializzata
        queue->size = 2;
        queue->elements = (char**)malloc(sizeof(char*)*queue->size);
    } else if(((queue->front == 0) && (queue->rear == queue->size-1)) || (queue->rear == queue->front-1)) { //Non ci sono slot liberi
        char** newElements = (char**)malloc(sizeof(char*)*(queue->size*2)); //Alloco un vettore grande il doppio di quello attualmente contenuto in queue

        int newElementsIndex = 0;
        if(queue->front < queue->rear) { // TODO: Si può evitare di usare "i" sfruttando il fatto che non mi serve tenere traccia di queue->front?
            for(int i = queue->front; i<= queue->rear; i++) {
                newElements[newElementsIndex] = queue->elements[i];
                newElementsIndex++;
            }
        } else {
            for (int i = queue->front; i < queue->size; i++) {
                newElements[newElementsIndex] = queue->elements[i];
                newElementsIndex++;
            }
            for (int i = 0; i <= queue->rear; i++) {
                newElements[newElementsIndex] = queue->elements[i];
                newElementsIndex++;
            }
        }

        free(queue->elements);
        queue->elements = newElements;

        queue->front = 0;
        queue->rear = queue->numElem-1;

        queue->size *= 2;
    }

    //Inserimento effettivo della stringa nella queue
    if (queue->front == -1) { //La queue è vuota
        queue->front = 0;
        queue->rear = 0;
    } else {
        if(queue->rear == queue->size-1) { //rear è all'ultima posizione della queue
            queue->rear = 0;
        } else {
            queue->rear = queue->rear+1;
        }
    }
    //printf("Inserisco in posizione %d\n", queue->rear);
    queue->elements[queue->rear] = elemCopy;
    queue->numElem++;
}

char** duplicateAndOrderVectorElem(char** elements) {

}

int queSize(QueueObject* queue) {
    return queue->numElem;
}


QueueObject* queClone(QueueObject* queue) { //TODO: Controllare complessità computazionale: si può fare meglio?
    QueueObject* clonedQueue = queConstruct();

    if(queue->front < queue->rear) {
        for(int i = queue->front; i <= queue->rear; i++) {
            queEnqueue(clonedQueue, queue->elements[i]);
        }
    } else {
        for(int i = queue->front; i < queue->size; i++) {
            queEnqueue(clonedQueue, queue->elements[i]);
        }
        for(int i = 0; i<=queue->rear; i++) {
            queEnqueue(clonedQueue, queue->elements[i]);
        }
    }

    return clonedQueue;
}

bool queEqual(QueueObject* firstQueue, QueueObject* secondQueue) {
    if(firstQueue->front != -1 && secondQueue->front != -1) { //Controllo che entrambe le queue non siano vuote
        if(firstQueue->front < firstQueue->rear) {
            printf("-CASO F<R\n");
            for(int i = firstQueue->front; i <= firstQueue->rear; i++) {
                if(secondQueue->front < secondQueue->rear) {
                    for(int j = secondQueue->front; j <= secondQueue->rear; j++) {
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                } else {
                    for(int j = secondQueue->front; j < secondQueue->size; j++) {
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                    for(int j = 0; j <= secondQueue->rear; j++) {
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                }
            }
        } else {
            printf("-CASO F>R\n");
            for(int i = firstQueue->front; i < firstQueue->size; i++) {
                if(secondQueue->front < secondQueue->rear) {
                    for(int j = secondQueue->front; j <= secondQueue->rear; j++) {
                        printf("--COMPARE %s vs %s", firstQueue->elements[i], secondQueue->elements[j])
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                } else {
                    for(int j = secondQueue->front; j < secondQueue->size; j++) {
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                    for(int j = 0; j <= secondQueue->rear; j++) {
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                }
            }
            for(int i = 0; i < firstQueue->rear; i++) {
                if(secondQueue->front < secondQueue->rear) {
                    for(int j = secondQueue->front; j <= secondQueue->rear; j++) {
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                } else {
                    for(int j = secondQueue->front; j < secondQueue->size; j++) {
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                    for(int j = 0; j <= secondQueue->rear; j++) {
                        if(strcmp(firstQueue->elements[i], secondQueue->elements[j]) != 0) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool queExists(QueueObject* queue, char* elem) {
    if(queue->front < queue->rear) {
        for(int i = queue->front; i <= queue->rear; i++) {
            if(strcmp(queue->elements[i], elem) == 0) {
                return true;
            }
        }
    } else {
        for(int i = queue->front; i<queue->size; i++) {
            if(strcmp(queue->elements[i], elem) == 0) {
                return true;
            }
        }
        for(int i = 0; i<=queue->rear; i++) {
            if(strcmp(queue->elements[i], elem) == 0) {
                return true;
            }
        }
    }

    return false;
}

// type queMap(arguments);

// type queFold(arguments);

void queuePrint(QueueObject* queue) {
    printf("ELEMENTI:\n");

    if(!queEmpty(queue)) {
        if (queue->front <= queue->rear) {
            for(int i = queue->front; i <= queue->rear; ++i) {
                printf("%d) %s\n", i, queue->elements[i]);
            }
        } else {
            for(int i = queue->front; i < queue->size; ++i) {
                printf("%d) %s\n", i, queue->elements[i]);
            }
            for(int i = 0; i <= queue->rear; ++i) {
                printf("%d) %s\n", i, queue->elements[i]);
            }
        }
    } else {
        printf("Queue vuota\n");
    }
}

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
        printf("MEMORIA INIZIALIZZATA (%d)\n", queue->size);
    } else if(((queue->front == 0) && (queue->rear == queue->size-1)) || (queue->rear == queue->front-1)) { //Non ci sono slot liberi
        queue->size *= 2; //Raddoppio la sua dimensione
        queue->elements = realloc(queue->elements, sizeof(char *) * queue->size); //Alloco nuova memoria
        printf("MEMORIA RADDOPPIATA (%d)\n", queue->size);
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
    //rintf("Inserisco in posizione %d\n", queue->rear);
    queue->elements[queue->rear] = elemCopy;
    queue->numElem++;
}

int queSize(QueueObject* queue) {
    return queue->numElem;
}


// type queClone(arguments);

// type queEqual(arguments);

bool queExists(QueueObject* queue, char* elem) {
    int i = 0;

    while(i < queue->numElem) {
        printf("ELEMENTO: %s\n", queue->elements[i]);
        if(strcmp(queue->elements[i], elem) == 0) {
            return true;
        }
        ++i;
    }

    return false;
}

// type queMap(arguments);

// type queFold(arguments);

void queuePrint(QueueObject* queue) {
    printf("\nELEMENTI:\n");

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
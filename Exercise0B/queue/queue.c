
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

//Costruttore di queue che riceve come parametro la dimensione da allocare in memoria all'atto della creazione della queue
QueueObject* queConstructWSize(int size) {
    QueueObject * obj = (QueueObject *) malloc(sizeof(QueueObject));

    obj->front = -1;
    obj->rear = -1;
    obj->size = size;
    obj->numElem = 0;
    obj->elements = (DataObject**)malloc(sizeof(DataObject*)*size);

    return obj;
}

void queDestruct(QueueObject* queue) {
    if(!queEmpty(queue)) {
        if (queue->front < queue->rear) {
            for (uint i = queue->front; i <= queue->rear; ++i) {
                adtDestruct(queue->elements[i]);
            }
        } else {
            for (uint i = queue->front; i < queue->size; ++i) {
                adtDestruct(queue->elements[i]);
            }
            for (uint i = 0; i <= queue->rear; ++i) {
                adtDestruct(queue->elements[i]);
            }
        }
    }

    free(queue->elements);
    free(queue);
}


bool queEmpty(QueueObject* queue) {
    return queue->front == -1; //Se queue->front = -1, di conseguenza lo sarà sicuramente anche queue->rear. Tale situazione si verifica solo nel casp in cui la queue è vuota
}

DataObject* queHead(QueueObject* queue) {
    return adtClone(queue->elements[queue->front]);
}

void queDequeue(QueueObject* queue) {
    if(!queEmpty(queue)) {
        adtDestruct(queue->elements[queue->front]);

        if (queue->front == queue->rear) { //La queue aveva un solo elemento
            queue->front = -1;
            queue->rear = -1;
        } else queue->front = (queue->front+1)%queue->size; /*if (queue->front == queue->size-1) {  //La queue ha almeno un elemento e front si trova all'ultimo indice disponibile prima di ricominciare
            queue->front = 0;
        } else {
            queue->front++;
        }
        queue->numElem--;*/

        /*if(queue->numElem < queue->size/4) { //La queue ha troppa memoria libera
            printf("-------------- Dimezzo la dimensione della queue --------------\n");
            QueueObject* newQueue = queConstructWSize(queue->size/2);

            free(queue);
            *queue = *newQueue;
        }*/
    }
}

DataObject* queHeadNDequeue(QueueObject* queue) {
    if(!queEmpty(queue)) {
        DataObject* dequeuedElement = adtClone(queue->elements[queue->front]);

        queDequeue(queue);

        return dequeuedElement;
    } else { //La queue è vuota
        return NULL;
    }
}

void queEnqueue(QueueObject* queue, DataObject* elem) {
    //Controllo memoria disponibile
    if(queue->elements == NULL) { //Queue non ancora inizializzata
        queue->size = 2;
        queue->elements = (DataObject**)malloc(sizeof(DataObject*)*queue->size);
    } else if(((queue->front == 0) && (queue->rear == queue->size-1)) || (queue->rear == queue->front-1)) { //Non ci sono slot liberi
        DataObject** newElements = (DataObject**)malloc(sizeof(DataObject*)*(queue->size*2)); //Alloco un vettore grande il doppio di quello attualmente contenuto in queue

        int newElementsIndex = 0;
        if(queue->front < queue->rear) { //TODO: Risparmiati 4 bytes e il codice è meno leggibile... ne vale la pena?
            while(queue->front <= queue->rear) {
                newElements[newElementsIndex] = queue->elements[queue->front];
                newElementsIndex++;
                queue->front++;
            }
            /*for(int i = queue->front; i<= queue->rear; i++) {
                newElements[newElementsIndex] = queue->elements[i];
                newElementsIndex++;
            }*/
        } else {
            while(queue->front < queue->size) {
                newElements[newElementsIndex] = queue->elements[queue->front];
                newElementsIndex++;
                queue->front++;
            }
            queue->front = 0;
            while(queue->front <= queue->rear) {
                newElements[newElementsIndex] = queue->elements[queue->front];
                newElementsIndex++;
                queue->front++;
            }
            /*
            for (int i = queue->front; i < queue->size; i++) {
                newElements[newElementsIndex] = queue->elements[i];
                newElementsIndex++;
            }
            for (int i = 0; i <= queue->rear; i++) {
                newElements[newElementsIndex] = queue->elements[i];
              */

        }

        free(queue->elements);
        queue->elements = newElements;

        queue->front = 0;
        queue->rear = queue->numElem-1;

        queue->size *= 2;
    }

    //Inserimento effettivo della stringa nella queue
    /*if (queue->front == -1) { //La queue è vuota
        queue->front = 0;
        queue->rear = 0;
    } else {
        if(queue->rear == queue->size-1) { //rear è all'ultima posizione della queue
            queue->rear = 0;
        } else {
            queue->rear = queue->rear+1;
        }
    }*/
    if(queue->front == -1) {
        queue->front = 0;
    }
    queue->rear = (queue->rear+1) % queue->size;

    //printf("Inserisco in posizione %d\n", queue->rear);
    queue->elements[queue->rear] = adtClone(elem);
    queue->numElem++;
}

int queSize(QueueObject* queue) { //TODO: Togliere numElem e cambiare tutto di conseguenza
    return queue->numElem;
}


QueueObject* queClone(QueueObject* queue) {
    /*QueueObject* clonedQueue = queConstruct();

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

    return clonedQueue;*/

    QueueObject* clonedQueue = queConstructWSize(queue->size);

    if(!queEmpty(queue)) {
        if (queue->front < queue->rear) {
            for (int i = queue->front; i <= queue->rear; i++) {
                clonedQueue->rear++;
                clonedQueue->elements[clonedQueue->rear] = adtClone(queue->elements[i]);
            }
        } else {
            for (int i = queue->front; i < queue->size; i++) {
                clonedQueue->rear++;
                clonedQueue->elements[clonedQueue->rear] = adtClone(queue->elements[i]);
            }
            for (int i = 0; i <= queue->rear; i++) {
                clonedQueue->rear++;
                clonedQueue->elements[clonedQueue->rear] = adtClone(queue->elements[i]);
            }
        }

        clonedQueue->front = 0;
        clonedQueue->numElem = queue->numElem;
    }

    return clonedQueue;

}

bool queEqual(QueueObject* firstQueue, QueueObject* secondQueue) {
    if(!queEmpty(firstQueue) && !queEmpty(secondQueue)) {  //Controllo che entrambe le queue non siano vuote
        if(firstQueue->numElem != secondQueue->numElem) { //Controllo che il numero degli elementi delle queue sia lo stesso
            return false;
        }

        int j = secondQueue->front;
        if(firstQueue->front <= firstQueue->rear) {
            for(int i = firstQueue->front; i <= firstQueue->rear; i++) { //Ciclo su tutti gli elementi della prima queue
                if (adtCompare(firstQueue->elements[i], secondQueue->elements[j]) == 0) {
                    return false;
                }
                j++;
                if (j >= secondQueue->size) {
                    j = 0;
                }
            }
        } else {
            for(int i = firstQueue->front; i < firstQueue->size; i++) {
                if (adtCompare(firstQueue->elements[i], secondQueue->elements[j]) == 0) {
                    return false;
                }
                j++;
                if (j >= secondQueue->size) {
                    j = 0;
                }
            }
            for(int i = 0; i <= firstQueue->rear; i++) {
                if (adtCompare(firstQueue->elements[i], secondQueue->elements[j]) == 0) {
                    return false;
                }
                j++;
                if (j >= secondQueue->size) {
                    j = 0;
                }
            }
        }
    } else {
        return false; //Solo una delle due queue è vuota
    }
    return true;
}

bool queExists(QueueObject* queue, DataObject* elem) {
    if(!queEmpty(queue)) {
        if (queue->front < queue->rear) {
            for (int i = queue->front; i <= queue->rear; i++) {
                if (adtCompare(queue->elements[i], elem) == 0) {
                    return true;
                }
            }
        } else {
            for (int i = queue->front; i < queue->size; i++) {
                if (adtCompare(queue->elements[i], elem) == 0) {
                    return true;
                }
            }
            for (int i = 0; i <= queue->rear; i++) {
                if (adtCompare(queue->elements[i], elem) == 0) {
                    return true;
                }
            }
        }
    }

    return false;
}

void queMap(QueueObject* queue, MapFun function, void* param) {
    if(!queEmpty(queue)) {
        if (queue->front < queue->rear) {
            for (uint i = queue->front; i <= queue->rear; ++i) {
                function(queue->elements[i], param);
            }
        } else {
            for (uint i = queue->front; i < queue->size; ++i) {
                function(queue->elements[i], param);
            }
            for (uint i = 0; i <= queue->rear; ++i) {
                function(queue->elements[i], param);
            }
        }
    }
}

void queFold(QueueObject* queue, FoldFun function, void* accumulator, void* param) {
    if(!queEmpty(queue)) {
        if (queue->front < queue->rear) {
            for (uint i = queue->front; i <= queue->rear; ++i) {
                function(queue->elements[i], accumulator, param);
            }
        } else {
            for (uint i = queue->front; i < queue->size; ++i) {
                function(queue->elements[i], accumulator, param);
            }
            for (uint i = 0; i <= queue->rear; ++i) {
                function(queue->elements[i], accumulator, param);
            }
        }
    }
}

void queuePrint(QueueObject* queue) {
    if(!queEmpty(queue)) {
        if (queue->front <= queue->rear) {
            for(int i = queue->front; i <= queue->rear; ++i) {
                printf("%d) ", i);
                adtWriteToMonitor(queue->elements[i]);
                printf("\n");
            }
        } else {
            for(int i = queue->front; i < queue->size; ++i) {
                printf("%d) ", i);
                adtWriteToMonitor(queue->elements[i]);
                printf("\n");
            }
            for(int i = 0; i <= queue->rear; ++i) {
                printf("%d) ", i);
                adtWriteToMonitor(queue->elements[i]);
                printf("\n");
            }
        }
    } else {
        printf("Queue vuota\n");
    }
}

void elemConcat(char* elem, char* accumulator, void* param) {
    strcat(accumulator, elem);
}

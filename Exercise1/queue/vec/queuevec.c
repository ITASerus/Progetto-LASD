
#include "queuevec.h"

/* ************************************************************************** */

void* queVecConstruct() {
    QueueVec * obj = (QueueVec *) malloc(sizeof(QueueVec));

    obj->front = -1;
    obj->rear = -1;
    obj->size = 0;
    obj->numElem = 0;
    obj->elements = NULL;

    return obj;
}

//Costruttore di queue che riceve come parametro la dimensione da allocare in memoria all'atto della creazione della queue
void* queVecConstructWSize(int size) {
    QueueVec * obj = (QueueVec *) malloc(sizeof(QueueVec));

    obj->front = -1;
    obj->rear = -1;
    obj->size = size;
    obj->numElem = 0;
    obj->elements = (DataObject**)malloc(sizeof(DataObject*)*size);

    return obj;
}

bool queVecEmpty(void* queue) {
    return ((QueueVec*)queue)->front == -1; //Se queue->front = -1, di conseguenza lo sarà sicuramente anche queue->rear. Tale situazione si verifica solo nel casp in cui la queue è vuota
} //TODO: Evitare di usare queVecEmpty per lo stack

void queVecDestruct(void* queue) {
    QueueVec* queueVector = queue;
    if(!queVecEmpty(queueVector)) {
        if (queueVector->front < queueVector->rear) {
            for (uint i = queueVector->front; i <= queueVector->rear; ++i) {
                adtDestruct(queueVector->elements[i]);
            }
        } else {
            for (uint i = queueVector->front; i < queueVector->size; ++i) {
                adtDestruct(queueVector->elements[i]);
            }
            for (uint i = 0; i <= queueVector->rear; ++i) {
                adtDestruct(queueVector->elements[i]);
            }
        }
    }

    free(queueVector->elements);
    free(queueVector);
}


void* queVecHead(void* queue) {
    QueueVec* queueVector = queue;

    return adtClone(queueVector->elements[queueVector->front]);
}

void queVecDequeue(void* queue) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        adtDestruct(queueVector->elements[queueVector->front]);

        if (queueVector->front == queueVector->rear) { //La queue aveva un solo elemento
            queueVector->front = -1;
            queueVector->rear = -1;
        } else queueVector->front = (queueVector->front+1)%queueVector->size; /*if (queue->front == queue->size-1) {  //La queue ha almeno un elemento e front si trova all'ultimo indice disponibile prima di ricominciare
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

void* queVecHeadNDequeue(void* queue) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        DataObject* dequeuedElement = adtClone(queueVector->elements[queueVector->front]);

        queVecDequeue(queueVector);

        return dequeuedElement;
    } else { //La queue è vuota
        return NULL;
    }
}

void queVecEnqueue(void* queue, void* elem) {
    QueueVec* queueVector = queue;

    //Controllo memoria disponibile
    if(queueVector->elements == NULL) { //Queue non ancora inizializzata
        queueVector->size = 2;
        queueVector->elements = (DataObject**)malloc(sizeof(DataObject*)*queueVector->size);
    } else if(((queueVector->front == 0) && (queueVector->rear == queueVector->size-1)) || (queueVector->rear == queueVector->front-1)) { //Non ci sono slot liberi
        DataObject** newElements = (DataObject**)malloc(sizeof(DataObject*)*(queueVector->size*2)); //Alloco un vettore grande il doppio di quello attualmente contenuto in queue

        int newElementsIndex = 0;
        if(queueVector->front < queueVector->rear) { //TODO: Risparmiati 4 bytes e il codice è meno leggibile... ne vale la pena?
            while(queueVector->front <= queueVector->rear) {
                newElements[newElementsIndex] = queueVector->elements[queueVector->front];
                newElementsIndex++;
                queueVector->front++;
            }
            /*for(int i = queue->front; i<= queue->rear; i++) {
                newElements[newElementsIndex] = queue->elements[i];
                newElementsIndex++;
            }*/
        } else {
            while(queueVector->front < queueVector->size) {
                newElements[newElementsIndex] = queueVector->elements[queueVector->front];
                newElementsIndex++;
                queueVector->front++;
            }
            queueVector->front = 0;
            while(queueVector->front <= queueVector->rear) {
                newElements[newElementsIndex] = queueVector->elements[queueVector->front];
                newElementsIndex++;
                queueVector->front++;
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

        free(queueVector->elements);
        queueVector->elements = newElements;

        queueVector->front = 0;
        queueVector->rear = queueVector->numElem-1;

        queueVector->size *= 2;
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
    if(queueVector->front == -1) {
        queueVector->front = 0;
    }
    queueVector->rear = (queueVector->rear+1) % queueVector->size;

    //printf("Inserisco in posizione %d\n", queue->rear);
    queueVector->elements[queueVector->rear] = adtClone(elem);
    queueVector->numElem++;
}

int queVecSize(void* queue) { //TODO: Togliere numElem e cambiare tutto di conseguenza
    return ((QueueVec*)queue)->numElem;
}


void* queVecClone(void* queue) {
    QueueVec* queueVector = queue;

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

    QueueVec* clonedQueue = queVecConstructWSize(queueVector->size);

    if(!queVecEmpty(queueVector)) {
        if (queueVector->front < queueVector->rear) {
            for (int i = queueVector->front; i <= queueVector->rear; i++) {
                clonedQueue->rear++;
                clonedQueue->elements[clonedQueue->rear] = adtClone(queueVector->elements[i]);
            }
        } else {
            for (int i = queueVector->front; i < queueVector->size; i++) {
                clonedQueue->rear++;
                clonedQueue->elements[clonedQueue->rear] = adtClone(queueVector->elements[i]);
            }
            for (int i = 0; i <= queueVector->rear; i++) {
                clonedQueue->rear++;
                clonedQueue->elements[clonedQueue->rear] = adtClone(queueVector->elements[i]);
            }
        }

        clonedQueue->front = 0;
        clonedQueue->numElem = queueVector->numElem;
    }

    return clonedQueue;

}

bool queVecEqual(void* firstQueue, void* secondQueue) {
    QueueVec* firstQueueVector = firstQueue;
    QueueVec* secondQueueVector = secondQueue;

    if(!queVecEmpty(firstQueueVector) && !queVecEmpty(secondQueue)) {  //Controllo che entrambe le queue non siano vuote
        if(firstQueueVector->numElem != secondQueueVector->numElem) { //Controllo che il numero degli elementi delle queue sia lo stesso
            return false;
        }

        int j = secondQueueVector->front;
        if(firstQueueVector->front <= firstQueueVector->rear) {
            for(int i = firstQueueVector->front; i <= firstQueueVector->rear; i++) { //Ciclo su tutti gli elementi della prima queue
                if (adtCompare(firstQueueVector->elements[i], secondQueueVector->elements[j]) == 0) {
                    return false;
                }
                j++;
                if (j >= secondQueueVector->size) {
                    j = 0;
                }
            }
        } else {
            for(int i = firstQueueVector->front; i < firstQueueVector->size; i++) {
                if (adtCompare(firstQueueVector->elements[i], secondQueueVector->elements[j]) == 0) {
                    return false;
                }
                j++;
                if (j >= secondQueueVector->size) {
                    j = 0;
                }
            }
            for(int i = 0; i <= firstQueueVector->rear; i++) {
                if (adtCompare(firstQueueVector->elements[i], secondQueueVector->elements[j]) == 0) {
                    return false;
                }
                j++;
                if (j >= secondQueueVector->size) {
                    j = 0;
                }
            }
        }
    } else {
        return false; //Solo una delle due queue è vuota
    }
    return true;
}

bool queVecExists(void* queue, DataObject* elem) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        if (queueVector->front < queueVector->rear) {
            for (int i = queueVector->front; i <= queueVector->rear; i++) {
                if (adtCompare(queueVector->elements[i], elem) == 0) {
                    return true;
                }
            }
        } else {
            for (int i = queueVector->front; i < queueVector->size; i++) {
                if (adtCompare(queueVector->elements[i], elem) == 0) {
                    return true;
                }
            }
            for (int i = 0; i <= queueVector->rear; i++) {
                if (adtCompare(queueVector->elements[i], elem) == 0) {
                    return true;
                }
            }
        }
    }

    return false;
}

void queVecMap(void* queue, MapFun function, void* param) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        if (queueVector->front < queueVector->rear) {
            for (uint i = queueVector->front; i <= queueVector->rear; ++i) {
                function(queueVector->elements[i], param);
            }
        } else {
            for (uint i = queueVector->front; i < queueVector->size; ++i) {
                function(queueVector->elements[i], param);
            }
            for (uint i = 0; i <= queueVector->rear; ++i) {
                function(queueVector->elements[i], param);
            }
        }
    }
}

void queVecFold(void* queue, FoldFun function, void* accumulator, void* param) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        if (queueVector->front < queueVector->rear) {
            for (uint i = queueVector->front; i <= queueVector->rear; ++i) {
                function(queueVector->elements[i], accumulator, param);
            }
        } else {
            for (uint i = queueVector->front; i < queueVector->size; ++i) {
                function(queueVector->elements[i], accumulator, param);
            }
            for (uint i = 0; i <= queueVector->rear; ++i) {
                function(queueVector->elements[i], accumulator, param);
            }
        }
    }
}

void queueVecPrint(void* queue) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        if (queueVector->front <= queueVector->rear) {
            for(int i = queueVector->front; i <= queueVector->rear; ++i) {
                printf("%d) ", i);
                adtWriteToMonitor(queueVector->elements[i]);
                printf("\n");
            }
        } else {
            for(int i = queueVector->front; i < queueVector->size; ++i) {
                printf("%d) ", i);
                adtWriteToMonitor(queueVector->elements[i]);
                printf("\n");
            }
            for(int i = 0; i <= queueVector->rear; ++i) {
                printf("%d) ", i);
                adtWriteToMonitor(queueVector->elements[i]);
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


QueueType* ConstructQueueVecType() {
    QueueType* type = (QueueType*)malloc(sizeof(QueueType));

    type->construct = queVecConstruct;
    type->destruct = queVecDestruct;

    type->isEmpty = queVecEmpty;
    type->head = queVecHead;
    type->dequeue = queVecDequeue;
    type->headNDequeue = queVecHeadNDequeue;
    type->enqueue = queVecEnqueue;
    //type->clear = queVecClear;

    type->clone = queVecClone;
    type->equal = queVecEqual;
    type->map = queVecMap;
    type->fold = queVecFold;

    return type;
}

void DestructQueueVecType(QueueType* queueType) {
    free(queueType);
}
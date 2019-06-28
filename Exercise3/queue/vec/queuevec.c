/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

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
    return (((QueueVec*)queue)->front == -1); //Se queue->front = -1, di conseguenza lo sarà sicuramente anche queue->rear. Tale situazione si verifica solo nel casp in cui la queue è vuota
}

void queVecDestruct(void* queue) {
    QueueVec* queueVector = queue;
    if(!queVecEmpty(queueVector)) {
        if (queueVector->front <= queueVector->rear) {
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

    if(!queVecEmpty(queue)) {
        return adtClone(queueVector->elements[queueVector->front]);
    } else {
        return NULL;
    }

}

void queVecDequeue(void* queue) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        adtDestruct(queueVector->elements[queueVector->front]);

        if (queueVector->front == queueVector->rear) { //La queue aveva un solo elemento
            queueVector->front = -1;
            queueVector->rear = -1;
        } else queueVector->front = (queueVector->front+1) % queueVector->size;

        if(queueVector->numElem < queueVector->size/4) { //La queue ha troppa memoria libera
            DataObject** newElements = (DataObject**)malloc(sizeof(DataObject*)*queueVector->size/2);

            int newElementsIndex = 0;
            if (queueVector->front <= queueVector->rear) {
                for (uint i = queueVector->front; i <= queueVector->rear; ++i) {
                    newElements[newElementsIndex] = queueVector->elements[i];
                    newElements++;
                }
            } else {
                for (uint i = queueVector->front; i < queueVector->size; ++i) {
                    newElements[newElementsIndex] = queueVector->elements[i];
                    newElements++;
                }
                for (uint i = 0; i <= queueVector->rear; ++i) {
                    newElements[newElementsIndex] = queueVector->elements[i];
                    newElements++;
                }
            }

            free(queueVector->elements);
            queueVector->elements = newElements;
            queueVector->size /= 2;
            queueVector->front = 0;
            queueVector->rear = queueVector->numElem;
            free(queueVector->elements);
        }
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
        if(queueVector->front <= queueVector->rear) {
            while(queueVector->front <= queueVector->rear) {
                newElements[newElementsIndex] = queueVector->elements[queueVector->front];
                newElementsIndex++;
                queueVector->front++;
            }
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
        }

        free(queueVector->elements);
        queueVector->elements = newElements;

        queueVector->front = 0;
        queueVector->rear = queueVector->numElem-1;

        queueVector->size *= 2;
    }

    //Inserimento effettivo dell'elemento  nella queue
    if(queueVector->front == -1) {
        queueVector->front = 0;
    }
    queueVector->rear = (queueVector->rear+1) % queueVector->size;
    queueVector->elements[queueVector->rear] = adtClone(elem);
    queueVector->numElem++;
}

void queVecClear(void* queue) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        if (queueVector->front <= queueVector->rear) {
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

        free(queueVector->elements);
        queueVector->elements = NULL;
        queueVector->size = 0;
        queueVector->numElem = 0;
        queueVector->front = -1;
        queueVector->rear = -1;
    }
}


void* queVecClone(void* queue) {
    QueueVec* queueVector = queue;
    QueueVec* clonedQueue = queVecConstructWSize(queueVector->size);

    if(!queVecEmpty(queueVector)) {
        if (queueVector->front <= queueVector->rear) {
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

    if(firstQueueVector->numElem != secondQueueVector->numElem) { //Controllo che il numero degli elementi delle queue sia lo stesso
        printf("FALSE 1\n");
        return false;
    }

    if(queVecEmpty(firstQueueVector) && queVecEmpty(secondQueueVector)) {
        return true;
    } else {
        int j = secondQueueVector->front;
        if (firstQueueVector->front <= firstQueueVector->rear) {
            for (int i = firstQueueVector->front;
                 i <= firstQueueVector->rear; i++) { //Ciclo su tutti gli elementi della prima queue
                printf("Confronto ");
                adtWriteToMonitor(firstQueueVector->elements[i]);
                printf(" con ");
                adtWriteToMonitor(secondQueueVector->elements[j]);
                printf("\n");
                if (adtCompare(firstQueueVector->elements[i], secondQueueVector->elements[j]) != 0) {
                    return false;
                }
                j++;
                if (j >= secondQueueVector->size) {
                    j = 0;
                }
            }
        } else {
            for (int i = firstQueueVector->front; i < firstQueueVector->size; i++) {
                printf("Confronto ");
                adtWriteToMonitor(firstQueueVector->elements[i]);
                printf(" con ");
                adtWriteToMonitor(secondQueueVector->elements[j]);
                printf("\n");
                if (adtCompare(firstQueueVector->elements[i], secondQueueVector->elements[j]) != 0) {
                    return false;
                }
                j++;
                if (j >= secondQueueVector->size) {
                    j = 0;
                }
            }
            for (int i = 0; i <= firstQueueVector->rear; i++) {
                printf("Confronto ");
                adtWriteToMonitor(firstQueueVector->elements[i]);
                printf(" con ");
                adtWriteToMonitor(secondQueueVector->elements[j]);
                printf("\n");
                if (adtCompare(firstQueueVector->elements[i], secondQueueVector->elements[j]) != 0) {
                    return false;
                }
                j++;
                if (j >= secondQueueVector->size) {
                    j = 0;
                }
            }
        }

        return true;
    }
}

void queVecMap(void* queue, MapFun function, void* param) {
    QueueVec* queueVector = queue;

    if(!queVecEmpty(queueVector)) {
        if (queueVector->front <= queueVector->rear) {
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
        if (queueVector->front <= queueVector->rear) {
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

QueueType* ConstructQueueVecType() {
    QueueType* type = (QueueType*)malloc(sizeof(QueueType));

    type->construct = queVecConstruct;
    type->destruct = queVecDestruct;

    type->isEmpty = queVecEmpty;
    type->head = queVecHead;
    type->dequeue = queVecDequeue;
    type->headNDequeue = queVecHeadNDequeue;
    type->enqueue = queVecEnqueue;
    type->clear = queVecClear;

    type->clone = queVecClone;
    type->equal = queVecEqual;
    type->map = queVecMap;
    type->fold = queVecFold;

    return type;
}

void DestructQueueVecType(QueueType* queueType) {
    free(queueType);
}
/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "queue.h"

void existElem(DataObject* objectToCompare, void * val, void * elem);

/* ************************************************************************** */

QueueObject* queConstruct(QueueType* type) {
    QueueObject * object = (QueueObject *) malloc(sizeof(QueueObject));

    object->type = type;
    object->queue = object->type->construct(type);
    object->numberOfElements = 0;

    return object;
}

void queDestruct(QueueObject* queue) {
    queue->type->destruct(queue->queue);
    free(queue);
}


bool queEmpty(QueueObject* queue) {
    return queue->type->isEmpty(queue->queue);
}

void* queHead(QueueObject* queue) {
    return queue->type->head(queue->queue);
}

void queDequeue(QueueObject* queue) {
    if(queue->numberOfElements > 0) {
        queue->type->dequeue(queue->queue);
        queue->numberOfElements--;
    }
}

void* queHeadNDequeue(QueueObject* queue) {
    if(queue->numberOfElements > 0) {
        queue->numberOfElements--;
        return queue->type->headNDequeue(queue->queue);
    } else {
        return NULL;
    }
}

void queEnqueue(QueueObject* queue, DataObject* object) {
    queue->type->enqueue(queue->queue, object);
    queue->numberOfElements++;
}

void queClear(QueueObject* queue) {
    queue->type->clear(queue->queue);
    queue->numberOfElements = 0;
}


QueueObject* queClone(QueueObject* queue) {
    QueueObject* clonedQueue = (QueueObject*)malloc(sizeof(QueueObject));

    clonedQueue->type = queue->type;
    clonedQueue->queue = queue->type->clone(queue->queue);

    clonedQueue->numberOfElements = queue->numberOfElements;
    return clonedQueue;
}

bool queEqual(QueueObject* firstQueue, QueueObject* secondQueue) {
    if(firstQueue->type == secondQueue->type) {
        return firstQueue->type->equal(firstQueue->queue, secondQueue->queue);
    } else {
        return false;
    }
}

void queMap(QueueObject* queue, MapFun mapFunction, void* param) {
    queue->type->map(queue->queue, mapFunction, param);
}

void queFold(QueueObject* queue, FoldFun foldFunction, void* accumulator, void* param) {
    queue->type->fold(queue->queue, foldFunction, accumulator, param);
}


int queSize(QueueObject* queue) {
    return queue->numberOfElements;
}

bool queExists(QueueObject* queue, DataObject* object) {
    bool* result = (bool*)malloc(sizeof(bool));
    *result = false;
    queFold(queue, existElem, result, object);
    return *result;
}


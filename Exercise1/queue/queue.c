
#include "queue.h"

/* ************************************************************************** */

QueueObject* queConstruct(QueueType* type) {
    QueueObject * object = (QueueObject *) malloc(sizeof(QueueObject));

    object->type = type;
    object->queue = object->type->construct(type);

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
    queue->type->dequeue(queue->queue);
}

void* queHeadNDequeue(QueueObject* queue) {
    return queue->type->headNDequeue(queue->queue);
}

void queEnqueue(QueueObject* queue, DataObject* object) {
    queue->type->enqueue(queue->queue, object);
}

void queClear(QueueObject* queue) {
    queue->type->clear(queue->queue);
}


QueueObject* queClone(QueueObject* queue) {
    QueueObject* clonedQueue = (QueueObject*)malloc(sizeof(QueueObject));

    clonedQueue->type = queue->type;
    clonedQueue->queue = queue->type->clone(queue->queue);

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


int queSize(QueueObject* queue) { //TODO: Da implementare
    /*int* size = (int*)malloc(sizeof(int));
    *size = 0;
    queFold(queue, sizeIncrement, size, NULL);
    return *size;*/
    return -1;
}

bool queExists(QueueObject* queue, DataObject* object) { //TODO: Da implementare
    /*bool* result = (bool*)malloc(sizeof(bool));
    *result = false;
    queFold(queue, existElem, result, object);
    return result;*/
    return false;
}


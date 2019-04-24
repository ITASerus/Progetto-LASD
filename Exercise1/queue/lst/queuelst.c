
#include "queuelst.h"

/* ************************************************************************** */

void* queLstConstruct() {
    QueueLst* obj = (QueueLst*)malloc(sizeof(QueueLst));

    obj->element = NULL;
    obj->next = NULL;

    return obj;
}

void queLstDestruct(void* queue) { //TODO: Da testare
    QueueLst* queueList = queue;

    while(queueList->next != NULL) {
        adtDestruct(queueList->next->element);
        queueList->next = queueList->next->next;
    }

    free(queue);
}


bool queLstEmpty(void* queue) {
    if(((QueueLst*)queue)->next == NULL) {
        return true;
    } else {
        return false;
    }
}

void* queLstHead(void* queue) { //TODO: Assicurati che si deve restituire questo oggetto e non quello all'altro capo
    return adtClone(((QueueLst*)queue)->next->element);
}

void queLstDequeue(void* queue) { //TODO: Da testare
    QueueLst* queueList = queue;

    while(queueList->next->next != NULL) {
        queueList = queueList->next;
    }
    adtDestruct(queueList->next->next->element);
    queueList->next = NULL;
}

void queLstEnqueue(void* queue, void* elem) { //TODO: Uguale a stkLstPush?
    QueueLst* newObj = (QueueLst*)malloc(sizeof(QueueLst));

    newObj->element = adtClone(elem);
    newObj->next = ((QueueLst*)queue)->next;
    ((QueueLst*)queue)->next = newObj;
}

QueueType* ConstructQueueLstType() {
    QueueType* type = (QueueType*)malloc(sizeof(QueueType));

    type->construct = queLstConstruct;
    type->destruct = queLstDestruct;

    type->isEmpty = queLstEmpty;
    type->head = queLstHead;
    type->dequeue = queLstDequeue;
    //type->headNDequeue = queLstHeadNDequeue;
    type->enqueue = queLstEnqueue;
    //type->clear = queLstClear;

    //type->clone = queLstClone;
    //type->equal = queLstEqual;
    //type->map = queLstMap;
    //type->fold = queLstFold;

    return type;
}

void DestructQueueLstType(QueueType* queueType) {

}

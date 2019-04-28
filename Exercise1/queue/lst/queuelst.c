
#include "queuelst.h"

/* ************************************************************************** */

void* queLstConstruct() {
    QueueLst* obj = (QueueLst*)malloc(sizeof(QueueLst));

    QueueNode* firstNode = (QueueNode*)malloc(sizeof(QueueNode));
    firstNode->element = NULL;
    firstNode->next = NULL;

    obj->front = firstNode;
    obj->rear = firstNode;

    return obj;
}

void queLstDestruct(void* queue) {
    QueueLst* queueList = queue;
    QueueNode* nodeToDelete;

    while(queueList->front->next != NULL) {
        nodeToDelete = queueList->front->next;
        queueList->front->next = queueList->front->next->next;
        adtDestruct(nodeToDelete->element);
        free(nodeToDelete);
    }

    free(queue);
}


bool queLstEmpty(void* queue) {
    if(((QueueLst*)queue)->front->next == NULL) {
        return true;
    } else {
        return false;
    }
}

void* queLstHead(void* queue) {
    if(!queLstEmpty(queue)) {
        return adtClone(((QueueLst*)queue)->front->next->element);
    } else {
        return NULL;
    }
}

void queLstDequeue(void* queue) {
    QueueLst* queueList = queue;
    QueueNode* tmp;

    if(!queLstEmpty(queueList)) {
        tmp = queueList->front->next;
        queueList->front->next = queueList->front->next->next;

        adtDestruct(tmp->element);
        free(tmp);

        if(queueList->front->next == NULL) {
            queueList->rear = queueList->front;
        }
    }
}

void* queLstHeadNDequeue(void* queue) {
    QueueLst* queueList = queue;

    if(!queLstEmpty(queueList)) {
        DataObject* dequeuedElement = adtClone(queueList->front->next->element);
        queLstDequeue(queueList);

        return dequeuedElement;
    } else { //La queue è vuota
        return NULL;
    }
}

void queLstEnqueue(void* queue, void* elem) {
    QueueLst* queueList = queue;

    //Creazione del nodo da inserire
    QueueNode* newObj = (QueueNode*)malloc(sizeof(QueueNode));
    newObj->element = adtClone(elem);
    newObj->next = NULL;

    //Posizionamento in coda
    queueList->rear->next = newObj;
    queueList->rear = newObj;
}

void queLstClear(void* queue) {
    QueueLst* queueList = queue;
    QueueNode* nodeToDelete;

    while(queueList->front->next != NULL) {
        nodeToDelete = queueList->front->next;
        queueList->front->next = queueList->front->next->next;
        adtDestruct(nodeToDelete->element);
        free(nodeToDelete);
    }

    queueList->rear = queueList->front;
}

void* queLstClone(void* queue) {
    QueueNode* nodeToClone = ((QueueLst*)queue)->front->next;
    QueueLst* clonedQueue = queLstConstruct();

    while(nodeToClone != NULL) {
        queLstEnqueue(clonedQueue, nodeToClone->element);
        nodeToClone = nodeToClone->next;
    }

    return clonedQueue;
}

void queLstMap(void* queue, MapFun function, void* param) {
    QueueNode* frontNode = ((QueueLst*)queue)->front;

    while(frontNode->next != NULL) {
        function(frontNode->next->element, param);
        frontNode = frontNode->next;
    }
}

void queLstFold(void* queue, FoldFun function, void* accumulator, void* param) {
    QueueNode* frontNode = ((QueueLst*)queue)->front;

    while(frontNode->next != NULL) {
        function(frontNode->next->element, accumulator, param);
        frontNode = frontNode->next;
    }
}

bool queLstEqual(void* firstQueue, void* secondQueue) {
    QueueNode* firstQueueNodeToCompare = ((QueueLst*)firstQueue)->front->next;
    QueueNode* secondQueueNodeToCompre = ((QueueLst*)secondQueue)->front->next;

    while(firstQueueNodeToCompare != NULL && secondQueueNodeToCompre != NULL) {
        if(adtCompare(firstQueueNodeToCompare->element, secondQueueNodeToCompre->element) != 0) {
            return false;
        }
        firstQueueNodeToCompare = firstQueueNodeToCompare->next;
        secondQueueNodeToCompre = secondQueueNodeToCompre->next;
    }

    if((firstQueueNodeToCompare == NULL && secondQueueNodeToCompre != NULL) || (firstQueueNodeToCompare != NULL && secondQueueNodeToCompre == NULL)) {
        return false;
    }

    return true;
}

QueueType* ConstructQueueLstType() {
    QueueType* type = (QueueType*)malloc(sizeof(QueueType));

    type->construct = queLstConstruct;
    type->destruct = queLstDestruct;

    type->isEmpty = queLstEmpty;
    type->head = queLstHead;
    type->dequeue = queLstDequeue;
    type->headNDequeue = queLstHeadNDequeue;
    type->enqueue = queLstEnqueue;
    type->clear = queLstClear;

    type->clone = queLstClone;
    type->equal = queLstEqual;
    type->map = queLstMap;
    type->fold = queLstFold;

    return type;
}

void DestructQueueLstType(QueueType* queueType) {
    free(queueType);
}


#include "queuelst.h"

/* ************************************************************************** */ //TODO: Controlla che al posto di adtDestruct non ci vada queLstDestruct

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
}


bool queLstEmpty(void* queue) {
    if(((QueueLst*)queue)->front->next == NULL) {
        printf("true\n");
        return true;
    } else {
        printf("false\n");
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

    printf("(enqueue)\n");
    if(queueList->front->next == NULL) {
        printf("--- Primo elemento\n");
        queueList->front->next = queueList->rear;
    }
}

void queLstClear(void* queue) {
    printf("OK\n");
    if(!queEmpty(queue)) {
        printf("OK\n");
        QueueNode* nodeToDelete = ((QueueLst*)queue)->front->next;

        while(nodeToDelete != NULL) {
            printf("node != null\n");
            ((QueueLst*)queue)->front->next = nodeToDelete->next;
            printf("Elimino: ");
            adtWriteToMonitor(nodeToDelete->element);
            printf("\n");
            adtDestruct(nodeToDelete->element);
            free(nodeToDelete);
            nodeToDelete = ((QueueLst*)queue)->front->next;
        }

        ((QueueLst*)queue)->rear = ((QueueLst*)queue)->front;
    }
}

void* queLstClone(void* queue) { //TODO: Da implementare
    QueueLst* clonedQueue = queLstConstruct();

    /*QueueLst* sentinelQueueList = queue;
    QueueLst* sentinelClonedQueue = clonedQueue;

    while(sentinelQueueList->next != NULL) {
        QueueLst* newNode = (QueueLst*)malloc(sizeof(QueueLst));
        newNode->element = adtClone(sentinelQueueList->next->element);
        printf("Clono: ");
        adtWriteToMonitor(newNode->element);
        printf("\n");

        sentinelClonedQueue->next = newNode;
        newNode->next = NULL;

        sentinelClonedQueue = sentinelClonedQueue->next;
        sentinelQueueList = sentinelQueueList->next;
    }
*/
    printf("DA IMPLEMENTARE\n");
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
    /*
    QueueLst* firstQueueList = firstQueue;
    QueueLst* secondQueueList = secondQueue;

    while(firstQueueList->next != NULL && secondQueueList->next != NULL) {
        if(adtCompare(firstQueueList->next->element, secondQueueList->next->element) != 0) {
            return false;
        }
        secondQueueList = secondQueueList->next;
        firstQueueList = firstQueueList->next;
    }

    if((firstQueueList->next == NULL && secondQueueList->next != NULL) || (firstQueueList->next != NULL && secondQueueList->next == NULL)) {
        return false;
    }

    return true;
     */
    printf("DA IMPLEMENTARE\n");
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

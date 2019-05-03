
#ifndef QUEUELST_H
#define QUEUELST_H

/* ************************************************************************** */

#include "../queue.h"

/* ************************************************************************** */

typedef struct QueueLst QueueLst;
typedef struct QueueNode QueueNode;

struct QueueLst {
    QueueNode* front;
    QueueNode* rear;
};

struct QueueNode {
    DataObject* element;
    QueueNode* next;
};

/* ************************************************************************** */

QueueType* ConstructQueueLstType();
void DestructQueueLstType(QueueType* queueType);

/* ************************************************************************** */

#endif


#ifndef QUEUELST_H
#define QUEUELST_H

/* ************************************************************************** */

#include "../queue.h"

/* ************************************************************************** */

typedef struct QueueLst QueueLst;
struct QueueLst
{
    DataObject* element;
    QueueLst* next;
};

/* ************************************************************************** */

QueueType* ConstructQueueLstType();
void DestructQueueLstType(QueueType* queueType);

/* ************************************************************************** */

#endif


#ifndef QUEUE_H
#define QUEUE_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

/* ************************************************************************** */

typedef void* (*QueConstruct)(void*);
typedef void (*QueDestruct)(void*);

typedef bool (*QueEmpty)(void*);
typedef void* (*QueHead)(void*);
typedef void (*QueDequeue)(void*);
typedef void* (*QueHeadNDequeue)(void*);
typedef void (*QueEnqueue)(void*, void*);
typedef void (*QueClear)(void*);

typedef void* (*QueClone)(void*);
typedef bool (*QueEqual)(void*, void*);
typedef void (*QueMap)();
typedef void (*QueFold)();

/* ************************************************************************** */

typedef struct QueueType
{
    QueConstruct construct;
    QueDestruct destruct;

    QueEmpty isEmpty;
    QueHead head;
    QueDequeue dequeue;
    QueHeadNDequeue headNDequeue;
    QueEnqueue enqueue;
    QueClear clear;

    QueClone clone;
    QueEqual equal;
    QueMap map;
    QueFold fold;
} QueueType;

typedef struct QueueObject
{
    QueueType* type;
    void* queue;
    int numberOfElements;
} QueueObject;

/* ************************************************************************** */

QueueObject* queConstruct(QueueType* type);
void queDestruct(QueueObject* queue);

bool queEmpty(QueueObject* queue);
void* queHead(QueueObject* queue);
void queDequeue(QueueObject* queue);
void* queHeadNDequeue(QueueObject* queue);
void queEnqueue(QueueObject* queue, DataObject* object);
void queClear(QueueObject* queue);

QueueObject* queClone(QueueObject* queue);
bool queEqual(QueueObject* firstQueue, QueueObject* secondQueue);
void queMap(QueueObject* queue, MapFun mapFunction, void* param);
void queFold(QueueObject* queue, FoldFun foldFunction, void* accumulator, void* param);

int queSize(QueueObject* queue);
bool queExists(QueueObject* queue, DataObject* object);

/* ************************************************************************** */

#endif

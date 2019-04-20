
#ifndef QUEUE_H
#define QUEUE_H

/* ************************************************************************** */

#include "../utility.h"

#include "../adt/adt.h"

/* ************************************************************************** */

typedef struct QueueObject
{
    DataObject** elements; //Array di stringhe
    uint front;
    uint rear;
    uint size; //Dimensione della queue, comprese le locazioni non utilizzate TODO: Cambiare size in altro (dimension?) perchè nelle librerie reali con size indicano il num di elementi presenti
    uint numElem; //TODO: Togliere? Superfluo?
} QueueObject;

/* ************************************************************************** */

QueueObject* queConstruct();
void queDestruct(QueueObject* queue);

bool queEmpty(QueueObject* queue);
DataObject* queHead(QueueObject* queue);
void queDequeue(QueueObject* queue);
DataObject* queHeadNDequeue(QueueObject* queue);
void queEnqueue(QueueObject* queue, DataObject* elem);
int queSize(QueueObject* queue);

QueueObject* queClone(QueueObject* queue);
bool queEqual(QueueObject* firstQueue, QueueObject* secondQueue);
bool queExists(QueueObject* queue, DataObject* elem);
void queMap(QueueObject* queue, MapFun function, void* param);
void queFold(QueueObject* queue, FoldFun function, void* accumulator, void* param);

/* ************************************************************************** */

void queuePrint(QueueObject* queue);
void elemConcat(char* elem, char* accumulator, void* param);

#endif

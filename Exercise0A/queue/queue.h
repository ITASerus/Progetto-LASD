
#ifndef QUEUE_H
#define QUEUE_H

/* ************************************************************************** */

#include "../utility.h"

/* ************************************************************************** */

typedef struct QueueObject {
    char** elements; //Array di stringhe
    uint front;
    uint rear;
    uint size; //Dimensione della queue, comprese le locazioni non utilizzate TODO: Cambiare size in altro (dimension?) perchè nelle librerie reali con size indicano il num di elementi presenti
    uint numElem; //TODO: Togliere? Superfluo?
} QueueObject;

/* ************************************************************************** */

QueueObject* queConstruct();
void queDestruct(QueueObject* queue);

bool queEmpty(QueueObject* queue);
char* queHead(QueueObject* queue);
void queDequeue(QueueObject* queue);
char* queHeadNDequeue(QueueObject* queue);
void queEnqueue(QueueObject* queue, char* elem);
int queSize(QueueObject* queue);

QueueObject* queClone(QueueObject* queue);
bool queEqual(QueueObject* firstQueue, QueueObject* secondQueue);
bool queExists(QueueObject* queue, char* elem);
void queMap(QueueObject* queue, MapFun function, void* param);
void queFold(QueueObject* queue, FoldFun function, void* accumulator, void* param);

/* ************************************************************************** */

void queuePrint(QueueObject* queue);
void elemConcat(char* elem, char* accumulator, void* param);
#endif


#ifndef QUEUEVEC_H
#define QUEUEVEC_H

/* ************************************************************************** */

#include "../queue.h"

/* ************************************************************************** */

typedef struct QueueVec
{
    DataObject** elements; //Array di DataObject
    uint front; //Testa della queue
    uint rear; //Coda della queue
    uint size; //Dimensione della queue, comprese le locazioni non utilizzate
    uint numElem; //Numero di elementi attualmente contenuto nella queue TODO: Togliere? Superfluo?
} QueueVec;

/* ************************************************************************** */

QueueType* ConstructQueueVecType();
void DestructQueueVecType(QueueType* queueType);

/* ************************************************************************** */

#endif

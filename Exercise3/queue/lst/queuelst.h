/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

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

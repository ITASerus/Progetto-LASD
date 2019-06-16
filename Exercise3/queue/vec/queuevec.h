/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

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
    uint numElem; //Numero di elementi attualmente contenuto nella queue
} QueueVec;

/* ************************************************************************** */

QueueType* ConstructQueueVecType();
void DestructQueueVecType(QueueType* queueType);

/* ************************************************************************** */

#endif

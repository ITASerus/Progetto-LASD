/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#ifndef GRAPHITRVERTEX_H
#define GRAPHITRVERTEX_H

/* ************************************************************************** */

#include "graph.h"

/* ************************************************************************** */

typedef struct GraphVertexIterator {
    VertexLst* element;
} GraphVertexIterator;

/* ************************************************************************** */

ITRType* ConstructVertexIterator();
void DestructVertexIterator(ITRType* type);

/* ************************************************************************** */

#endif

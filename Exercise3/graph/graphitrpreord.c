/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "graphitrpreord.h"

#include "../stack/vec/stackvec.h"
#include "../adt/int/adtint.h"

#include "graphitrvertex.h"

/* ************************************************************************** */

void printSupportStruct(GraphPreOrderIterator* iterator) {

    for(int i = 0; i < iterator->maxVertexIndex; i++) {
        printf("NOME: %d - COLOR: %c - ADIACENTI TERMINATI: %d\n", iterator->support[i]->vertexInfo->name, iterator->support[i]->color, itrTerminated(iterator->support[i]->adjacent));
    }
}

void* graphItrPreOrderConstruct(void* type, void* graph) {
    printf("CONSTRUCT\n");
    ITRObject* iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphPreOrderIterator*)malloc(sizeof(GraphPreOrderIterator));

    GraphPreOrderIterator* itr = (GraphPreOrderIterator*)iterator->iterator;

    ITRObject* graphVertexIterator = graphVertices(graph);

    if(!itrTerminated(graphVertexIterator)) { //Il grafo ha almeno un vertice
        printf("Il grafo ha almeno un vertice\n");

        //Allocazione e popolamento struttura di supporto
        itr->support = (SupportInfo**)malloc(sizeof(SupportInfo*) * ((GraphObject*)graph)->numVertex);
        for(int i = 0; i < ((GraphObject*)graph)->numVertex; i++) {
            printf("Analisi vertice %d\n", ((Vertex*)itrElement(graphVertexIterator))->name);
            itr->support[i] = malloc(sizeof(SupportInfo*));

            itr->support[i]->vertexInfo = itrElement(graphVertexIterator);
            itr->support[i]->color = 'b';
            itr->support[i]->adjacent = graphVertexEdges(graph, ((Vertex*)itrElement(graphVertexIterator))->name);
            itrSuccessor(graphVertexIterator);
            printf("Elemento inserito nella struttura di supporto: %d\n", itr->support[i]->vertexInfo->name);
        }
        itr->maxVertexIndex = ((GraphObject*)graph)->numVertex;
        printf("ELEMENTI INSERITI CORRETTAMENTE\n");

        //Inizializzazione primo elemento dell'iteratore
        itr->currentVertexIndex = 0;
        itr->support[0]->color = 'g';
        itr->element = itr->support[0]->vertexInfo;

        //Allocamento ed inizializzazione stack dei predecessori
        itr->stackPredecessor = stkConstruct(ConstructStackVecType());
        DataObject* nameVertex = adtConstruct(ConstructIntDataType());
        adtSetValue(nameVertex, &itr->support[0]->vertexInfo->name);
        stkPush(itr->stackPredecessor, nameVertex);
        adtDestruct(nameVertex);

        printSupportStruct(iterator->iterator);
    } else {
        itr->currentVertexIndex = -1; //Tutti i vertici sono stati analizzati, non essendocene nessuno
    }

    itrDestruct(graphVertexIterator);

    printf("FINE CONSTRUCT\n");
    return iterator;
}

void graphItrPreOrderDestruct(void* iterator) {

}

bool graphItrPreOrderTerminated(void* iterator) {
    return ((GraphPreOrderIterator*)iterator)->currentVertexIndex == -1 ? true : false;
}

void* graphItrPreOrderGetElement(void* iterator) {
    return ((GraphPreOrderIterator*)iterator)->element;
}

void graphItrPreOrderSuccessor(void* iterator) {
    GraphPreOrderIterator* itr = iterator;

    if(itrTerminated(itr->support[itr->currentVertexIndex]->adjacent)) { //Tutti gli adiacenti del vertice attuale sono stati visitati
        itr->support[itr->currentVertexIndex]->color = 'n';

        printf("Risalgo lo stack dei predecessori\n");
        int nextVertex = *(int*)((DataObject*)stkTopNPop(itr->stackPredecessor))->value;
        printf("Continuo ad analizzare gli adiacenti di %d\n", nextVertex);

    } else {
        printf("\nAdiacenti elemento attuale non terminati\n");
        int nextVertexName;
        int nextVertexIndex;

        bool found = false;
        do {
            nextVertexIndex = 0;

            nextVertexName = ((Vertex*)itrElement(itr->support[itr->currentVertexIndex]->adjacent))->name;
            printf("Analisi adiacente %d\n", nextVertexName);

            //Ricerca corrispondenza del vertice nella lista di supporto
            while(itr->support[nextVertexIndex]->vertexInfo->name != nextVertexName) {
                nextVertexIndex++;
            }

            if(itr->support[nextVertexIndex]->color != 'b') { //L'adiacente non va bene (è già stato visitato)
                itrSuccessor(itr->support[itr->currentVertexIndex]->adjacent);
            } else {
                found = true;
            }

        } while (!itrTerminated(itr->support[itr->currentVertexIndex]->adjacent) && !found);

        if(itrTerminated(itr->support[itr->currentVertexIndex]->adjacent)) { //Il vertice corrente non ha adiacenti mai esplorati

        } else { //Vertice adiacente valido trovato
            printf("Adiacente %d valido\n", nextVertexName);

            //Inserimento nello stack del nodo attuale
            DataObject* nameVertex = adtConstruct(ConstructIntDataType());
            adtSetValue(nameVertex, &itr->support[itr->currentVertexIndex]->vertexInfo->name);
            stkPush(itr->stackPredecessor, nameVertex);
            adtDestruct(nameVertex);

            itrSuccessor(itr->support[itr->currentVertexIndex]->adjacent);

            itr->currentVertexIndex = nextVertexIndex;
            itr->element = itr->support[nextVertexIndex]->vertexInfo;
            itr->support[nextVertexIndex]->color = 'g';

            printSupportStruct(itr);
        }
    }
}

ITRType* ConstructGraphPreOrderIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = graphItrPreOrderConstruct;
    type->destruct = graphItrPreOrderDestruct;

    type->terminated = graphItrPreOrderTerminated;

    type->getElement = graphItrPreOrderGetElement;

    type->successor = graphItrPreOrderSuccessor;

    return type;
}

void DestructGraphPreOrderIterator(ITRType* type) {
    free(type);
}


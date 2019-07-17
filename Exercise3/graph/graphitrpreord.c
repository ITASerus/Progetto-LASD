/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "graphitrpreord.h"

#include "../stack/vec/stackvec.h"
#include "../adt/ptr/adtptr.h"

/* ************************************************************************** */

void* graphItrPreOrderConstruct(void* type, void* graph) {
    ITRObject* iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphPreOrderIterator*)malloc(sizeof(GraphPreOrderIterator));

    GraphPreOrderIterator* iter = iterator->iterator;
    GraphObject* graphObject = (GraphObject*)graph;

    // Inizio a creare i 2 stack che mi serviranno
    StackType* stackType = ConstructStackVecType();
    StackObject* stackVertices = stkConstruct(stackType);
    StackObject* stackAdjacents = stkConstruct(stackType);
    iter->ptrType = ConstructPointerDataType();

    // Assegno il grafo, alloco i colori e li inizializzo
    iter->graph = graphObject;

    iter->support = (SupportPre*)malloc(sizeof(SupportPre) * graphObject->numVertex); //TODO: Mettere -1?
    ITRObject* vertexIterator = graphVertices(graphObject);
    for(int i = 0; i < graphObject->numVertex; i++) {
        iter->support[i].name = ((Vertex*)itrElement(vertexIterator))->name;
        iter->support[i].color = 'b';

        itrSuccessor(vertexIterator);
    }
    itrDestruct(vertexIterator);

    // Assegno un valore di default
    iter->currentVertex = NULL;

    // Creo l'iteratore dei vertici e prendo il primo
    iter->verticesIterator = graphVertices(graphObject);
    if(!itrTerminated(iter->verticesIterator)) {
        Vertex* vertex = itrElement(iter->verticesIterator);
        iter->indexVertices = 0;

        iter->currentVertex = vertex;
        iter->support[iter->indexVertices].color = 'g';

        // Costruisco l'iteratore dei suoi adiacenti
        ITRObject* adjIter = graphVertexEdges(graphObject, vertex->name);
        iter->currentAdjIterator = adjIter;
    }

    // Salvo i due stack
    iter->stackAdjacent = stackAdjacents;
    iter->stackVertices = stackVertices;

    return iterator;
}

void graphItrPreOrderDestruct(void* iterator) {
    GraphPreOrderIterator* iter = (GraphPreOrderIterator*) iterator;
    StackType* stackType = iter->stackVertices->type;

    // Distruggo l'iteratore ed il suo tipo
    itrDestruct(iter->verticesIterator);
    itrDestruct(iter->currentAdjIterator);

    // Se ho elementi nello stack degli adiacenti devo distruggerli man mano
    if(!stkEmpty(iter->stackAdjacent)) {
        DataObject* elem = stkTopNPop(iter->stackAdjacent);
        itrDestruct(elem->value);
        adtDestruct(elem);
    }

    stkClear(iter->stackVertices);
    stkDestruct(iter->stackVertices);
    stkDestruct(iter->stackAdjacent);
    DestructStackVecType(stackType);
    DestructPointerDataType(iter->ptrType);
    free(iter->support);
    free(iter);
}

bool graphItrPreOrderTerminated(void* iterator) {
    return !((GraphPreOrderIterator*)iterator)->currentVertex;
}

void* graphItrPreOrderGetElement(void* iterator) {
    return ((GraphPreOrderIterator*)iterator)->currentVertex;
}

void graphItrPreOrderSuccessor(void* iterator) {
    GraphPreOrderIterator* iter = (GraphPreOrderIterator*) iterator;
    DataObject* newPtr = adtConstruct(iter->ptrType);
    bool foundNext = false, foundAdj = true;

    // Itero finché non trovo un elemento
    while(!foundNext) {
        // Cerco un elemento tra gli adiacenti correnti, mi fermo quando lo trovo
        while (!itrTerminated(iter->currentAdjIterator) && !foundNext) {

            Vertex* innerVertex = itrElement(iter->currentAdjIterator);
            int innerIndex = 0;
            while(iter->support[innerIndex].name != innerVertex->name) {
                innerIndex++;
            }

            itrSuccessor(iter->currentAdjIterator);

            // Se il vertice è bianco lo salvo, salvo la lista adiacenti ed esco dal ciclo
            if (iter->support[innerIndex].color == 'b') {
                adtSetValue(newPtr, &iter->currentVertex->name);
                stkPush(iter->stackVertices, newPtr);

                adtSetValue(newPtr, iter->currentAdjIterator);
                stkPush(iter->stackAdjacent, newPtr);

                iter->currentVertex = innerVertex;
                iter->support[innerIndex].color = 'g';

                ITRObject *adjIter = graphVertexEdges(iter->graph, innerVertex->name);
                iter->currentAdjIterator = adjIter;

                // TOGLI POST ORDER
                foundNext = true;
            }
        }

        // Se arrivo qui l'iteratore è terminato, se foundNext è falso verifico se posso prendere dallo stack
        if ((!stkEmpty(iter->stackVertices) && !foundNext)) {
            DataObject *tmp1 = stkTopNPop(iter->stackVertices);
            DataObject *tmp2 = stkTopNPop(iter->stackAdjacent);

            iter->currentVertex = adtGetValue(tmp1); //CONTROLLA QUA
            iter->currentAdjIterator = adtGetValue(tmp2);

            adtDestruct(tmp1);
            adtDestruct(tmp2);
        }
        else if (stkEmpty(iter->stackVertices) || !foundNext){
            foundAdj = false;
            foundNext = true;
            iter->currentVertex = NULL;
        }
    }

    // Non ho trovato il nuovo vertice e lo cerco nell'iteratore dei vertici
    if(!foundAdj) {
        foundNext = false;

        while(!itrTerminated(iter->verticesIterator) && !foundNext) {

            Vertex* vertex = itrElement(iter->verticesIterator);
            int index = 0;
            while(iter->support[index].name != vertex->name) {
                index++;
            }

            itrSuccessor(iter->verticesIterator);

            // Se il vertice è bianco lo salvo, salvo la lista adiacenti ed esco dal ciclo
            if (iter->support[index].color == 'b') {
                iter->currentVertex = vertex;
                iter->support[index].color = 'g';

                ITRObject *adjIter = graphVertexEdges(iter->graph, vertex->name);
                iter->currentAdjIterator = adjIter;

                foundNext = true;
            }
        }
    }

    if(!foundNext) {
        iter->currentVertex = NULL;
    }

    adtDestruct(newPtr);
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


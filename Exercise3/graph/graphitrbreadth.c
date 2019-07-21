
#include "graphitrbreadth.h"

#include "../queue/vec/queuevec.h"
#include "../adt/int/adtint.h"
/* ************************************************************************** */

void* graphItrBreadthConstruct(void* type, void* graph) {
    ITRObject* iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphBreadthIterator*) malloc(sizeof(GraphBreadthIterator));

    GraphBreadthIterator* iter = iterator->iterator;
    GraphObject* graphObject = (GraphObject*)graph;

    QueueType* queueType = ConstructQueueVecType();

    iter->graph = (GraphObject*)graph;
    iter->queue = queConstruct(queueType);
    iter->intType = ConstructIntDataType();

    // Inizializzo tutti i colori a 'b'
    iter->support = (SupportBreadth*)malloc(sizeof(SupportBreadth) * graphObject->numVertex); //TODO: Mettere -1?
    ITRObject* vertexIterator = graphVertices(graphObject);
    for(int i = 0; i < graphObject->numVertex; i++) {
        iter->support[i].name = ((Vertex*)itrElement(vertexIterator))->name;
        iter->support[i].color = 'b';

        itrSuccessor(vertexIterator);
    }
    itrDestruct(vertexIterator);

    DataObject* newElem = adtConstruct(iter->intType);

    /* Se il grafo ha almeno un elemento, è possibile fare la BST, utilizzo vertices
     * in quanto non so la posizione del primo vertice nell'array dei vertici */
    iter->verticesIterator = graphVertices(graph);
    if(!itrTerminated(iter->verticesIterator)) {
        Vertex* vertex = itrElement(iter->verticesIterator);

        iter->currentVertex = vertex;
        iter->support[0].color = 'g';

        // Scorro tutti gli adiacenti di questo vertice e li accodo se bianchi
        ITRObject* adjIter = graphVertexEdges(iter->graph, vertex->name);
        while(!itrTerminated(adjIter)) {
            Vertex* innerVertex = itrElement(adjIter);
            uint innerId = 0;
            while(iter->support[innerId].name != innerVertex->name) {
                innerId++;
            }

            if(iter->support[innerId].color == 'b') {
                adtSetValue(newElem, &innerId);
                queEnqueue(iter->queue, newElem);
                iter->support[innerId].color = 'g';
            }
            itrSuccessor(adjIter);
        }
        itrDestruct(adjIter);
        itrSuccessor(iter->verticesIterator);
    }
    else {
        iter->currentVertex = NULL;
    }

    adtDestruct(newElem);
    return iterator;
}

void graphItrBreadthDestruct(void* iterator) {
    GraphBreadthIterator* iter = (GraphBreadthIterator*) iterator;
    QueueType* type = iter->queue->type;

    itrDestruct(iter->verticesIterator);
    queDestruct(iter->queue);
    DestructQueueVecType(type);
    DestructIntDataType(iter->intType);
    free(iter->support);
    free(iter);
}

bool graphItrBreadthTerminated(void* iterator) {
    GraphBreadthIterator* iter = (GraphBreadthIterator*) iterator;

    // Ritorno true solo se non ho un corrente e la coda è vuota
    return !iter->currentVertex && queEmpty(iter->queue);
}

void* graphItrBreadthGetElement(void* iterator) {
    return ((GraphBreadthIterator*) iterator)->currentVertex;
}

void graphItrBreadthSuccessor(void* iterator) {
    GraphBreadthIterator* iter = (GraphBreadthIterator*) iterator;
    DataObject* newElem = adtConstruct(iter->intType);
    bool found = false;

    // Ciclo finché non trovo un elemento
    while(!found) {

        // Controllo se posso prenderlo dalla coda
        if(!queEmpty(iter->queue)) {
            // Prendo il vertice dalla coda e lo assegno a currentVertex
            DataObject* name = queHeadNDequeue(iter->queue);
            uint currIndex = *(int*)adtGetValue(name);
            //TODO: Problema qua intorno
            Vertex* vertex = itrElement(iter->verticesIterator);
            iter->currentVertex = vertex;
            found = true;

            // Imposto che il suo colore è ora nero, siccome l'ho raggiunto
            iter->support[currIndex].color = 'n';

            // Scorro tutti gli adiacenti di questo vertice e li accodo se bianchi
            ITRObject* adjIter = graphVertexEdges(iter->graph, vertex->name);
            while(!itrTerminated(adjIter)) {
                Vertex* innerVertex = itrElement(adjIter);
                int innerId = 0;
                while(iter->support[innerId].name != innerVertex->name) {
                    innerId++;
                }

                if(iter->support[innerId].color == 'b') {
                    adtSetValue(newElem, &innerId);
                    queEnqueue(iter->queue, newElem);
                    iter->support[innerId].color = 'g';
                }
                itrSuccessor(adjIter);
            }
            itrDestruct(adjIter);
            adtDestruct(name);
        }
            // Se non posso prenderlo dalla coda, verifico se ho vertici bianchi nel grafo
        else if(!itrTerminated(iter->verticesIterator)) {

            // Ciclo finché non termino i vertici e li incodo
            while(!itrTerminated(iter->verticesIterator)) {
                Vertex* innerVertex = itrElement(iter->verticesIterator);
                int index = 0;
                while(iter->support[index].name != innerVertex->name) {
                    index++;
                }

                if(iter->support[index].color == 'b') {
                    adtSetValue(newElem, &index);
                    queEnqueue(iter->queue, newElem);
                    iter->support[index].color = 'g';
                }

                itrSuccessor(iter->verticesIterator);
            }
        }
            /* Se arrivo qui allora non ho vertici bianchi né in coda, posso settare
             * currentVertex a NULL in modo da realizzare la condizione di terminazione */
        else {
            iter->currentVertex = NULL;
            found = true;
        }
    }

    adtDestruct(newElem);
}

ITRType* ConstructGraphBreadthIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = graphItrBreadthConstruct;
    type->destruct = graphItrBreadthDestruct;

    type->terminated = graphItrBreadthTerminated;

    type->getElement = graphItrBreadthGetElement;

    type->successor = graphItrBreadthSuccessor;

    return type;
}

void DestructGraphBreadthIterator(ITRType* type) {
    free(type);
}


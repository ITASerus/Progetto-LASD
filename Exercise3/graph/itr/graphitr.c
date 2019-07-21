/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "../../bst/bst.h"
#include "graphitr.h"

#include "../../queue/queue.h"
#include "../../queue/vec/queuevec.h"

#include "../../adt/adt.h"
#include "../../adt/int/adtint.h"

/* ************************************************************************** */


/**
 * Verifica iterativamente se due grafi sono uguali, per vertici e archi, a prescindere dalla loro implementazione
 * @param firstGraph Riferimento al primo grafo
 * @param firstGraphRepresentation Riferimento al tipo di rappresentazione del primo grafo
 * @param secondGraph Riferimento al secondo grafo
 * @param secondGraphRepresentation Riferimento al tipo di rappresentazione del secondo grafo
 * @return TRUE se i due grafi sono uguali, FALSE altrimenti
 */
bool itrGraphEqual(void* firstGraph, void* firstGraphRepresentation, void* secondGraph, void* secondGraphRepresentation) {
    ITRObject* firstGraphVertexIterator = ((GraphRepresentation*)firstGraphRepresentation)->graphVertices(firstGraph);
    ITRObject* secondGraphVertexIterator = ((GraphRepresentation*)secondGraphRepresentation)->graphVertices(secondGraph);
    ITRObject* firstGraphAdjacentIterator;
    ITRObject* secondGraphAdjacentIterator;

    while(!itrTerminated(firstGraphVertexIterator) && !itrTerminated(secondGraphVertexIterator) &&
            ((Vertex*)itrElement(firstGraphVertexIterator))->name ==  ((Vertex*)itrElement(secondGraphVertexIterator))->name &&
            adtCompare(((Vertex*)itrElement(firstGraphVertexIterator))->label, ((Vertex*)itrElement(secondGraphVertexIterator))->label) == 0 ) {

        firstGraphAdjacentIterator = ((GraphRepresentation*)firstGraphRepresentation)->graphVertexEdges
                (firstGraph, ((Vertex*)itrElement(firstGraphVertexIterator))->name);
        secondGraphAdjacentIterator = ((GraphRepresentation*)secondGraphRepresentation)->graphVertexEdges
                (secondGraph, ((Vertex*)itrElement(secondGraphVertexIterator))->name);

        while(!itrTerminated(firstGraphAdjacentIterator) && !itrTerminated(secondGraphAdjacentIterator) &&
              ((Vertex*)itrElement(firstGraphAdjacentIterator))->name ==  ((Vertex*)itrElement(secondGraphAdjacentIterator))->name &&
              adtCompare(((Vertex*)itrElement(firstGraphAdjacentIterator))->label, ((Vertex*)itrElement(secondGraphAdjacentIterator))->label) == 0 ) {

            itrSuccessor(firstGraphAdjacentIterator);
            itrSuccessor(secondGraphAdjacentIterator);
        }

        if(!(itrTerminated(firstGraphAdjacentIterator) && itrTerminated(secondGraphAdjacentIterator))) {
            itrDestruct(firstGraphAdjacentIterator);
            itrDestruct(secondGraphAdjacentIterator);
            return false;
        }

        itrDestruct(firstGraphAdjacentIterator);
        itrDestruct(secondGraphAdjacentIterator);

        itrSuccessor(firstGraphVertexIterator);
        itrSuccessor(secondGraphVertexIterator);
    }

    if(!(itrTerminated(firstGraphVertexIterator) && itrTerminated(secondGraphVertexIterator))) {
        itrDestruct(firstGraphVertexIterator);
        itrDestruct(secondGraphVertexIterator);
        return false;
    }

    itrDestruct(firstGraphVertexIterator);
    itrDestruct(secondGraphVertexIterator);
    return true;
}

int itrGraphShortestPath(void* graph, int numVertex, void* graphRepresentation, int start, int arrival) {
    GraphObject* graphObject = (GraphObject*) graph;
    int shortestPath = -1;

    // Mi scorro i vari vertici per verificare che esistano entrambi
    ITRObject* vertices = ((GraphRepresentation*)graphRepresentation)->graphVertices(graph);
    uint startId = -1, arrivalId = -1;
    bool foundStart = false, foundArrival = false;

    while(!itrTerminated(vertices) && (!foundStart || !foundArrival)) {
        Vertex* vertex = itrElement(vertices);
        ITRObject* graphIterator = ((GraphRepresentation*)graphRepresentation)->graphVertices(graph);
        int index = 0;
        while(!itrTerminated(graphIterator) && ((Vertex*)itrElement(graphIterator))->name != vertex->name) {
            index++;
            itrSuccessor(graphIterator);
        }
        itrDestruct(graphIterator);

        // Se start o arrival esistono, allora mi prendo il loro index
        if(start == vertex->name) {
            startId = index;
            foundStart = true;
        }

        if(arrival == vertex->name) {
            arrivalId = index;
            foundArrival = true;
        }
        itrSuccessor(vertices);
    }
    itrDestruct(vertices);

    /* Se entrambi sono falsi, oppure solo uno dei due è falso, ritorno -1 */
    if((!foundStart && !foundArrival) || foundStart != foundArrival) {
        shortestPath = -1;
    }
        // Altrimenti se sono lo stesso vertice il percorso è 0
    else if(startId == arrivalId) {
        shortestPath = 0;
    }
        // Altrimenti potrebbe esistere un percorso
    else {

        // Dichiaro l'array dei colori, array delle distanze e la coda
        char* color = (char*) malloc(sizeof(char) * numVertex);
        int* distance = (int*) malloc(sizeof(int) * numVertex);
        DataType* intType = ConstructIntDataType();
        DataObject* newElem = adtConstruct(intType);
        QueueType* queueType = ConstructQueueVecType();
        QueueObject* queue = queConstruct(queueType);

        // Inizializzo i colori a bianco e le distanze a 0
        for (int i = 0; i < graphObject->numVertex; ++i) {
            color[i] = 'b';
            distance[i] = -1;
        }

        /* Imposto che il colore grigio e la distanza 0 del nodo iniziale
         * e lo accodo */
        color[startId] = 'g';
        distance[startId] = 0;
        adtSetValue(newElem, &startId);
        queEnqueue(queue, newElem);

        // Effettuo la BFS, la interrompo se trovo l'elemento
        bool found = false;
        while(!queEmpty(queue) && !found) {
            DataObject *name = queHeadNDequeue(queue);
            uint currIndex = *(int*)adtGetValue(name); //TODO??

            ITRObject* graphIterator = ((GraphRepresentation*)graphRepresentation)->graphVertices(graph);
            int index = 0;
            while(!itrTerminated(graphIterator) && index != currIndex) {
                index++;
                itrSuccessor(graphIterator);
            }
            Vertex* vertex = itrElement(graphIterator);
            itrDestruct(graphIterator);

            color[currIndex] = 'n';

            // Scorro tutti gli adiacenti di questo vertice e li accodo se bianchi
            ITRObject *adjIter = ((GraphRepresentation*)graphRepresentation)->graphVertexEdges(graph, vertex->name);
            while (!itrTerminated(adjIter) && !found) {
                vertex = itrElement(adjIter);
                graphIterator = ((GraphRepresentation*)graphRepresentation)->graphVertices(graph);
                uint innerId = 0;
                while(!itrTerminated(graphIterator) && ((Vertex*)itrElement(graphIterator))->name != vertex->name) {
                    innerId++;
                    itrSuccessor(graphIterator);
                }
                itrDestruct(graphIterator);

                if (color[innerId] == 'b') {
                    adtSetValue(newElem, &innerId);
                    queEnqueue(queue, newElem);
                    color[innerId] = 'g';
                    distance[innerId] = distance[currIndex] + 1;

                    if(innerId == arrivalId) {
                        shortestPath = distance[arrivalId];
                        found = true;
                    }
                }
                itrSuccessor(adjIter);
            }
            itrDestruct(adjIter);

            adtDestruct(name);
        }

        queClear(queue);
        queDestruct(queue);
        DestructQueueVecType(queueType);
        adtDestruct(newElem);
        DestructIntDataType(intType);
        free(color);
        free(distance);
    }

    return shortestPath;
}


void itrGraphPreOrderMap(void* graph, void* graphRepresentation, MapFun mapFunction, void* parameter) {
    ITRType* preOrderType = ConstructGraphPreOrderIterator();
    ITRObject* iter = itrConstruct(preOrderType, graph);

    while(!itrTerminated(iter)) {
        Vertex* vertex = itrElement(iter);
        printf("Nome: %d - Value: ", vertex->name);
        mapFunction(vertex->label, parameter);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphBreadthIterator(preOrderType);
}

void itrGraphPostOrderMap(void* graph, void* graphRepresentation, MapFun mapFunction, void* parameter) {
    ITRType* preOrderType = ConstructGraphPostOrderIterator();
    ITRObject* iter = itrConstruct(preOrderType, graph);

    while(!itrTerminated(iter)) {
        Vertex* vertex = itrElement(iter);
        printf("Nome: %d - Value: ", vertex->name);
        mapFunction(vertex->label, parameter);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphBreadthIterator(preOrderType);
}

void itrGraphBreadthMap(void* graph, void* graphRepresentation, MapFun mapFunction, void* parameter) {
    ITRType* breadthType = ConstructGraphBreadthIterator();
    ITRObject* iter = itrConstruct(breadthType, graph);

    while(!itrTerminated(iter)) {
        Vertex* vertex = itrElement(iter);
        printf("Nome: %d - Value: ", vertex->name);
        mapFunction(vertex->label, parameter);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphBreadthIterator(breadthType);
}


void itrGraphPreOrderFold(void* graph, void* graphRepresentation, FoldFun foldFunction, void* accumulator, void* parameter) {
    ITRType* preOrderType = ConstructGraphPreOrderIterator();
    ITRObject* iter = itrConstruct(preOrderType, graph);

    while(!itrTerminated(iter)) {
        DataObject* dataObject = itrElement(iter);
        foldFunction(dataObject, accumulator, parameter);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphBreadthIterator(preOrderType);
}

void itrGraphPostOrderFold(void* graph, void* graphRepresentation, FoldFun foldFunction, void* accumulator, void* parameter) {
    ITRType* preOrderType = ConstructGraphPostOrderIterator();
    ITRObject* iter = itrConstruct(preOrderType, graph);

    while(!itrTerminated(iter)) {
        DataObject* dataObject = itrElement(iter);
        foldFunction(dataObject, accumulator, parameter);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphBreadthIterator(preOrderType);
}

void itrGraphBreadthFold(void* graph, void* graphRepresentation, FoldFun foldFunction, void* accumulator, void* parameter) {
    ITRType* breadthType = ConstructGraphBreadthIterator();
    ITRObject* iter = itrConstruct(breadthType, graph);

    while(!itrTerminated(iter)) {
        DataObject* dataObject = itrElement(iter);
        foldFunction(dataObject, accumulator, parameter);
        itrSuccessor(iter);
    }
    itrDestruct(iter);
    DestructGraphBreadthIterator(breadthType);
}


void ConstructGraphIterative(GraphType* type) {
    type->graphEqual = itrGraphEqual;

    type->graphShortestPath = itrGraphShortestPath;

    type->graphPreOrderMap = itrGraphPreOrderMap;
    type->graphPostOrderMap = itrGraphPostOrderMap;
    type->graphBreadthMap = itrGraphBreadthMap;

    type->graphPreOrderFold = itrGraphPreOrderFold;
    type->graphPostOrderFold = itrGraphPostOrderFold;
    type->graphBreadthFold = itrGraphBreadthFold;
}

void DestructGraphIterative() {

}

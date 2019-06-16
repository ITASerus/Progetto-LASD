/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "graphrec.h"

/* ************************************************************************** */

/**
 * Verifica ricorsivamente, tramtite due iteratori, se due grafi hanno gli stessi archi
 * @param firstGraphAdjacent Iteratore sugli adiacenti del primo grafo
 * @param secondGraphAdjacent Iteratore sugli adiacenti del secondo grafo
 * @return TRUE se gli adiacenti dei due grafi sono uguali, FALSE altrimenti
 */
bool checkAdjacent(ITRObject* firstGraphAdjacent, ITRObject* secondGraphAdjacent) {
    if(!itrTerminated(firstGraphAdjacent) && !itrTerminated(secondGraphAdjacent)) {
        if( ((Vertex*)itrElement(firstGraphAdjacent))->name == ((Vertex*)itrElement(secondGraphAdjacent))->name &&
            adtCompare(((Vertex*)itrElement(firstGraphAdjacent))->label, ((Vertex*)itrElement(secondGraphAdjacent))->label) == 0) {
            itrSuccessor(firstGraphAdjacent);
            itrSuccessor(secondGraphAdjacent);
            return checkAdjacent(firstGraphAdjacent, secondGraphAdjacent);
        }
    }

    if(itrTerminated(firstGraphAdjacent) && itrTerminated(secondGraphAdjacent)) {
        return true;
    } else {
        return false;
    }
}

/**
 * Supporto alla funzione 'recGraphEqual' che ricorsivamente verifica se due grafi hanno i vertici uguali e, per ogni vertice, controlla se gli archi sono uguali richiamanto la funzione 'checkAdjacent'
 * @param firstGraph Riferimento al primo grafo
 * @param firstGraphRepresentation Riferimento al tipo di rappresentazione del primo grafo
 * @param firstGraphVertices Iteratore sui vertici del primo grafo
 * @param secondGraph Riferimento al secondo grafo
 * @param secondGraphRepresentation Riferimento al tipo di rappresentazione del secondo grafo
 * @param secondGraphVertices Iteratore sui vertici del secondo grafo
 * @return TRUE se i due grafi sono uguali, FALSE altrimenti
 */
bool checkVertices(void* firstGraph, GraphRepresentation* firstGraphRepresentation, ITRObject* firstGraphVertices, void* secondGraph, GraphRepresentation* secondGraphRepresentation, ITRObject* secondGraphVertices) {
    if(!itrTerminated(firstGraphVertices) && !itrTerminated(secondGraphVertices)) {
        if( ((Vertex*)itrElement(firstGraphVertices))->name == ((Vertex*)itrElement(secondGraphVertices))->name &&
        adtCompare(((Vertex*)itrElement(firstGraphVertices))->label, ((Vertex*)itrElement(secondGraphVertices))->label) == 0) {

            //Controllo adiacenti
            ITRObject* firstGraphAdjacentIterator = firstGraphRepresentation->graphVertexEdges
                                                    (firstGraph, ((Vertex*)itrElement(firstGraphVertices))->name);
            ITRObject* secondGraphAdjacentIterator = secondGraphRepresentation->graphVertexEdges
                                                    (secondGraph, ((Vertex*)itrElement(secondGraphVertices))->name);

            if(!checkAdjacent(firstGraphAdjacentIterator, secondGraphAdjacentIterator)) {
                return false;
            }

            itrDestruct(firstGraphAdjacentIterator);
            itrDestruct(secondGraphAdjacentIterator);

            itrSuccessor(firstGraphVertices);
            itrSuccessor(secondGraphVertices);
            return checkVertices(firstGraph, firstGraphRepresentation, firstGraphVertices,
                                 secondGraph, secondGraphRepresentation, secondGraphVertices);
        }
    }

    if(itrTerminated(firstGraphVertices) && itrTerminated(secondGraphVertices)) {
        return true;
    } else {
        return false;
    }
}

/**
 * Verifica ricorsivamente se due grafi sono uguali, per vertici e archi, a prescindere dalla loro implementazione, ric
 * @param firstGraph Riferimento al primo grafo
 * @param firstGraphRepresentation Riferimento al tipo di rappresentazione del primo grafo
 * @param secondGraph Riferimento al secondo grafo
 * @param secondGraphRepresentation Riferimento al tipo di rappresentazione del secondo grafo
 * @return TRUE se i due grafi sono uguali, FALSE altrimenti
 */
bool recGraphEqual(void* firstGraph, void* firstGraphRepresentation, void* secondGraph, void* secondGraphRepresentation) {
    ITRObject* firstGraphVertexIterator = ((GraphRepresentation*)firstGraphRepresentation)->graphVertices(firstGraph);
    ITRObject* secondGraphVertexIterator = ((GraphRepresentation*)secondGraphRepresentation)->graphVertices(secondGraph);

    bool result = checkVertices(firstGraph, firstGraphRepresentation, firstGraphVertexIterator, secondGraph, secondGraphRepresentation, secondGraphVertexIterator);

    itrDestruct(firstGraphVertexIterator);
    itrDestruct(secondGraphVertexIterator);

    return result;
}

int recGraphShortestPath(void* graph, int numVertex, void* graphRepresentation, int firstName, int secondName) {
    printf("Da implementare");
    return 0;
}


void _recGraphPreOrderMap(ITRObject* iterator, MapFun mapFunction, void* parameter) {
    if(!itrTerminated(iterator)) {
        mapFunction(((Vertex*)itrElement(iterator))->label, parameter);
        itrSuccessor(iterator);
        _recGraphPreOrderMap(iterator, mapFunction, parameter);
    }
}

void recGraphPreOrderMap(void* graph, void* graphRepresentation, MapFun mapFunction, void* parameter) {
    ITRObject* vertexIterator = ((GraphRepresentation*)graphRepresentation)->graphVertices(graph);

    _recGraphPreOrderMap(vertexIterator, mapFunction, parameter);

    itrDestruct(vertexIterator);
}

void _recGraphPostOrderMap(ITRObject* iterator, MapFun mapFunction, void* parameter) {
    if(!itrTerminated(iterator)) {
        itrSuccessor(iterator);
        _recGraphPreOrderMap(iterator, mapFunction, parameter);
        mapFunction(((Vertex*)itrElement(iterator))->label, parameter);
    }
}

void recGraphPostOrderMap(void* graph, void* graphRepresentation, MapFun mapFunction, void* parameter) {
    ITRObject* vertexIterator = ((GraphRepresentation*)graphRepresentation)->graphVertices(graph);

    _recGraphPostOrderMap(vertexIterator, mapFunction, parameter);

    itrDestruct(vertexIterator);
}

void recGraphBreadthMap(void* graph, void* graphRepresentation, MapFun mapFunction, void* parameter) {
    printf("Da implementare\n");
}


void _recGraphPreOrderFold(ITRObject* iterator, FoldFun foldFunction, void* accumulator, void* parameter) {
    if(!itrTerminated(iterator)) {
        foldFunction(((Vertex*)itrElement(iterator))->label, accumulator, parameter);
        itrSuccessor(iterator);
        _recGraphPreOrderFold(iterator, foldFunction, accumulator, parameter);
    }
}

void recGraphPreOrderFold(void* graph, void* graphRepresentation, FoldFun foldFunction, void* accumulator, void* parameter) {
    ITRObject* vertexIterator = ((GraphRepresentation*)graphRepresentation)->graphVertices(graph);

    _recGraphPreOrderFold(vertexIterator, foldFunction, accumulator, parameter);

    itrDestruct(vertexIterator);
}

void recGraphPostOrderFold(void* graph, void* graphRepresentation, FoldFun foldFunction, void* accumulator, void* parameter) {
    printf("Da implementare\n");
}

void recGraphBreadthFold(void* graph, void* graphRepresentation, FoldFun foldFunction, void* accumulator, void* parameter) {
    printf("Da implementare\n");
}


void ConstructGraphRecursive(GraphType* type) {
    type->graphEqual = recGraphEqual;

    type->graphShortestPath = recGraphShortestPath;

    type->graphPreOrderMap = recGraphPreOrderMap;
    type->graphPostOrderMap = recGraphPostOrderMap;
    type->graphBreadthMap = recGraphBreadthMap;

    type->graphPreOrderFold = recGraphPreOrderFold;
    type->graphPostOrderFold = recGraphPostOrderFold;
    type->graphBreadthFold = recGraphBreadthFold;
}

void DestructGraphRecursive() {

}
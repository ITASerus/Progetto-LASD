
#include <bst/bst.h>
#include "graphitr.h"

#include "queue.h"
#include "queuevec.h"

#include "adt.h"
#include "adtint.h"

/* ************************************************************************** */

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

int itrShortestPath(void* graph, int numVertex, void* graphRepresentation, int firstName, int secondName) {

    //Inizializzo strutture di supporto
    int shortestPath = -1;

    int* vectorIndex = (int*)malloc(sizeof(int) * numVertex); //Vettore di vertici per corrispondenza vertice - indice
    char* color = (char*)malloc(sizeof(char) * numVertex); //Vettore di colori di ogni vertice
    int* distance = (int*)malloc(sizeof(int) * numVertex);

    for(int i = 0; i < numVertex; i++) {
        color[i] = 'b';
        distance[i] = -1;
    }

    QueueType* queType = ConstructQueueVecType();
    QueueObject* queue = queConstruct(queType);

    ITRObject* itrVertices = ((GraphRepresentation*)graphRepresentation)->graphVertices(graph);

    int i = 0;
    while(!itrTerminated(itrVertices)) {
        vectorIndex[i] = ((Vertex*)itrElement(itrVertices))->name;
        itrSuccessor(itrVertices);
        i++;
    }

    DataType* dataType = ConstructIntDataType();
    DataObject* dataObject = adtConstruct(dataType);
    adtSetValue(dataObject, &firstName);

    queEnqueue(queue, dataObject);

    bool found = false;
    int currentIndex = 0;
    while(!queEmpty(queue) && !found) {
        DataObject* name = queHeadNDequeue(queue);
        int* currentName = adtGetValue(name);

        currentIndex = 0;
        while(vectorIndex[currentIndex] != *currentName) {
            currentIndex++;
        }
        color[currentIndex] = 'n';

        //Scorro tutti gli adiacenti di questo vertice e li accodo se bianchi
        ITRObject* itrAdjacent = ((GraphRepresentation*)graphRepresentation)->graphVertexEdges(graph, *currentName);
        while(!itrTerminated(itrAdjacent) && !found) {

            int currentAdjacent = ((Vertex*)itrElement(itrAdjacent))->name;

            //Ricerco corrispondenza l'indice corrispondente al vertice
            int j = 0;
            while(vectorIndex[j] != currentAdjacent) {
                j++;
            }

            if(color[j] == 'b') {
                adtSetValue(dataObject, &vectorIndex[j]);
                queEnqueue(queue, dataObject);
                color[j] = 'g';
                distance[j] = distance[currentIndex]+1; //Incremento la distanza

                if(vectorIndex[j] == secondName) {
                    shortestPath = distance[j];
                    found = true;
                } else {
                }
            }
            itrSuccessor(itrAdjacent);
        }
    }

    return shortestPath;
}

void ConstructGraphIterative(GraphType* type) {
    type->graphEqual = itrGraphEqual;
    type->graphShortestPath = itrShortestPath;
}

void DestructGraphIterative() {

}

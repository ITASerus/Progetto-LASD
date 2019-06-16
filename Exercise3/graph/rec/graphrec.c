
#include "graphrec.h"

/* ************************************************************************** */

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

bool recGraphEqual(void* firstGraph, void* firstGraphRepresentation, void* secondGraph, void* secondGraphRepresentation) {
    ITRObject* firstGraphVertexIterator = ((GraphRepresentation*)firstGraphRepresentation)->graphVertices(firstGraph);
    ITRObject* secondGraphVertexIterator = ((GraphRepresentation*)secondGraphRepresentation)->graphVertices(secondGraph);

    bool result = checkVertices(firstGraph, firstGraphRepresentation, firstGraphVertexIterator, secondGraph, secondGraphRepresentation, secondGraphVertexIterator);

    itrDestruct(firstGraphVertexIterator);
    itrDestruct(secondGraphVertexIterator);

    return result;
}

void ConstructGraphRecursive(GraphType* type) {
    type->graphEqual = recGraphEqual;
}

void DestructGraphRecursive() { //TODO: dA IMPLEMENTARE

}
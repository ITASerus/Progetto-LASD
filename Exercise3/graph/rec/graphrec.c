
#include "graphrec.h"

/* ************************************************************************** */

bool checkAdjacent(ITRObject* firstGraphAdjacent, ITRObject* secondGraphAdjacent) {
    if (!itrTerminated(firstGraphAdjacent)) {
        if (!itrTerminated(secondGraphAdjacent)) {
            if (((Vertex *) itrElement(firstGraphAdjacent))->name ==
                ((Vertex *) itrElement(secondGraphAdjacent))->name) {
                printf("NOMI ADIACENTI UGUALI\n");

                if (((Vertex *) itrElement(firstGraphAdjacent))->label ==
                    ((Vertex *) itrElement(secondGraphAdjacent))->label) {
                    printf("VALORI ADIACENTI UGUALI\n");

                    itrSuccessor(firstGraphAdjacent);
                    itrSuccessor(secondGraphAdjacent);
                    return checkAdjacent(firstGraphAdjacent, secondGraphAdjacent);
                }
            }

            if (itrTerminated(firstGraphAdjacent) && itrTerminated(secondGraphAdjacent)) {
                return true;
            }
        }
    }

    return false;
}

bool recGraphEqual(void* firstGraph, void* secondGraph) {
    printf("INIZIA EQUAL\n");
    ITRObject* firstIterator = graphVertices(firstGraph);
    ITRObject* secondIterator = graphVertices(secondGraph);

    while (!itrTerminated(firstIterator) && !itrTerminated(secondIterator)) {
        if( ((Vertex*)itrElement(firstIterator))->name ==  ((Vertex*)itrElement(secondIterator))->name) {
            printf("NOMI UGUALI\n");

            if(adtCompare(((Vertex*)itrElement(firstIterator))->label, ((Vertex*)itrElement(secondIterator))->label) == 0) {
                printf("VALORI UGUALI\n");

                ITRObject* firstAdjacentIterator = graphVertexEdges(firstGraph,((Vertex*)itrElement(firstIterator))->name);
                ITRObject* secondAdjacentIterator = graphVertexEdges(secondGraph, ((Vertex*)itrElement(firstIterator))->name);

                if(checkAdjacent(firstAdjacentIterator, secondAdjacentIterator)) {
                    itrSuccessor(firstIterator);
                    itrSuccessor(secondIterator);
                } else {
                    return false;
                }
            } else return false;
        } else return false;
        itrSuccessor(firstIterator);
        itrSuccessor(secondIterator);
    }

    if(itrTerminated(firstIterator) && itrTerminated(secondIterator)) {
        return true;
    }

    /*
    printf("\n");
    ITRObject* iter = graphVertices(firstGraph);

    while(!itrTerminated(iter)) {
        printf("Nome: %d - Label: ", ((Vertex*)itrElement(iter))->name);
        adtWriteToMonitor(((Vertex*)itrElement(iter))->label);
        printf("\n");
        itrSuccessor(iter);
    }
    printf("\n");
     */
}

void ConstructGraphRecursive(GraphType* type) {
    type->graphEqual = recGraphEqual;
}

void DestructGraphRecursive() {

}
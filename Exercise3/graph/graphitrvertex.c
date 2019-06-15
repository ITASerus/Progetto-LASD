
#include "graphitrvertex.h"

/* ************************************************************************** */

void* itrVertexConstruct(void* type, void* vertexLst) {
    ITRObject *iterator = (ITRObject*)malloc(sizeof(ITRObject));

    iterator->type = (ITRType*)type;
    iterator->iterator = (GraphVertexIterator*)malloc(sizeof(GraphVertexIterator));

    ((GraphVertexIterator*)iterator->iterator)->element = (VertexLst*)vertexLst;

    return iterator;
}

void itrVertexDestruct(void* iterator) {
    free(iterator);
}

bool itrVertexTerminated(void* iterator) {
    return ((GraphVertexIterator*)iterator)->element == NULL ? true : false;
}

void* itrVertexGetElement(void* iterator) {
    return ((GraphVertexIterator*)iterator)->element->vertexInfo;
}

void itrVertexSuccessor(void *iterator) {
    GraphVertexIterator *itr = (GraphVertexIterator*)iterator;

    if (itr->element != NULL) {
        itr->element = itr->element->nextVertex;
    }
}

ITRType* ConstructVertexIterator() {
    ITRType* type = (ITRType*)malloc(sizeof(ITRType));

    type->construct = itrVertexConstruct;
    type->destruct = itrVertexDestruct;

    type->terminated = itrVertexTerminated;

    type->getElement = itrVertexGetElement;

    type->successor = itrVertexSuccessor;

    return type;
}

void DestructVertexIterator(ITRType* type) {
    free(type);
}

#include "graph.h"

/* ************************************************************************** */

GraphObject* graphConstruct(GraphType* type) {
    GraphObject* object = (GraphObject*)malloc(sizeof(GraphObject));

    object->type = type;
    object->graph = type->graphRep->graphConstruct(type);

    return object;
}

void graphDestruct(GraphObject* graphObject) {
    graphObject->type->graphRep->graphDestruct(graphObject->graph);
    free(graphObject);
}


bool graphEmpty(GraphObject* graphObject) {
    return graphObject->type->graphRep->graphEmpty(graphObject->graph);
}


GraphObject* graphClone(GraphObject* graphObject) {
    GraphObject* clonedGraphObject =(GraphObject*)malloc(sizeof(GraphObject));
    clonedGraphObject->type = graphObject->type;
    clonedGraphObject->graph = graphObject->type->graphRep->graphClone(graphObject->graph);

    return clonedGraphObject;
}


GraphObject* graphTranspose(GraphObject* graphObject) {
    GraphObject* transposedGraphObject =(GraphObject*)malloc(sizeof(GraphObject));
    transposedGraphObject->type = graphObject->type;
    transposedGraphObject->graph = graphObject->type->graphRep->graphTranspose(graphObject->graph);

    return transposedGraphObject;
}


void graphInsertVertex(GraphObject* graphObject, int name, DataObject* label) {
    graphObject->type->graphRep->graphInsertVertex(graphObject->graph, name, label);
}

void graphRemoveVertex(GraphObject* graphObject, int name) {
    graphObject->type->graphRep->graphRemoveVertex(graphObject->graph, name);
}

void graphInsertEdge(GraphObject* graphObject, int fromVertexName, int toVertexName) {
    graphObject->type->graphRep->graphInsertEdge(graphObject->graph, fromVertexName, toVertexName);
}

void graphRemoveEdge(GraphObject* graphObject, int fromVertexName, int toVertexName) {
    graphObject->type->graphRep->graphRemoveEdge(graphObject->graph, fromVertexName, toVertexName);
}

bool graphExistsVertex(GraphObject* graphObject, int name) {
    return graphObject->type->graphRep->graphExistsVertex(graphObject->graph, name);
}

bool graphExistsEdge(GraphObject* graphObject, int fromVertexName, int toVertexName) {
    return graphObject->type->graphRep->graphExistsEdge(graphObject->graph, fromVertexName, toVertexName);
}

DataObject* graphGetVertexData(GraphObject* graphObject, int name) {
    return graphObject->type->graphRep->graphGetVertexData(graphObject->graph, name);
}

void graphSetVertexData(GraphObject* graphObject, int name, DataObject* newValue) {
    graphObject->type->graphRep->graphSetVertexData(graphObject->graph, name, newValue);
}
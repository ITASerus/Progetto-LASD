
#include "graph.h"

/* ************************************************************************** */

GraphObject* graphConstruct(GraphType* type) {
    GraphObject* object = (GraphObject*)malloc(sizeof(GraphObject));

    object->type = type;
    object->graph = type->graphRep->graphConstruct(type);

    return object;
}

bool graphEmpty(GraphObject* graphObject) {
    return graphObject->type->graphRep->graphEmpty(graphObject->graph);
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

bool graphExistsVertex(GraphObject* graphObject, int name) {
    return graphObject->type->graphRep->graphExistsVertex(graphObject->graph, name);
}

bool graphExistsEdge(GraphObject* graphObject, int fromVertexName, int toVertexName) {
    return graphObject->type->graphRep->graphExistsEdge(graphObject->graph, fromVertexName, toVertexName);
}

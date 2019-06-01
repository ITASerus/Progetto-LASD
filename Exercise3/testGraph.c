
#include "testGraph.h"

void printGraphLst(GraphObject* graphObject) {
    GraphLst* tmp = ((GraphLst*)graphObject->graph);
    while(tmp->vertexInfo != NULL) {
        adtWriteToMonitor(tmp->vertexInfo->label);
        printf("\n");
        tmp = tmp->next;
    }
}

void testGraph() {
    GraphType *graphTyp = (GraphType *) malloc(sizeof(GraphType));
    graphTyp->graphRep = ConstructGraphLst();

    GraphObject *graphObject = graphConstruct(graphTyp);

    DataType *dataTyp = ConstructIntDataType();
    DataObject *dataPtr = adtConstruct(dataTyp);
    adtRandomValue(dataPtr);

    printf("Grafo vuoto?: ");
    if (graphEmpty(graphObject)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    graphInsertVertex(graphObject, 2, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 5, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 8, dataPtr);

    printGraphLst(graphObject);
/*
    printf("Grafo vuoto?: ");
    if (graphEmpty(graphObject)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("*****************************************************************\n");

    printf("VERIFICA ESISTENZA VERTICE 2: ");
    if(graphExistsVertex(graphObject, 2)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA VERTICE 9: ");
    if(graphExistsVertex(graphObject, 9)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA VERTICE 5: ");
    if(graphExistsVertex(graphObject, 5)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("*****************************************************************\n");
    printf("INSERIMENTO ARCO TRA 2 e 9\n");
    graphInsertEdge(graphObject, 2, 9);

    printf("INSERIMENTO ARCO TRA 3 e 9\n");
    graphInsertEdge(graphObject, 2, 9);

    printf("INSERIMENTO ARCO TRA 2 e 7\n");
    graphInsertEdge(graphObject, 2, 9);*/
}
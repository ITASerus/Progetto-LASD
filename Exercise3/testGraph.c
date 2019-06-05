
#include "testGraph.h"

void printGraphLst(GraphObject* graphObject) {
    printf("\nGRAFO:\n");
    VertexLst* tmp = ((GraphLst*)graphObject->graph)->vertexLst;
    AdjacentLst* tmpAdjacentLstVertex = ((GraphLst*)graphObject->graph)->adjacentVertexLst;
    while(tmp != NULL && tmpAdjacentLstVertex != NULL) {
        printf("Nome: %d Etichetta: ", tmp->vertexInfo->name);
        adtWriteToMonitor(tmp->vertexInfo->label);

        AdjacentLst* tmpAdjacentLstAdjacent = tmpAdjacentLstVertex;
        printf(" ADIACENTI:");
        while(tmpAdjacentLstAdjacent != NULL) {
            printf(" %d |", tmpAdjacentLstAdjacent->vertexPointer->name);
            tmpAdjacentLstAdjacent = tmpAdjacentLstAdjacent->nextAdjacent;
        }

        tmp = tmp->nextVertex;
        tmpAdjacentLstVertex = tmpAdjacentLstVertex->nextVertex;

        printf("\n");
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

    printf("INSERIMENTO VERTICE 8\n");
    graphInsertVertex(graphObject, 8, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 5\n");
    graphInsertVertex(graphObject, 5, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 3\n");
    graphInsertVertex(graphObject, 3, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 8 GIA INSERITO\n");
    graphInsertVertex(graphObject, 8, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 2\n");
    graphInsertVertex(graphObject, 2, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 5 GIA INSERITO\n");
    graphInsertVertex(graphObject, 5, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 0\n");
    graphInsertVertex(graphObject, 0, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 7\n");
    graphInsertVertex(graphObject, 7, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 8 GIA INSERITO\n");
    graphInsertVertex(graphObject, 8, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 9\n");
    graphInsertVertex(graphObject, 9, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 9 GIA INSERITO\n");
    graphInsertVertex(graphObject, 9, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 0 GIA INSERITO\n");
    graphInsertVertex(graphObject, 0, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 2 GIA INSERITO\n");
    graphInsertVertex(graphObject, 2, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 3 GIA INSERITO\n");
    graphInsertVertex(graphObject, 3, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 5 GIA INSERITO\n");
    graphInsertVertex(graphObject, 5, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 7 GIA INSERITO\n");
    graphInsertVertex(graphObject, 7, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 8 GIA INSERITO\n");
    graphInsertVertex(graphObject, 8, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 9 GIA INSERITO\n");
    graphInsertVertex(graphObject, 9, dataPtr);

    printf("Grafo vuoto?: ");
    if (graphEmpty(graphObject)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printGraphLst(graphObject);

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

    printf("VERIFICA ESISTENZA VERTICE 0: ");
    if(graphExistsVertex(graphObject, 0)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA VERTICE 8: ");
    if(graphExistsVertex(graphObject, 8)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("*****************************************************************\n");

    printf("INSERIMENTO ARCO TRA 0 e 5\n");
    graphInsertEdge(graphObject, 0, 5);

    printf("INSERIMENTO ARCO TRA 0 e 0\n");
    graphInsertEdge(graphObject, 0, 0);

    printf("INSERIMENTO ARCO TRA 2 e 8\n");
    graphInsertEdge(graphObject, 2, 8);

    printf("INSERIMENTO ARCO TRA 3 e 5\n");
    graphInsertEdge(graphObject, 3, 5);

    printf("INSERIMENTO ARCO TRA 5 e 5\n");
    graphInsertEdge(graphObject, 5, 5);

    printf("INSERIMENTO ARCO TRA 7 e 8\n");
    graphInsertEdge(graphObject, 7, 8);

    printf("INSERIMENTO ARCO TRA 7 e 5\n");
    graphInsertEdge(graphObject, 7, 5);

    printf("INSERIMENTO ARCO TRA 7 e 7\n");
    graphInsertEdge(graphObject, 7, 7);

    printf("INSERIMENTO ARCO TRA 8 e 0\n");
    graphInsertEdge(graphObject, 8, 0);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 0 e 5\n");
    graphInsertEdge(graphObject, 0, 5);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 8 e 0\n");
    graphInsertEdge(graphObject, 8, 0);

    printf("INSERIMENTO ARCO TRA 8 e 8\n");
    graphInsertEdge(graphObject, 8, 8);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 5 e 5\n");
    graphInsertEdge(graphObject, 5, 5);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 8 e 8\n");
    graphInsertEdge(graphObject, 8, 8);

    printf("INSERIMENTO ARCO TRA 9 e 7\n");
    graphInsertEdge(graphObject, 9, 7);

    printf("INSERIMENTO ARCO TRA 9 e 0\n");
    graphInsertEdge(graphObject, 9, 0);

    printf("INSERIMENTO ARCO TRA 9 e 9\n");
    graphInsertEdge(graphObject, 9, 9);

    printf("INSERIMENTO ARCO TRA 9 e 8\n");
    graphInsertEdge(graphObject, 9, 8);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 0\n");
    graphInsertEdge(graphObject, 9, 0);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 7\n");
    graphInsertEdge(graphObject, 9, 7);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 9\n");
    graphInsertEdge(graphObject, 9, 9);

    printGraphLst(graphObject);

    printf("*****************************************************************\n");

    printf("VERIFICA ESISTENZA ARCO TRA 9 e 0: ");
    if(graphExistsEdge(graphObject, 9, 0)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA ARCO TRA 0 e 9: ");
    if(graphExistsEdge(graphObject, 0, 9)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA ARCO TRA 0 e 0: ");
    if(graphExistsEdge(graphObject, 0, 0)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA ARCO TRA 2 e 2: ");
    if(graphExistsEdge(graphObject, 2, 2)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA ARCO TRA 7 e 8: ");
    if(graphExistsEdge(graphObject, 7, 8)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA ARCO TRA 7 e 7: ");
    if(graphExistsEdge(graphObject, 7, 7)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA ARCO TRA 9 e 9: ");
    if(graphExistsEdge(graphObject, 9, 9)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA ARCO TRA 3 e 6: ");
    if(graphExistsEdge(graphObject, 3, 6)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("*****************************************************************\n");

    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 8");
    graphRemoveVertex(graphObject, 8);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 9");
    graphRemoveVertex(graphObject, 9);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 2");
    graphRemoveVertex(graphObject, 2);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 1");
    graphRemoveVertex(graphObject, 1);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 3");
    graphRemoveVertex(graphObject, 3);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 4");
    graphRemoveVertex(graphObject, 4);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 5");
    graphRemoveVertex(graphObject, 5);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 67");
    graphRemoveVertex(graphObject, 67);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 8");
    graphRemoveVertex(graphObject, 8);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE VERTICE 0");
    graphRemoveVertex(graphObject, 0);
    printGraphLst(graphObject);

    printf("*****************************************************************\n");

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 2\n");
    graphInsertVertex(graphObject, 2, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 6\n");
    graphInsertVertex(graphObject, 6, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 8\n");
    graphInsertVertex(graphObject, 8, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 2\n");
    graphInsertVertex(graphObject, 2, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 1\n");
    graphInsertVertex(graphObject, 1, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 0\n");
    graphInsertVertex(graphObject, 0, dataPtr);

    printGraphLst(graphObject);

    printf("*****************************************************************\n");

    printf("INSERIMENTO ARCO TRA 0 e 5\n");
    graphInsertEdge(graphObject, 0, 5);

    printf("INSERIMENTO ARCO TRA 0 e 0\n");
    graphInsertEdge(graphObject, 0, 0);

    printf("INSERIMENTO ARCO TRA 2 e 8\n");
    graphInsertEdge(graphObject, 2, 8);

    printf("INSERIMENTO ARCO TRA 3 e 5\n");
    graphInsertEdge(graphObject, 3, 5);

    printf("INSERIMENTO ARCO TRA 5 e 5\n");
    graphInsertEdge(graphObject, 5, 5);

    printf("INSERIMENTO ARCO TRA 7 e 8\n");
    graphInsertEdge(graphObject, 7, 8);

    printf("INSERIMENTO ARCO TRA 7 e 5\n");
    graphInsertEdge(graphObject, 7, 5);

    printf("INSERIMENTO ARCO TRA 7 e 7\n");
    graphInsertEdge(graphObject, 7, 7);

    printf("INSERIMENTO ARCO TRA 8 e 0\n");
    graphInsertEdge(graphObject, 8, 0);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 0 e 5\n");
    graphInsertEdge(graphObject, 0, 5);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 8 e 0\n");
    graphInsertEdge(graphObject, 8, 0);

    printf("INSERIMENTO ARCO TRA 8 e 8\n");
    graphInsertEdge(graphObject, 8, 8);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 5 e 5\n");
    graphInsertEdge(graphObject, 5, 5);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 8 e 8\n");
    graphInsertEdge(graphObject, 8, 8);

    printf("INSERIMENTO ARCO TRA 9 e 7\n");
    graphInsertEdge(graphObject, 9, 7);

    printf("INSERIMENTO ARCO TRA 9 e 0\n");
    graphInsertEdge(graphObject, 9, 0);

    printf("INSERIMENTO ARCO TRA 9 e 9\n");
    graphInsertEdge(graphObject, 9, 9);

    printf("INSERIMENTO ARCO TRA 9 e 8\n");
    graphInsertEdge(graphObject, 9, 8);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 0\n");
    graphInsertEdge(graphObject, 9, 0);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 7\n");
    graphInsertEdge(graphObject, 9, 7);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 9\n");
    graphInsertEdge(graphObject, 9, 9);

    printGraphLst(graphObject);

}
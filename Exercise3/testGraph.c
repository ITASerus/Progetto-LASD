
#include "testGraph.h"

void printGraphLst(GraphObject* graphObject) { //TODO: Evita di stampare il primo nodo della lista di adiacenza
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

void printGraphMat(GraphObject* graphObject) {
    printf("\nGRAFO:\n");
    VertexLst* tmp = ((GraphMat*)graphObject->graph)->vertexLst;

    int index = 0;
    while(tmp != NULL) {
        printf("Nome: %d Etichetta: ", tmp->vertexInfo->name);
        adtWriteToMonitor(tmp->vertexInfo->label);

        printf(" ADIACENTI:");
        bool** matrix = ((GraphMat*)graphObject->graph)->adjacentMatrix;
        for(int i = 0; i < ((GraphMat*)graphObject->graph)->numVertex; i++) {
            if(matrix[index][i]) {
                VertexLst* currentVertex = ((GraphMat*)graphObject->graph)->vertexLst;
                for(int j = 0; j < i; j++) {
                    currentVertex = currentVertex->nextVertex;
                }
                printf(" %d |", currentVertex->vertexInfo->name);
            }
        }
        tmp = tmp->nextVertex;

        index++;
        printf("\n");
    }
}

void printGraphMatValue(GraphObject* graphObject) {
    printf("\nGRAFO:\n");
    VertexLst* tmp = ((GraphMat*)graphObject->graph)->vertexLst;

    int index = 0;
    while(tmp != NULL) {
        printf("Nome: %d Etichetta: ", tmp->vertexInfo->name);
        adtWriteToMonitor(tmp->vertexInfo->label);

        printf(" ADIACENTI: ");
        bool** matrix = ((GraphMat*)graphObject->graph)->adjacentMatrix;
        for(int i = 0; i < ((GraphMat*)graphObject->graph)->numVertex; i++) {
            if(matrix[index][i]) {
                printf("T | ");
            }
            else {
                printf("F | ");
            }
        }

        tmp = tmp->nextVertex;
        index++;
        printf("\n");
    }
}

void testList() {
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
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

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

    printf("VERIFICA ESISTENZA VERTICE -1: ");
    if(graphExistsVertex(graphObject, -1)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("VERIFICA ESISTENZA VERTICE 19: ");
    if(graphExistsVertex(graphObject, 19)) {
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

    printf("INSERIMENTO ARCO TRA 7 e 0\n");
    graphInsertEdge(graphObject, 7, 0);

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
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");

    printf("VERIFICA ESISTENZA ARCO TRA 200 e 300: ");
    if(graphExistsEdge(graphObject, 200, 300)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

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

    printf("\nRIMOZIONE VERTICE 7");
    graphRemoveVertex(graphObject, 7);
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

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");

    printf("\nINSERIMENTO VERTICE 7");
    graphInsertVertex(graphObject, 7, dataPtr);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

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

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 10\n");
    graphInsertVertex(graphObject, 10, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 12\n");
    graphInsertVertex(graphObject, 12, dataPtr);

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 15\n");
    graphInsertVertex(graphObject, 15, dataPtr);

    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");

    printf("INSERIMENTO ARCO TRA 0 e 5\n");
    graphInsertEdge(graphObject, 0, 5);

    printf("INSERIMENTO ARCO TRA 0 e 0\n");
    graphInsertEdge(graphObject, 0, 0);

    printf("INSERIMENTO ARCO TRA 2 e 8\n");
    graphInsertEdge(graphObject, 2, 8);

    printf("INSERIMENTO ARCO TRA 7 e 15\n");
    graphInsertEdge(graphObject, 7, 15);

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

    printf("INSERIMENTO ARCO TRA 7 e 12\n");
    graphInsertEdge(graphObject, 7, 12);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 0\n");
    graphInsertEdge(graphObject, 9, 0);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 7\n");
    graphInsertEdge(graphObject, 9, 7);

    printf("INSERIMENTO ARCO GIA PRESENTE TRA 9 e 9\n");
    graphInsertEdge(graphObject, 9, 9);

    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");
    printGraphLst(graphObject);

    printf("\nRIMOZIONE ARCO TRA 1 e 3");
    graphRemoveEdge(graphObject, 1, 3);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 7 e 11");
    graphRemoveEdge(graphObject, 7, 11);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 7 e 12");
    graphRemoveEdge(graphObject, 7, 12);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 7 e 7");
    graphRemoveEdge(graphObject, 7, 7);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 8 e 0");
    graphRemoveEdge(graphObject, 8, 0);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 8 e 8");
    graphRemoveEdge(graphObject, 8, 8);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 2 e 8");
    graphRemoveEdge(graphObject, 2, 8);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 7 e 7");
    graphRemoveEdge(graphObject, 7, 7);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 7 e 5");
    graphRemoveEdge(graphObject, 7, 5);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 7 e 8");
    graphRemoveEdge(graphObject, 7, 8);
    printGraphLst(graphObject);

    printf("\nRIMOZIONE ARCO TRA 3 e 3");
    graphRemoveEdge(graphObject, 3, 3);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 7 e 15");
    graphRemoveEdge(graphObject, 7, 15);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 7 e 0");
    graphRemoveEdge(graphObject, 7, 0);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("\nRIMOZIONE ARCO TRA 0 e 0");
    graphRemoveEdge(graphObject, 0, 0);
    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");

    printf("\nRIMOZIONE VERTICE 0");
    graphRemoveVertex(graphObject, 0);

    printf("\nRIMOZIONE VERTICE 1");
    graphRemoveVertex(graphObject, 1);

    printf("\nRIMOZIONE VERTICE 2");
    graphRemoveVertex(graphObject, 2);

    printf("\nRIMOZIONE VERTICE 6");
    graphRemoveVertex(graphObject, 6);

    printf("\nRIMOZIONE VERTICE 7");
    graphRemoveVertex(graphObject, 7);

    printf("\nRIMOZIONE VERTICE 8");
    graphRemoveVertex(graphObject, 8);

    printf("\nRIMOZIONE VERTICE 10");
    graphRemoveVertex(graphObject, 10);

    printf("\nRIMOZIONE VERTICE 12");
    graphRemoveVertex(graphObject, 12);

    printf("\nRIMOZIONE VERTICE 15");
    graphRemoveVertex(graphObject, 15);

    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");

    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 1, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 2, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 3, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 4, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 5, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 7, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 8, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 9, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 10, dataPtr);

    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");

    if((dataPtr = graphGetVertexData(graphObject, 1))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 2))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 3))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 4))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 5))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 6))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 7))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 8))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 9))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 10))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, -1))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    if((dataPtr = graphGetVertexData(graphObject, 100))) {
        adtWriteToMonitor(dataPtr);
        printf("\n");
    } else {
        printf("NON PRESENTE\n");
    }

    printf("*****************************************************************\n");

    dataPtr = adtConstruct(dataTyp);
    adtRandomValue(dataPtr);
    printf("Nuovo valore: ");
    adtWriteToMonitor(dataPtr);
    printf("\n");

    graphSetVertexData(graphObject, 1, dataPtr);
    graphSetVertexData(graphObject, 2, dataPtr);
    graphSetVertexData(graphObject, 3, dataPtr);
    graphSetVertexData(graphObject, 4, dataPtr);
    graphSetVertexData(graphObject, 5, dataPtr);
    graphSetVertexData(graphObject, 6, dataPtr);
    graphSetVertexData(graphObject, 7, dataPtr);
    graphSetVertexData(graphObject, 8, dataPtr);
    graphSetVertexData(graphObject, 9, dataPtr);
    graphSetVertexData(graphObject, 10, dataPtr);
    graphSetVertexData(graphObject, 11, dataPtr);
    graphSetVertexData(graphObject, -1, dataPtr);

    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");

    graphDestruct(graphObject);

    printGraphLst(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n");

    graphObject = graphConstruct(graphTyp);

    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 1, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 2, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 3, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 4, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 5, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 6, dataPtr);

    graphInsertEdge(graphObject, 1, 5);
    graphInsertEdge(graphObject, 1, 1);
    graphInsertEdge(graphObject, 1, 2);
    graphInsertEdge(graphObject, 1, 15);
    graphInsertEdge(graphObject, 2, 5);
    graphInsertEdge(graphObject, 2, 6);
    graphInsertEdge(graphObject, 2, 1);
    graphInsertEdge(graphObject, 3, 3);
    graphInsertEdge(graphObject, 3, 1);
    graphInsertEdge(graphObject, 3, 2);
    graphInsertEdge(graphObject, 3, 5);
    graphInsertEdge(graphObject, 3, 0);
    graphInsertEdge(graphObject, 3, 8);
    graphInsertEdge(graphObject, 3, 4);
    graphInsertEdge(graphObject, 4, 6);
    graphInsertEdge(graphObject, 4, 1);
    graphInsertEdge(graphObject, 5, 1);
    graphInsertEdge(graphObject, 5, 5);
    graphInsertEdge(graphObject, 5, 5);
    graphInsertEdge(graphObject, 5, 4);
    graphInsertEdge(graphObject, 5, 2);
    graphInsertEdge(graphObject, 5, 3);
    graphInsertEdge(graphObject, 7, 0);

    printGraphLst(graphObject);

    GraphObject* clonedGraph;
    clonedGraph = graphClone(graphObject);
    printGraphLst(clonedGraph);

    printf("*****************************************************************\n");
    printf("\nTEST CORRETTEZZA PUNTATORI CLONE:\n");

    printf("\nPRE-MODIFICA:");
    printGraphLst(graphObject);
    printGraphLst(clonedGraph);

    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 1, dataPtr);
    graphSetVertexData(graphObject, 2, dataPtr);
    graphSetVertexData(graphObject, 3, dataPtr);
    graphSetVertexData(graphObject, 4, dataPtr);
    graphSetVertexData(graphObject, 5, dataPtr);
    graphSetVertexData(graphObject, 6, dataPtr);
    graphRemoveEdge(graphObject, 1, 1);
    graphRemoveEdge(graphObject, 1, 1);
    graphRemoveEdge(graphObject, 2, 5);
    graphRemoveEdge(graphObject, 2, 6);
    graphRemoveEdge(graphObject, 5, 3);
    graphRemoveEdge(graphObject, 5, 1);
    graphRemoveEdge(graphObject, 5, 2);

    adtRandomValue(dataPtr);
    graphSetVertexData(clonedGraph, 1, dataPtr);
    graphSetVertexData(clonedGraph, 2, dataPtr);
    graphSetVertexData(clonedGraph, 3, dataPtr);
    graphSetVertexData(clonedGraph, 4, dataPtr);
    graphSetVertexData(clonedGraph, 5, dataPtr);
    graphSetVertexData(clonedGraph, 6, dataPtr);
    graphRemoveEdge(clonedGraph, 1, 1);
    graphRemoveEdge(clonedGraph, 1, 5);
    graphRemoveEdge(clonedGraph, 2, 6);
    graphRemoveEdge(clonedGraph, 5, 1);
    graphRemoveEdge(clonedGraph, 5, 3);
    graphRemoveEdge(clonedGraph, 5, 6);
    graphRemoveEdge(clonedGraph, 5, 5);
    graphRemoveVertex(clonedGraph, 3);

    printf("\nPOST-MODIFICA:");
    printGraphLst(graphObject);
    printGraphLst(clonedGraph);

    graphDestruct(clonedGraph);

    printf("*****************************************************************\n");

    printGraphLst(graphObject);

    GraphObject* transposedGraph = graphTranspose(graphObject);
    printGraphLst(transposedGraph);

    graphDestruct(transposedGraph);
    printf("*****************************************************************\n");

    printf("\nNUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBJECT: %d\n\n", graphEdgeNumber(graphObject));

    graphDestruct(graphObject);
    printf("*****************************************************************\n");

    printf("\nTEST TRANSPOSEDGRAPH:\n");

    graphObject = graphConstruct(graphTyp);
    transposedGraph = graphTranspose(graphObject);

    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    graphInsertVertex(graphObject, 8, dataPtr);
    transposedGraph = graphTranspose(graphObject);
    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    graphInsertVertex(graphObject, 7, dataPtr);
    transposedGraph = graphTranspose(graphObject);
    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    graphInsertEdge(graphObject, 7, 8);
    transposedGraph = graphTranspose(graphObject);
    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    graphInsertEdge(graphObject, 8, 7);
    transposedGraph = graphTranspose(graphObject);
    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    graphInsertEdge(graphObject, 7, 7);
    transposedGraph = graphTranspose(graphObject);
    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    graphInsertVertex(graphObject, 10, dataPtr);
    transposedGraph = graphTranspose(graphObject);
    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    adtRandomValue(dataPtr);
    graphSetVertexData(transposedGraph, 10, dataPtr);
    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    ((GraphLst*)transposedGraph->graph)->vertexLst->vertexInfo->name = 90;
    printGraphLst(graphObject);
    printGraphLst(transposedGraph);

    graphDestruct(transposedGraph);

    printf("*****************************************************************\n");
}

void testMat() {
    GraphType *graphTyp = (GraphType*)malloc(sizeof(GraphType));
    graphTyp->graphRep = ConstructGraphMat();

    GraphObject *graphObject = graphConstruct(graphTyp);

    DataType *dataTyp = ConstructIntDataType();
    DataObject *dataPtr = adtConstruct(dataTyp);


    printf("Grafo vuoto?: ");
    if (graphEmpty(graphObject)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("\n\n");

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 1\n");
    graphInsertVertex(graphObject, 1, dataPtr);
}

void testGraph() {
    //testList();
    testMat();
}

#include "testGraph.h"

void printGraphLst(GraphObject* graphObject) { //TODO: Evita di stampare il primo nodo della lista di adiacenza
    printf("\nGRAFO:\n");
    VertexLst* tmp = ((GraphLst*)graphObject->graph)->vertexLst;
    AdjacentLst* tmpAdjacentLstVertex = ((GraphLst*)graphObject->graph)->adjacentVertexLst;
    while(tmp != NULL && tmpAdjacentLstVertex != NULL) {
        printf("Nome: %d Etichetta: ", tmp->vertexInfo->name);
        adtWriteToMonitor(tmp->vertexInfo->label);

        AdjacentLst* tmpAdjacentLstAdjacent = tmpAdjacentLstVertex->nextAdjacent;
        printf(" ADIACENTI:");
        while(tmpAdjacentLstAdjacent != NULL) {
            printf(" (%d, ", tmpAdjacentLstAdjacent->vertexPointer->name);
            printf("%d) |", *(int*)tmpAdjacentLstAdjacent->vertexPointer->label->value);
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
        bool** matrix = ((GraphMat*)graphObject->graph)->adjacentMatrix->matrix;
        for(int i = 0; i < ((GraphMat*)graphObject->graph)->adjacentMatrix->numVertex; i++) {
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
        printf("Nome: %d ", tmp->vertexInfo->name);

        printf(" ADIACENTI: ");
        bool** matrix = ((GraphMat*)graphObject->graph)->adjacentMatrix->matrix;
        for(int i = 0; i < ((GraphMat*)graphObject->graph)->adjacentMatrix->numVertex; i++) {
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


void printBSTElem(DataObject* dat, void* _) {
    printf(" | ");
    adtWriteToMonitor(dat);
}

void printGraphBST(GraphObject* graphObject) {
    VertexLst* tmp = ((GraphLst*)graphObject->graph)->vertexLst;
    AdjacentBSTLst* tmpAdjacentBSTLstVertex = ((GraphBST*)graphObject->graph)->adjacentBSTLst;
    printf("\n");
    while(tmp != NULL && tmpAdjacentBSTLstVertex != NULL) {
        printf("Nome: %d Etichetta: ", tmp->vertexInfo->name);
        adtWriteToMonitor(tmp->vertexInfo->label);

        printf(" ADIACENTI:");
        if(!bstEmpty(tmpAdjacentBSTLstVertex->adjacentTree)) {
            bstInOrderMap(tmpAdjacentBSTLstVertex->adjacentTree, printBSTElem, NULL);
        } else {
            printf(" Nessuno");
        }

        tmp = tmp->nextVertex;
        tmpAdjacentBSTLstVertex = tmpAdjacentBSTLstVertex->nextVertex;

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

    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 8, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 10, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 15, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 2, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 7, dataPtr);
    graphInsertEdge(graphObject, 2, 15);
    graphInsertEdge(graphObject, 10, 2);
    graphInsertEdge(graphObject, 10, 7);
    graphInsertEdge(graphObject, 10, 8);
    graphInsertEdge(graphObject, 10, 10);
    graphInsertEdge(graphObject, 10, 15);

    printGraphLst(graphObject);

    printf("*****************************************************************\n");

    printf("\nTEST ITERATORE VERTICI\n");
    ITRObject* iter = graphVertices(graphObject);

    while(!itrTerminated(iter)) {
        printf("Nome: %d - Label: ", ((Vertex*)itrElement(iter))->name);
        adtWriteToMonitor(((Vertex*)itrElement(iter))->label);
        printf("\n");
        itrSuccessor(iter);
    }

    printf("\n*****************************************************************\n");

    printf("\nTEST ITERATORE ADIACENTI\n");

    iter = graphVertexEdges(graphObject, 10);

    while(!itrTerminated(iter)) {
        printf("Nome: %d - Label: ", ((Vertex*)itrElement(iter))->name);
        adtWriteToMonitor(((Vertex*)itrElement(iter))->label);
        printf("\n");
        itrSuccessor(iter);
    }


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

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("*****************************************************************\n\n");

    adtRandomValue(dataPtr);
    printf("INSERIMENTO VERTICE 5");
    graphInsertVertex(graphObject, 5, dataPtr);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 5, 5);
    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("INSERIMENTO VERTICE 4");
    graphInsertVertex(graphObject, 4, dataPtr);
    printGraphMatValue(graphObject);

    printf("INSERIMENTO VERTICE 6");
    graphInsertVertex(graphObject, 6, dataPtr);
    printGraphMatValue(graphObject);

    printf("INSERIMENTO VERTICE 3");
    graphInsertVertex(graphObject, 3, dataPtr);
    printGraphMatValue(graphObject);

    printf("INSERIMENTO VERTICE 7");
    graphInsertVertex(graphObject, 7, dataPtr);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 3, 3);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 3, 4);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 3, 5);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 3, 6);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 3, 7);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 4, 3);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 5, 3);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 6, 3);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 7, 3);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 7, 4);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 7, 5);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 7, 6);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 7, 7);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 3, 7);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 4, 7);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 5, 7);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 6, 7);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    printGraphMatValue(graphObject);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("INSERIMENTO VERTICE 2");
    graphInsertVertex(graphObject, 2, dataPtr);
    printGraphMatValue(graphObject);

    printf("INSERIMENTO VERTICE 8");
    graphInsertVertex(graphObject, 8, dataPtr);
    printGraphMatValue(graphObject);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    printf("INSERIMENTO VERTICE 1");
    graphInsertVertex(graphObject, 1, dataPtr);
    printGraphMatValue(graphObject);

    printf("INSERIMENTO VERTICE 9");
    graphInsertVertex(graphObject, 9, dataPtr);
    printGraphMatValue(graphObject);

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 1, 1);
    graphInsertEdge(graphObject, 1, 2);
    graphInsertEdge(graphObject, 1, 3);
    graphInsertEdge(graphObject, 1, 4);
    graphInsertEdge(graphObject, 1, 5);
    graphInsertEdge(graphObject, 1, 6);
    graphInsertEdge(graphObject, 1, 7);
    graphInsertEdge(graphObject, 1, 8);
    graphInsertEdge(graphObject, 1, 9);
    graphInsertEdge(graphObject, 9, 1);
    graphInsertEdge(graphObject, 9, 2);
    graphInsertEdge(graphObject, 9, 3);
    graphInsertEdge(graphObject, 9, 4);
    graphInsertEdge(graphObject, 9, 5);
    graphInsertEdge(graphObject, 9, 6);
    graphInsertEdge(graphObject, 9, 7);
    graphInsertEdge(graphObject, 9, 8);
    graphInsertEdge(graphObject, 9, 9);
    graphInsertEdge(graphObject, 2, 1);
    graphInsertEdge(graphObject, 3, 1);
    graphInsertEdge(graphObject, 4, 1);
    graphInsertEdge(graphObject, 5, 1);
    graphInsertEdge(graphObject, 6, 1);
    graphInsertEdge(graphObject, 7, 1);
    graphInsertEdge(graphObject, 8, 1);
    graphInsertEdge(graphObject, 2, 9);
    graphInsertEdge(graphObject, 3, 9);
    graphInsertEdge(graphObject, 4, 9);
    graphInsertEdge(graphObject, 5, 9);
    graphInsertEdge(graphObject, 6, 9);
    graphInsertEdge(graphObject, 7, 9);
    graphInsertEdge(graphObject, 8, 9);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphRemoveVertex(graphObject, 1);
    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertVertex(graphObject, 1, dataPtr);
    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 1, 1);
    graphInsertEdge(graphObject, 1, 2);
    graphInsertEdge(graphObject, 1, 3);
    graphInsertEdge(graphObject, 1, 4);
    graphInsertEdge(graphObject, 1, 5);
    graphInsertEdge(graphObject, 1, 6);
    graphInsertEdge(graphObject, 1, 7);
    graphInsertEdge(graphObject, 1, 8);
    graphInsertEdge(graphObject, 1, 9);
    graphInsertEdge(graphObject, 1, 1);
    graphInsertEdge(graphObject, 2, 1);
    graphInsertEdge(graphObject, 3, 1);
    graphInsertEdge(graphObject, 4, 1);
    graphInsertEdge(graphObject, 5, 1);
    graphInsertEdge(graphObject, 6, 1);
    graphInsertEdge(graphObject, 7, 1);
    graphInsertEdge(graphObject, 8, 1);
    graphInsertEdge(graphObject, 9, 1);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphRemoveVertex(graphObject, 9);
    printGraphMatValue(graphObject);

    graphRemoveVertex(graphObject, 5);
    printGraphMatValue(graphObject);

    graphRemoveVertex(graphObject, 7);
    printGraphMatValue(graphObject);

    graphRemoveVertex(graphObject, 3);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 4, 4);
    graphInsertEdge(graphObject, 4, 6);
    graphInsertEdge(graphObject, 6, 4);
    graphInsertEdge(graphObject, 6, 6);

    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));


    graphRemoveVertex(graphObject, 2);
    printGraphMatValue(graphObject);

    graphRemoveVertex(graphObject, 6);
    printGraphMatValue(graphObject);

    graphRemoveVertex(graphObject, 8);
    printGraphMatValue(graphObject);

    graphRemoveVertex(graphObject, 4);
    printGraphMatValue(graphObject);

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertVertex(graphObject, 2, dataPtr);
    printGraphMatValue(graphObject);

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertVertex(graphObject, 4, dataPtr);
    printGraphMatValue(graphObject);

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertVertex(graphObject, 3, dataPtr);
    printGraphMatValue(graphObject);
    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertVertex(graphObject, 1, dataPtr);
    printGraphMatValue(graphObject);

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertVertex(graphObject, 5, dataPtr);
    printGraphMatValue(graphObject);

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphInsertEdge(graphObject, 1, 1);
    graphInsertEdge(graphObject, 1, 3);
    graphInsertEdge(graphObject, 1, 5);

    graphInsertEdge(graphObject, 2, 2);
    graphInsertEdge(graphObject, 2, 4);

    graphInsertEdge(graphObject, 3, 1);
    graphInsertEdge(graphObject, 3, 3);
    graphInsertEdge(graphObject, 3, 5);

    graphInsertEdge(graphObject, 4, 2);
    graphInsertEdge(graphObject, 4, 4);

    graphInsertEdge(graphObject, 5, 1);
    graphInsertEdge(graphObject, 5, 3);
    graphInsertEdge(graphObject, 5, 5);

    printGraphMatValue(graphObject);

    printf("NUMERO DI VERTICI GRAPHOBJECT: %d\n", graphVertexNumber(graphObject));
    printf("NUMERO DI ARCHI GRAPHOBHECT: %d\n\n", graphEdgeNumber(graphObject));

    graphDestruct(graphObject);

    printf("*****************************************************************\n");

    graphObject = graphConstruct(graphTyp);

    graphInsertVertex(graphObject, 9, dataPtr);
    graphInsertVertex(graphObject, 3, dataPtr);
    graphInsertVertex(graphObject, 1, dataPtr);

    printGraphMatValue(graphObject);

    graphInsertEdge(graphObject, 1, 3);
    graphInsertEdge(graphObject, 3, 3);
    graphInsertEdge(graphObject, 9, 1);
    graphInsertEdge(graphObject, 9, 3);

    printGraphMatValue(graphObject);

    GraphObject* trans = graphTranspose(graphObject);
    printGraphMatValue(trans);

    GraphObject* clone = graphClone(trans);
    printGraphMatValue(clone);

    printf("\n*****************************************************************\n");

    printf("PULIZIA MEMORIA");
    graphDestruct(trans);
    graphDestruct(clone);

    printf("\n*****************************************************************\n");

    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, -1, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 1, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 3, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 9, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 15, dataPtr);

    graphInsertVertex(graphObject, 15, dataPtr);
    graphInsertVertex(graphObject, -1, dataPtr);

    graphInsertEdge(graphObject, 1, 1);
    graphInsertEdge(graphObject, 9, 9);
    graphInsertEdge(graphObject, 15, 15);
    graphInsertEdge(graphObject, 15, 1);
    graphInsertEdge(graphObject, 15, -1);
    graphInsertEdge(graphObject, 15, 9);
    graphInsertEdge(graphObject, 15, 3);
    graphInsertEdge(graphObject, 15, 15);
    printGraphMatValue(graphObject);

    printf("\nTEST ITERATORE VERTICI\n");
    ITRObject* iter = graphVertices(graphObject);

    while(!itrTerminated(iter)) {
        printf("Nome: %d - Label: ", ((Vertex*)itrElement(iter))->name);
        adtWriteToMonitor(((Vertex*)itrElement(iter))->label);
        printf("\n");
        itrSuccessor(iter);
    }

    printf("\n*****************************************************************\n");

    printf("\nTEST ITERATORE ADIACENTI\n");

    iter = graphVertexEdges(graphObject, 1);

    while(!itrTerminated(iter)) {
        printf("Nome: %d - Label: ", ((Vertex*)itrElement(iter))->name);
        adtWriteToMonitor(((Vertex*)itrElement(iter))->label);
        printf("\n");
        itrSuccessor(iter);
    }
}

void testBSTgraph() {
    GraphType *graphTyp = (GraphType *) malloc(sizeof(GraphType));
    graphTyp->graphRep = ConstructGraphBST();
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

    printf("Numero di vertici: %d\n", graphVertexNumber(graphObject));
    printf("Numero di archi: %d\n", graphEdgeNumber(graphObject));

    printf("\n*****************************************************************\n\n");

    printf("Inserimento vertice 1\n");
    graphInsertVertex(graphObject, 1, dataPtr);

    printf("Inserimento vertice 2\n");
    graphInsertVertex(graphObject, 2, dataPtr);

    printf("Inserimento vertice 3\n");
    graphInsertVertex(graphObject, 3, dataPtr);

    printf("Inserimento vertice 4\n");
    graphInsertVertex(graphObject, 4, dataPtr);

    printf("Inserimento vertice 5\n");
    graphInsertVertex(graphObject, 5, dataPtr);

    printf("Inserimento vertice 6\n");
    graphInsertVertex(graphObject, 6, dataPtr);

    printf("Inserimento vertice 7\n");
    graphInsertVertex(graphObject, 7, dataPtr);

    printGraphBST(graphObject);
    printf("Numero di vertici: %d\n", graphVertexNumber(graphObject));
    printf("Numero di archi: %d\n", graphEdgeNumber(graphObject));

    printf("\n*****************************************************************\n\n");

    printf("Inserimento arco tra 3 e 3\n");
    graphInsertEdge(graphObject, 3, 3);

    printf("Inserimento arco tra 3 e 2\n");
    graphInsertEdge(graphObject, 3, 2);

    printf("Inserimento arco tra 1 e 1\n");
    graphInsertEdge(graphObject, 1, 1);

    printf("Inserimento arco tra 1 e 2\n");
    graphInsertEdge(graphObject, 1, 2);

    printf("Inserimento arco tra 1 e 3\n");
    graphInsertEdge(graphObject, 1, 3);

    printf("Inserimento arco tra 1 e 4\n");
    graphInsertEdge(graphObject, 1, 4);

    printf("Inserimento arco tra 1 e 5\n");
    graphInsertEdge(graphObject, 1, 5);

    printf("Inserimento arco tra 7 e 1\n");
    graphInsertEdge(graphObject, 7, 1);

    printf("Inserimento arco tra 7 e 2\n");
    graphInsertEdge(graphObject, 7, 2);

    printf("Inserimento arco tra 7 e 4\n");
    graphInsertEdge(graphObject, 7, 4);

    printf("Inserimento arco tra 7 e 5\n");
    graphInsertEdge(graphObject, 7, 5);

    printf("Inserimento arco tra 7 e 6\n");
    graphInsertEdge(graphObject, 7, 6);

    printf("Inserimento arco tra 7 e 7\n");
    graphInsertEdge(graphObject, 7, 7);

    printf("Inserimento arco tra 7 e 8\n");
    graphInsertEdge(graphObject, 7, 8);

    printf("Inserimento arco tra 7 e 2\n");
    graphInsertEdge(graphObject, 7, 2);

    printf("Inserimento arco tra 7 e 2\n");
    graphInsertEdge(graphObject, 7, 2);

    printGraphBST(graphObject);
    printf("Numero di vertici: %d\n", graphVertexNumber(graphObject));
    printf("Numero di archi: %d\n", graphEdgeNumber(graphObject));

    printf("\n*****************************************************************\n\n");

    printf("Rimozione arco tra 1 e 5\n");
    graphRemoveEdge(graphObject, 1, 5);

    printf("Rimozione arco tra 1 e 1\n");
    graphRemoveEdge(graphObject, 1, 1);

    printf("Rimozione arco tra 9 e 7\n");
    graphRemoveEdge(graphObject, 9, 7);

    printf("Rimozione arco tra 7 e 9\n");
    graphRemoveEdge(graphObject, 7, 9);

    printf("Rimozione arco tra 7 e 7\n");
    graphRemoveEdge(graphObject, 7, 7);

    printGraphBST(graphObject);
    printf("Numero di vertici: %d\n", graphVertexNumber(graphObject));
    printf("Numero di archi: %d\n", graphEdgeNumber(graphObject));

    printf("\n*****************************************************************\n\n");

    printf("Rimozione vertice 1");
    graphRemoveVertex(graphObject, 1);

    printf("\n\nRimozione vertice 7");
    graphRemoveVertex(graphObject, 7);

    printf("\n\nRimozione vertice 5");
    graphRemoveVertex(graphObject, 5);

    printf("\n\nRimozione vertice 6");
    graphRemoveVertex(graphObject, 6);

    printGraphBST(graphObject);
    printf("Numero di vertici: %d\n", graphVertexNumber(graphObject));
    printf("Numero di archi: %d\n", graphEdgeNumber(graphObject));

    printf("\n*****************************************************************\n\n");

    printGraphBST(graphObject);

    printf("\nEsistenza vertice %d: %d\n", 1, graphExistsVertex(graphObject, 1));
    printf("Esistenza vertice %d: %d\n", 2, graphExistsVertex(graphObject, 2));
    printf("Esistenza vertice %d: %d\n", 3, graphExistsVertex(graphObject, 3));
    printf("Esistenza vertice %d: %d\n", 4, graphExistsVertex(graphObject, 4));
    printf("Esistenza vertice %d: %d\n", 5, graphExistsVertex(graphObject, 5));
    printf("Esistenza arto tra %d e %d: %d\n", 5, 6, graphExistsEdge(graphObject, 5, 6));
    printf("Esistenza arto tra %d e %d: %d\n", 2, 3, graphExistsEdge(graphObject, 2, 3));
    printf("Esistenza arto tra %d e %d: %d\n", 3, 2, graphExistsEdge(graphObject, 3, 2));
    printf("Esistenza arto tra %d e %d: %d\n", 3, 3, graphExistsEdge(graphObject, 3, 3));
    printf("Esistenza arto tra %d e %d: %d\n", 3, 4, graphExistsEdge(graphObject, 3, 4));
    printf("Esistenza arto tra %d e %d: %d\n", 2, 5, graphExistsEdge(graphObject, 2, 5));

    printf("\n*****************************************************************\n\n");

    printf("Distruzione graphObject\n");

    graphDestruct(graphObject);

    printf("\n*****************************************************************\n\n");

    graphObject = graphConstruct(graphTyp);

    printf("Grafo vuoto?: ");
    if (graphEmpty(graphObject)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    printf("\nCopia grafo vuoto");
    GraphObject* clonedGraph = graphClone(graphObject);
    printGraphBST(clonedGraph);

    graphInsertVertex(graphObject, 4, dataPtr);
    graphInsertVertex(graphObject, 3, dataPtr);
    graphInsertVertex(graphObject, 2, dataPtr);
    graphInsertVertex(graphObject, 1, dataPtr);

    printf("\nCopia grafo pieno ma senza archi");
    clonedGraph = graphClone(graphObject);
    printGraphBST(clonedGraph);

    graphInsertEdge(graphObject, 1, 1);
    graphInsertEdge(graphObject, 1, 2);
    graphInsertEdge(graphObject, 1, 3);
    graphInsertEdge(graphObject, 1, 4);
    graphInsertEdge(graphObject, 2, 2);
    graphInsertEdge(graphObject, 4, 3);
    graphInsertEdge(graphObject, 4, 1);

    printf("\nCopia grafo pieno con archi");
    clonedGraph = graphClone(graphObject);
    printGraphBST(clonedGraph);

    printf("\n*****************************************************************\n\n");

    printf("Test trasposta: \n");

    printGraphBST(clonedGraph);

    GraphObject* transposedGraph = graphTranspose(clonedGraph);
    printGraphBST(transposedGraph);

    graphDestruct(graphObject);
    graphDestruct(clonedGraph);
    graphDestruct(transposedGraph);

    graphObject = graphConstruct(graphTyp);

    printf("\nGRAPH VUOTO");
    printGraphBST(graphObject);
    transposedGraph = graphTranspose(graphObject);
    printGraphBST(transposedGraph);

    printf("\nGRAPH CON UN VERTICE");
    graphInsertVertex(graphObject, 1, dataPtr);
    printGraphBST(graphObject);
    transposedGraph = graphTranspose(graphObject);
    printGraphBST(transposedGraph);

    printf("\nGRAPH CON DUE VERTICI E UN ARCO");
    graphInsertVertex(graphObject, 10, dataPtr);
    graphInsertEdge(graphObject, 1, 10);
    printGraphBST(graphObject);
    transposedGraph = graphTranspose(graphObject);
    printGraphBST(transposedGraph);

    printf("\nGRAPH CON DUE VERTICI E DUE ARCHI");
    graphInsertEdge(graphObject, 10, 1);
    printGraphBST(graphObject);
    transposedGraph = graphTranspose(graphObject);
    printGraphBST(transposedGraph);

    printf("\nGRAPH CON VARI VERTICI E VARI ARCHI");
    graphInsertVertex(graphObject, 2, dataPtr);
    graphInsertVertex(graphObject, 3, dataPtr);
    graphInsertVertex(graphObject, 4, dataPtr);
    graphInsertVertex(graphObject, 5, dataPtr);
    graphInsertVertex(graphObject, 6, dataPtr);
    graphInsertEdge(graphObject, 2, 2);
    graphInsertEdge(graphObject, 2, 3);
    graphInsertEdge(graphObject, 3, 6);
    graphInsertEdge(graphObject, 4, 4);
    graphInsertEdge(graphObject, 4, 1);
    graphInsertEdge(graphObject, 5, 4);
    graphInsertEdge(graphObject, 5, 6);
    graphInsertEdge(graphObject, 5, 2);
    graphInsertEdge(graphObject, 10, 6);

    printGraphBST(graphObject);
    printf("Numero di vertici: %d\n", graphVertexNumber(graphObject));
    printf("Numero di archi: %d\n", graphEdgeNumber(graphObject));

    transposedGraph = graphTranspose(graphObject);
    printGraphBST(transposedGraph);
    printf("Numero di vertici: %d\n", graphVertexNumber(transposedGraph));
    printf("Numero di archi: %d\n", graphEdgeNumber(transposedGraph));

    graphRemoveVertex(transposedGraph, 5);
    printGraphBST(transposedGraph);
    printf("Numero di vertici: %d\n", graphVertexNumber(transposedGraph));
    printf("Numero di archi: %d\n", graphEdgeNumber(transposedGraph));

    printf("*****************************************************************\n");

    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 1, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 2, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 3, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 4, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 5, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 6, dataPtr);
    adtRandomValue(dataPtr);
    graphSetVertexData(graphObject, 10, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 15, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 2, dataPtr);
    adtRandomValue(dataPtr);
    graphInsertVertex(graphObject, 7, dataPtr);
    graphInsertEdge(graphObject, 2, 15);
    graphInsertEdge(graphObject, 10, 2);
    graphInsertEdge(graphObject, 10, 7);
    graphInsertEdge(graphObject, 10, 8);
    graphInsertEdge(graphObject, 10, 10);
    graphInsertEdge(graphObject, 10, 15);

    printf("*****************************************************************\n");

    printGraphBST(graphObject);

    printf("\nTEST ITERATORE VERTICI\n");
    ITRObject* iter = graphVertices(graphObject);

    while(!itrTerminated(iter)) {
        printf("Nome: %d - Label: ", ((Vertex*)itrElement(iter))->name);
        adtWriteToMonitor(((Vertex*)itrElement(iter))->label);
        printf("\n");
        itrSuccessor(iter);
    }

    printf("\n*****************************************************************\n");

    printf("\nTEST ITERATORE ADIACENTI\n");

    iter = graphVertexEdges(graphObject, 2);

    while(!itrTerminated(iter)) {
        printf("Nome: %d - Label: ", ((Vertex*)itrElement(iter))->name);
        adtWriteToMonitor(((Vertex*)itrElement(iter))->label);
        printf("\n");

        itrSuccessor(iter);
    }

}

void testGraph() {
    //testList();
    testMat();
    //testBSTgraph();
}
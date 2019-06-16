
#include "testGraph.h"

void testGraph() {
    GraphType* graphType = (GraphType*)malloc(sizeof(GraphType));

    int repType, number, scelta;
    printf("Inserire tipologia di struttra da utilizzare\n(1) Liste di adiacenza\n(2) Matrice di Adiacenza\n(3) Alberi di adiacenza\n");
    do {
        printf("Scelta: ");
        scanf("%d", &repType);
        switch (repType) {
            case 1: {
                graphType->graphRep = ConstructGraphLst();
                break;
            }
            case 2: {
                graphType->graphRep = ConstructGraphMat();
                break;
            }
            case 3: {
                graphType->graphRep = ConstructGraphBST();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Liste di adiacenza\n(2) Matrice di Adiacenza\n(3) Alberi di adiacenza");
                break;
            }
        }
    } while (repType != 1 && repType != 2 && repType!= 3);

    printf("Inserire tipologia di implementazione della pila da utilizzare\n(1) Ricorsiva\n(2) Iterativa\n");
    do {
        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                ConstructGraphRecursive(graphType);
                break;
            }
            case 2: {
                ConstructGraphIterative(graphType);
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Ricorsiva\n(2) Iterativa\n");
                break;
            }
        }
    } while (scelta != 1 && scelta != 2);

    DataType* datatype = NULL;
    int tipoDatoScelto;
    printf("Inserire tipologia di dato da gestire\n(1) Intero\n(2) Float\n(3) Stringhe\n(4) Record\n");
    do {
        printf("Scelta: ");
        scanf("%d", &tipoDatoScelto);
        switch (tipoDatoScelto) {
            case 1: {
                datatype = ConstructIntDataType();
                break;
            }
            case 2: {
                datatype = ConstructFloatDataType();
                break;
            }
            case 3: {
                datatype = ConstructStringDataType();
                break;
            }
            case 4: {
                datatype = ConstructRecordDataType();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Intero\n(2) Float\n(3) Stringhe\n(4) Record\n");
                break;
            }
        }
    } while( (tipoDatoScelto <1) || (tipoDatoScelto >4));

    GraphObject* graphObject = graphConstruct(graphType);
    DataObject* dataPtr = adtConstruct(datatype);

    do {
        printf("\n***********************************************************************************************\n\n");
        printf("Menu':\n"
               "(1) Popolamento randomico del grafo con N elementi\n"
               "\n"
               "(2) Visualizzazione del contenuto del grafo Pre-Order\n"
               "(3) Visualizzazione del contenuto del grafo Post-Order\n"
               "(4) Visualizzazione del contenuto del grafo in ampiezza\n"
               "\n"
               "(5) Inserimento manuale di un vertice nel grafo\n"
               "(6) Rimozione di un vertice dal grafo\n"
               "(7) Controllo esistenza di un vertice\n"
               "\n"
               "(8) Inserimento manuale di un arco tra due vertici presenti nel grafo\n"
               "(9) Rimozione di un arco dal grafo\n"
               "(10) Controllo esistenza di un arco tra due vertici presenti nel grafo\n");
        switch (tipoDatoScelto) {
            case 1: { //Interi
                printf("(11) Prodotto di ogni elemento minore di N\n"
                       "(12) Applicazione 2n per ogni elemento\n");
                break;
            }
            case 2: { //Float
                printf("(11) Somma valori maggiori di N\n"
                       "(12) Applicazione n^2 per ogni elemento\n");
                break;
            }
            case 3: { //Stringhe
                printf("(11) Concatenazione dei valori di lunghezza minore o uguale a N\n"
                       "(12) Applicazione funzione uppercase/lowercase per ogni elemento\n");
                break;
            }
            default: { //Record
                printf("(11) N/A\n"
                       "(12) N/A\n");
                break;
            }
        }
        printf("(13) Controllo vuotezza del grafo\n"
               "(14) Numero di nodi contenuti nel grafo\n"
               "(15) Numero di archi contenuti nel grafo\n"
               "(16) Svuotamento del grafo\n"
               "(17) Creazione e stampa di un clone del grafo e\n"
               "     controllo uguaglianza con il grafo principale\n"
               "(18) Creazione e stampa del trasposto del grafo\n"
               "\n"
               "(0) Deallocazione della stuttura ed uscita dal programma\n"
               "Scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                int numVertex;
                printf("Numero di vertici da inserire nel grafo: ");
                scanf("%d", &numVertex);

                int* vertexReference = (int*)malloc(sizeof(int) * numVertex); //Vettore utilizzato per creare gli archi successivamente

                int vertexName;
                for(int i = 0; i < numVertex; i++) {
                    adtRandomValue(dataPtr);

                    vertexName = rndNum(-250, 250);
                    graphInsertVertex(graphObject, vertexName, dataPtr);

                    vertexReference[i] = vertexName;
                }

                printf("Numero di archi da inserire nel grafo: ");
                scanf("%d", &number);

                int  fromVertexNumber;
                int toVertexNumber;
                for(int i = 0; i < number; i++) {
                    fromVertexNumber  = vertexReference[rndNum(0, numVertex-1)];
                    toVertexNumber = vertexReference[rndNum(0, numVertex-1)];

                    graphInsertEdge(graphObject, fromVertexNumber, toVertexNumber);
                }

                printf("Elementi inseriti!\n");
                break;
            }
            case 2: {
                printf("Da implementare\n");
                break;
            }
            case 3: {
                printf("Da implementare\n");
                break;
            }
            case 4: {
                printf("Da implementare\n");
                break;
            }
            case 5: {
                printf("Inserire il nome del nuovo vertice: ");
                scanf("%d", &number);

                printf("Inserire il valore del nuovo vertice: ");
                adtReadFromKeyboard(dataPtr);

                if(!graphExistsVertex(graphObject, number)){
                    graphInsertVertex(graphObject, number, dataPtr);
                    printf("Vetice inserito nel grafo!\n");
                } else {
                    printf("Vertice già presente nel grafo!\n");
                }

                break;
            }
            case 6: {
                printf("Inserire il nome del vertice da rimuovere: ");
                scanf("%d", &number);

                if(graphExistsVertex(graphObject, number)) {
                    graphRemoveVertex(graphObject, number);
                    printf("Vertice rimosso dal grafo!\n");
                } else {
                    printf("Il vertice non è presente nel grafo!\n");
                }

                break;
            }
            case 7: {
                printf("Inserire il nome del vertice da ricercare: ");
                scanf("%d", &number);

                if(graphExistsVertex(graphObject, number)) {
                    printf("Il vertice è presente nel grafo\n");
                } else {
                    printf("Il vertice non è presente nel grafo\n");
                }

                break;
            }
            case 8: {
                int fromName, toName;

                printf("Inserire il nome del vertice da cui far partire l'arco: ");
                scanf("%d", &fromName);

                if(graphExistsVertex(graphObject, fromName)) {
                    printf("Inserire il nome del vertice in cui far arrivare l'arco: ");
                    scanf("%d", &toName);

                    if(graphExistsVertex(graphObject, toName)) {
                        graphInsertEdge(graphObject, fromName, toName);

                        printf("Arco inserito!\n");
                    } else {
                        printf("Vertice di arrivo non presente nel grafo!\n");
                    }
                } else {
                    printf("Vertice di partenza non presente nel grafo!\n");
                }

                break;
            }
            case 9: {
                int fromName, toName;

                printf("Inserire il nome del vertice da cui parte l'arco che si vuole rimuovere: ");
                scanf("%d", &fromName);

                if(graphExistsVertex(graphObject, fromName)) {
                    printf("Inserire il nome del vertice in cui arriva l'arco che si vuole rimuovere: ");
                    scanf("%d", &toName);

                    if(graphExistsVertex(graphObject, toName)) {
                        graphRemoveEdge(graphObject, fromName, toName);
                        printf("Arco rimosso dal grafo!\n");
                    } else {
                        printf("Il vertice di arrivo dell'arco che si vuole rimuovere non è presente nel grafo!\n");
                    }
                } else {
                    printf("Il vertice di partenda dell'arco che si vuole rimuovere non è presente nel grafo!\n");
                }

                break;
            }
            case 10: {
                int fromName, toName;

                printf("Inserire il nome del vertice da cui parte l'arco di cui si vuole controllare l'esitenza: ");
                scanf("%d", &fromName);

                if(graphExistsVertex(graphObject, fromName)) {
                    printf("Inserire il nome del vertice in cui arriva l'arco di cui si vuole controllare l'esitenza: ");
                    scanf("%d", &toName);

                    if(graphExistsVertex(graphObject, toName)) {
                        if(graphExistsEdge(graphObject, fromName, toName)) {
                            printf("L'arco è presente nel grafo!\n");
                        } else {
                            printf("L'arco non è presente nel graf!\n");
                        }
                    } else {
                        printf("Il vertice di arrivo dell'arco che si vuole analizzare non è presente nel grafo!\n");
                    }
                } else {
                    printf("Il vertice di partenza dell'arco che si vuole analizzare non è presente nel grafo!\n");
                }

                break;
            }
            case 11: { break;}
            case 12: { break;}
            case 13: {
                if(graphEmpty(graphObject)) {
                    printf("Il grafo è vuoto!\n");
                } else {
                    printf("Il grafo non è vuoto!\n");
                }

                break;
            }
            case 14: {
                printf("Il grafo contiene %d nodi.\n", graphVertexNumber(graphObject));
                break;
            }
            case 15: {
                printf("Il grafo contiene %d archi.\n", graphEdgeNumber(graphObject));
                break;
            }
            case 16: {
                graphClear(graphObject);
                printf("Il grafo è stato svuotato!\n");
                break;
            }
            case 17: {
                GraphObject* clonedGraph = graphClone(graphObject);

                ITRObject* vertexIterator = graphVertices(clonedGraph);

                if(itrTerminated(vertexIterator)) {
                    printf("Grafo vuoto!\n");
                } else {
                    while(!itrTerminated(vertexIterator)) {
                        int name = ((Vertex*)itrElement(vertexIterator))->name;
                        DataObject* label = ((Vertex*)itrElement(vertexIterator))->label;
                        printf("Nome: %d, Etichetta: ", name);
                        adtWriteToMonitor(label);

                        printf(" - Adiacenti: ");
                        ITRObject* adjacentIterator = graphVertexEdges(graphObject, name);

                        while(!itrTerminated(adjacentIterator)) {
                            printf("%d, ", ((Vertex*)itrElement(adjacentIterator))->name);
                            itrSuccessor(adjacentIterator);
                        }

                        itrDestruct(adjacentIterator);

                        itrSuccessor(vertexIterator);
                        printf("\n");
                    }
                }

                itrDestruct(vertexIterator);
                graphDestruct(clonedGraph);

                break;
            }
            case 18: {
                GraphObject* transposedGraph = graphTranspose(graphObject);

                ITRObject* vertexIterator = graphVertices(transposedGraph);

                if(itrTerminated(vertexIterator)) {
                    printf("Grafo vuoto!\n");
                } else {
                    while (!itrTerminated(vertexIterator)) {
                        int name = ((Vertex *) itrElement(vertexIterator))->name;
                        DataObject *label = ((Vertex *) itrElement(vertexIterator))->label;
                        printf("Nome: %d, Etichetta: ", name);
                        adtWriteToMonitor(label);

                        printf(" - Adiacenti: ");
                        ITRObject *adjacentIterator = graphVertexEdges(transposedGraph, name);

                        while (!itrTerminated(adjacentIterator)) {
                            printf("%d, ", ((Vertex *) itrElement(adjacentIterator))->name);
                            itrSuccessor(adjacentIterator);
                        }

                        itrDestruct(adjacentIterator);

                        itrSuccessor(vertexIterator);
                        printf("\n");
                    }
                }

                itrDestruct(vertexIterator);
                graphDestruct(transposedGraph);

                break;
            }
            case 0: {
                graphDestruct(graphObject);
                printf("Grafo deallocato!\n");

                switch(repType) {
                    case 1: {
                        DestructGraphLst(graphType->graphRep);
                        break;
                    }
                    case 2: {
                        DestructGraphMat(graphType->graphRep);
                        break;
                    }
                    case 3: {
                        DestructGraphBST(graphType->graphRep);
                        break;
                    }
                    default: { break; }
                }
                printf("Rappresentazione grafo deallocata!\n");

                adtDestruct(dataPtr);
                printf("DataObject deallocato!\n");

                switch(tipoDatoScelto) {
                    case 1: {
                        DestructIntDataType(datatype);
                        break;
                    }
                    case 2: {
                        DestructFloatDataType(datatype);
                        break;
                    }
                    case 3: {
                        DestructStringDataType(datatype);
                        break;
                    }
                    case 4: {
                        DestructRecordDataType(datatype);
                    }
                    default: { break; }
                }
                printf("DataType deallocato!\n");

                break;
            }
            default: {
                printf("Opzione non valida!\n");
                break;
            }
        }
    } while (scelta != 0);
}
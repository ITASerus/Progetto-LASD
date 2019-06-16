/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "testGraph.h"

/* *********************** FUNZIONI MAP E FOLD ******************************* */

void mapSquareInteger(DataObject* dat, void* _);
void mapDoubleFloat(DataObject* dat, void* _);
void mapLowerCase(DataObject* dat, void* _);
void mapUpperCase(DataObject* dat, void* _);
void foldProdLesserThanN(DataObject* dat, void *val, void *n);
void foldSumGreaterThanN(DataObject* dat, void *val, void *n);
void foldSumNumCharStrLessOrEqThanN(DataObject* dat, void *val, void *n);
void foldConcatLessOrEqThanN(DataObject * dat, void *val, void *n);

/* ************************************************************************** */

void testGraph() {
    char* buffer = (char*)malloc(sizeof(char) * MaxStrLen); //Buffer riservato all'input dell'utente

    GraphType* graphType = (GraphType*)malloc(sizeof(GraphType));

    int repType, number, scelta;
    printf("Inserire tipologia di struttra da utilizzare\n(1) Liste di adiacenza\n(2) Matrice di Adiacenza\n(3) Alberi di adiacenza\n");
    do {
        printf("Scelta: ");
        getStr(buffer, MaxStrLen);
        repType = strtol(buffer, NULL, 10);
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
        getStr(buffer, MaxStrLen);
        scelta = strtol(buffer, NULL, 10);
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
        getStr(buffer, MaxStrLen);
        tipoDatoScelto = strtol(buffer, NULL, 10);
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
               "(2) Visualizzazione dei vertici contenuti nel grafo\n"
               "(3) Visualizzazione del grafo e degli adiacente di ogni vertice\n"
               "\n"
               "(5) Inserimento manuale di un vertice nel grafo\n"
               "(6) Rimozione di un vertice dal grafo\n"
               "(7) Controllo esistenza di un vertice\n"
               "\n"
               "(8) Inserimento manuale di un arco tra due vertici presenti nel grafo\n"
               "(9) Rimozione di un arco dal grafo\n"
               "(10) Controllo esistenza di un arco tra due vertici presenti nel grafo\n"
               "\n(11) Etichetta di un vertice dato il nome\n"
               "(12) Modifica dell'etichetta di un vertice dato il nome\n");
        switch (tipoDatoScelto) {
            case 1: { //Interi
                printf("\n(13) Prodotto di ogni elemento minore di N\n"
                       "(14) Applicazione 2n per ogni elemento\n");
                break;
            }
            case 2: { //Float
                printf("\n(13) Somma valori maggiori di N\n"
                       "(14) Applicazione n^2 per ogni elemento\n");
                break;
            }
            case 3: { //Stringhe
                printf("\n(13) Concatenazione dei valori di lunghezza minore o uguale a N\n"
                       "(14) Applicazione funzione uppercase/lowercase per ogni elemento\n");
                break;
            }
            default: { //Record
                printf("\n(13) N/A\n"
                       "(14) N/A\n");
                break;
            }
        }
        printf("\n(15) Controllo vuotezza del grafo\n"
               "(16) Numero di nodi contenuti nel grafo\n"
               "(17) Numero di archi contenuti nel grafo\n"
               "(18) Svuotamento del grafo\n"
               "(19) Creazione e stampa di un clone del grafo e\n"
               "     controllo uguaglianza con il grafo principale\n"
               "(20) Creazione e stampa del trasposto del grafo\n"
               "\n"
               "(0) Deallocazione della stuttura ed uscita dal programma\n"
               "Scelta: ");
        getStr(buffer, MaxStrLen);
        scelta = strtol(buffer, NULL, 10);
        switch (scelta) {
            case 1: {
                int numVertex;
                printf("Numero di vertici da inserire nel grafo: ");
                getStr(buffer, MaxStrLen);
                numVertex = strtol(buffer, NULL, 10);

                int* vertexReference = (int*)malloc(sizeof(int) * numVertex); //Vettore utilizzato per creare gli archi successivamente

                int vertexName;
                for(int i = 0; i < numVertex; i++) {
                    adtRandomValue(dataPtr);

                    vertexName = rndNum(-250, 250);
                    graphInsertVertex(graphObject, vertexName, dataPtr);

                    vertexReference[i] = vertexName;
                }

                printf("Numero di archi da inserire nel grafo: ");
                getStr(buffer, MaxStrLen);
                number = strtol(buffer, NULL, 10);

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
                ITRObject* vertexIterator = graphVertices(graphObject);

                if(itrTerminated(vertexIterator)) {
                    printf("Grafo vuoto!\n");
                } else {
                    while(!itrTerminated(vertexIterator)) {
                        printf("Nome Vertice: %d\n", ((Vertex*)itrElement(vertexIterator))->name);
                        itrSuccessor(vertexIterator);
                    }
                }

                itrDestruct(vertexIterator);

                break;
            }
            case 3: {
                ITRObject* vertexIterator = graphVertices(graphObject);

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
                break;
            }
            case 4: {
                printf("Da implementare\n");
                break;
            }
            case 5: {
                printf("Inserire il nome del nuovo vertice: ");
                getStr(buffer, MaxStrLen);
                number = strtol(buffer, NULL, 10);
                printf("%d\n", number);

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
                getStr(buffer, MaxStrLen);
                number = strtol(buffer, NULL, 10);

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
                getStr(buffer, MaxStrLen);
                number = strtol(buffer, NULL, 10);

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
                getStr(buffer, MaxStrLen);
                fromName = strtol(buffer, NULL, 10);

                if(graphExistsVertex(graphObject, fromName)) {
                    printf("Inserire il nome del vertice in cui far arrivare l'arco: ");
                    getStr(buffer, MaxStrLen);
                    toName = strtol(buffer, NULL, 10);

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
                getStr(buffer, MaxStrLen);
                fromName = strtol(buffer, NULL, 10);

                if(graphExistsVertex(graphObject, fromName)) {
                    printf("Inserire il nome del vertice in cui arriva l'arco che si vuole rimuovere: ");
                    getStr(buffer, MaxStrLen);
                    toName = strtol(buffer, NULL, 10);

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
                getStr(buffer, MaxStrLen);
                fromName = strtol(buffer, NULL, 10);

                if(graphExistsVertex(graphObject, fromName)) {
                    printf("Inserire il nome del vertice in cui arriva l'arco di cui si vuole controllare l'esitenza: ");
                    getStr(buffer, MaxStrLen);
                    toName = strtol(buffer, NULL, 10);

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
            case 11: {
                printf("Inserire il nome del vertice di cui si vuole sapere l'etichetta: ");
                getStr(buffer, MaxStrLen);
                number = strtol(buffer, NULL, 10);

                if (graphExistsVertex(graphObject, number)) {
                    DataObject *data = graphGetVertexData(graphObject, number);

                    printf("Il valore dell'etichetta del vertice %d è: ", number);
                    adtWriteToMonitor(data);

                    adtDestruct(data);
                } else {
                    printf("Vertice non presente nel grafo!\n");
                }

                break;
            }
            case 12: {
                printf("Inserire il nome del vertice di cui si vuole modificare l'etichetta: ");
                getStr(buffer, MaxStrLen);
                number = strtol(buffer, NULL, 10);

                if (graphExistsVertex(graphObject, number)) {
                    DataObject *data = adtConstruct(datatype);

                    printf("Inserire il nuovo valore dell'etichetta del vertice %d: ", number);
                    adtReadFromKeyboard(data);

                    graphSetVertexData(graphObject, number, data);

                    printf("Il valore dell'etichetta del vertice %d è stato modificato!\n", number);

                    adtDestruct(data);
                } else {
                    printf("Vertice non presente nel grafo!\n");
                }

                break;

            }
            case 13: {
                switch (tipoDatoScelto) {
                    case 1: { //Int
                        int* value = (int*)malloc(sizeof(int));
                        *value = 1;

                        int* n = (int*)malloc(sizeof(int));
                        printf("Inserire N: ");
                        getStr(buffer, MaxStrLen);
                        *n = strtol(buffer, NULL, 10);

                        graphPreOrderFold(graphObject, foldProdLesserThanN, value, n);
                        printf("Risultato: %d\n", *value);

                        free(value);
                        free(n);

                        break;
                    }
                    case 2: { //Float
                        float* value = (float*)malloc(sizeof(float));
                        *value = 0;

                        float* n = (float*)malloc(sizeof(float));
                        printf("Inserire N: ");
                        getStr(buffer, MaxStrLen);
                        *n = strtof(buffer, NULL);

                        graphPreOrderFold(graphObject, foldSumGreaterThanN, value, n);
                        printf("Risultato: %f\n", *value);

                        free(value);
                        free(n);

                        break;
                    }
                    case 3: { //String
                        int* n = (int*)malloc(sizeof(int));
                        printf("Inserire N: ");
                        getStr(buffer, MaxStrLen);
                        *n = strtol(buffer, NULL, 10);

                        int* value = (int*)malloc(sizeof(int));
                        *value = 0;
                        graphPreOrderFold(graphObject, foldSumNumCharStrLessOrEqThanN, value, n);
                        char* strResult = (char*)malloc(sizeof(char) * (*(int*)value));
                        strcpy(strResult, "");

                        graphPreOrderFold(graphObject, foldConcatLessOrEqThanN, strResult, n);
                        printf("Risultato: %s\n", strResult);

                        free(value);
                        free(n);
                        free(strResult);

                        break;
                    }
                    default: break; //Record
                }

                break;
            }
            case 14: {
                switch (tipoDatoScelto) {
                    case 1: { //Int
                        graphPreOrderMap(graphObject, mapSquareInteger, NULL);
                        printf("Operazione effettuata!\n");
                        break;
                    }
                    case 2: { //Float
                        graphPreOrderMap(graphObject, mapDoubleFloat, NULL);
                        printf("Operazione effettuata!\n");
                        break;
                    }
                    case 3: { //String
                        printf("(1) Applica funzione upperCase\n(2) Applica funzione lowerCase\nScelta: ");
                        getStr(buffer, MaxStrLen);
                        scelta = strtol(buffer, NULL, 10);
                        switch (scelta) {
                            case 1: {
                                graphPreOrderMap(graphObject, mapUpperCase, NULL);
                                printf("Operazione effettuata!\n");
                                break;
                            }
                            case 2: {
                                graphPreOrderMap(graphObject, mapLowerCase, NULL);
                                printf("Operazione effettuata!\n");
                                break;
                            }
                            default: {
                                printf("Scleta non valida\n");
                                break;
                            }
                        }
                        break;
                    }
                    default: break; //Record
                }

                break;
            }
            case 15: {
                if(graphEmpty(graphObject)) {
                    printf("Il grafo è vuoto!\n");
                } else {
                    printf("Il grafo non è vuoto!\n");
                }

                break;
            }
            case 16: {
                printf("Il grafo contiene %d nodi.\n", graphVertexNumber(graphObject));
                break;
            }
            case 17: {
                printf("Il grafo contiene %d archi.\n", graphEdgeNumber(graphObject));
                break;
            }
            case 18: {
                graphClear(graphObject);
                printf("Il grafo è stato svuotato!\n");
                break;
            }
            case 19: {
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

                printf("I grafi sono uguali?: ");
                if(graphEqual(graphObject, clonedGraph)) {
                    printf("Sì!\n");
                } else {
                    printf("No!\n"); //Condizione che non si verificherà mai. Inserita a puro scopo di verifica didattica
                }

                graphDestruct(clonedGraph);

                break;
            }
            case 20: {
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

                free(buffer);
                printf("Buffer deallocato!\n");
                break;
            }
            default: {
                printf("Opzione non valida!\n");
                break;
            }
        }
    } while (scelta != 0);
}


/**
 * Dato un DataObject di DataType INTEGER, ne assegna il quadrato
 * @param dat DataObject INTEGER di cui si vuole ottenere il quadrato
 * @param _ NULL
 */
void mapSquareInteger(DataObject* dat, void* _) {
    *(int*)dat->value = (*(int*)dat->value)*(*(int*)dat->value);
}

/**
 * Dato un DataObject di DataType FLOAT, ne raddoppia il valore
 * @param dat DataObject FLOAT di cui si vuole raddoppiare il valore
 * @param _ NULL
 */
void mapDoubleFloat(DataObject* dat, void* _) {
    *(float*)dat->value *= 2;
}

/**
 * Dato un DataObject di DataType CHAR* (STRING), ne converte tutti i caratteri in minuscolo
 * @param dat DataObject CHAR* (STRING) di cui si vuole convertire i caratteri
 * @param _ NULL
 */
void mapLowerCase(DataObject* dat, void* _) {
    for(int i = 0; i<strlen((char*)dat->value); i++) {
        if((((char*)dat->value)[i] >= 65) && (((char*)dat->value)[i]<=90)) {
            ((char*)dat->value)[i] += 32;
        }
    }
}

/**
 * Dato un DataObject di DataType CHAR* (STRING), ne converte tutti i caratteri in maiuscolo
 * @param dat DataObject CHAR* (STRING) di cui si vuole convertire i caratteri
 * @param _ NULL
 */
void mapUpperCase(DataObject* dat, void* _) {
    for(int i = 0; i<strlen((char*)dat->value); i++) {
        if((((char*)dat->value)[i] >= 97) && (((char*)dat->value)[i]<=122)) {
            ((char*)dat->value)[i] -= 32;
        }
    }
}

/**
 * Dato un DataObject INTEGER 'dat', se il valore di 'dat' è minore di 'n', viene sommato a 'val' il valore di 'dat'
 * @param dat DataObject INTEGER in esame
 * @param val Valore al quale, a condizione soddisfatta, verrà sommato 'dat'
 * @param n Valore di riferimento della condizione
 */
void foldProdLesserThanN(DataObject* dat, void *val, void *n) {
    if(*(int*)dat->value < *(int*)n) {
        *(int*)val *= *(int*)dat->value;
    }
}

/**
 *  Dato un DataObject FLOAT 'dat', se il valore di 'dat' è maggiore di 'n', viene moltiplicato a 'val' il valore di 'dat'
 * @param dat DataObject FLOAT in esame
 * @param val Valore al quale, a condizione soddisfatta, verrà moltiplicato 'dat'
 * @param n Valore di riferimento della condizione
 */
void foldSumGreaterThanN(DataObject* dat, void *val, void *n) { //TODO: Non funziona bene sembra
    if((*(float*)dat->value > *(int*)n)) {
        *(float*)val += *(float*)dat->value;
    }
}

/**
 * Dato un DataObject CHAR* (STRING) 'dat', se il numero di caratteri di 'dat' è minore o uguale a 'n', viene sommato a 'val' il numero di caratteri di 'dat'
 * @param dat DataObject CHAR* (STRING) in esame
 * @param val Valore al quale, a condizione soddisfatta, verrà sommato il numero di caratteri di 'dat'
 * @param n Valore di riferimento della condizione
 */
void foldSumNumCharStrLessOrEqThanN(DataObject* dat, void *val, void *n) {
    if( strlen((char*)dat->value) <= *(int*)n ) {
        *(int*)val += strlen((char*)dat->value);
    }
}

/**
 * Dato un DataObject CHAR* (STRING) 'dat', se il numero di caratteri di 'dat' è minore o uguale a 'n', viene concatenato a 'val' il valore di 'dat'
 * @param dat DataObject CHAR* (STRING) in esame
 * @param val Valore al quale, a condizione soddisfatta, verrà concatenato il valore di 'dat'
 * @param n Valore di riferimento della condizione
 */
void foldConcatLessOrEqThanN(DataObject * dat, void *val, void *n) {
    if((strlen((char*)dat->value) <= *(int*)n)) {
        strcat(val, dat->value);
    }
}
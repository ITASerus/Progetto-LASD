
#include "testBST.h"

void printStructBST(DataObject* dat, void* _) {
    printf(" | ");
    adtWriteToMonitor(dat);
}

void testBST() {
    BSTType* bstTyp = NULL;
    DataType* dataType = NULL;

    int scelta, number, tipoScelto;

    printf("Inserire tipologia di albero da utilizzare\n(1) Ricorsivo\n(2) Iterativo\n");
    do {
        printf("Scelta: ");
        //scanf("%d", &scelta);
        char* buffer = (char*)malloc(sizeof(char)*10);
        getStr(buffer, 10);
        scelta = strtol(buffer, NULL, 10);

        switch (scelta) {
            case 1: {
                bstTyp = ConstructBSTRecursive();
                break;
            }
            case 2: {
                bstTyp = ConstructBSTIterative();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Ricorsivo\n(2) Iterativo\n");
                break;
            }
        }
    } while (scelta != 1 && scelta != 2);

    printf("Inserire tipologia di dato da gestire\n(1) Intero\n(2) Float\n(3) Stringhe\n(4) Record\n");
    do {
        printf("Scelta: ");
        scanf("%d", &tipoScelto);
        switch (tipoScelto) {
            case 1: {
                dataType = ConstructIntDataType();
                break;
            }
            case 2: {
                dataType = ConstructFloatDataType();
                break;
            }
            case 3: {
                dataType = ConstructStringDataType();
                break;
            }
            case 4: {
                dataType = ConstructRecordDataType();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Intero\n(2) Float\n(3) Stringhe\n(4) Record\n");
                break;
            }
        }
    } while( (tipoScelto<1) || (tipoScelto >4));


    BSTObject* bst = bstConstruct(bstTyp);
    DataObject* dataPtr;

    do {
        printf("\n***********************************************************************************************\n\n");
        printf("Menu':\n"
               "(1) Popolamento randomico dell'albero con N elementi\n"
               "\n"
               "(2) Visualizzazione del contenuto dell'albero Pre-Order\n"
               "(3) Visualizzazione del contenuto dell'albero In-Order\n"
               "(4) Visualizzazione del contenuto dell'albero Post-Order\n"
               "(5) Visualizzazione del contenuto dell'albero in ampiezza\n"
               "\n"
               "(6) Inserimento manuale di un elemento\n"
               "\n"
               "(7) Rimozione di un elemento\n"
               "\n"
               "(8) Lettura dell'elemento minimo\n"
               "(9) Rimozione dell'elemento minimo\n"
               "(10) Lettura e rimozione dell'elemento minimo\n"
               "\n"
               "(11) Lettura dell'elemento massimo\n"
               "(12) Rimozione dell'elemento massimo\n"
               "(13) Lettura e rimozione dell'elemento massimo\n"
               "\n"
               "(14) Lettura del predecessore di un elemento\n"
               "(15) Rimozione del predecessore di un elemento\n"
               "(16) Lettura e rimozione del predecessore di un elemento\n"
               "\n"
               "(17) Lettura del successore di un elemento\n"
               "(18) Rimozione del successore di un elemento\n"
               "(19) Lettura e rimozione del successore di un elemento\n"
               "\n"
               "(20) Controllo vuotezza dell'albero\n"
               "(21) Numero di nodi contenuti nell'albero\n"
               "(22) Svuotamento dell'albero\n"
               "(23) Ricerca di un elemento nell'albero\n"
               "(24) Creazione e stampa di un clone dell'albero e\n"
               "     controllo uguaglianza con l'albero principale\n"
               "\n"
               "(0) Deallocazione della stuttura ed uscita dal programma\n"
               "Scelta: ");

        dataPtr = adtConstruct(dataType);

        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                printf("Numero di elementi da inserire nell'albero: ");
                scanf("%d", &number);

                for(int i = 0; i < number; i++) {
                    adtRandomValue(dataPtr);
                    bstInsert(bst, dataPtr);
                }

                printf("Elementi inseriti!\n");
                break;
            }

            case 2: {
                if(bstSize(bst) > 0) {
                    bstPreOrderMap(bst, printStructBST, NULL);
                } else {
                    printf("L'albero è vuoto!\n");
                }
                break;
            }
            case 3: {
                if(bstSize(bst) > 0) {
                    bstInOrderMap(bst, printStructBST, NULL);
                } else {
                    printf("L'albero è vuoto!\n");
                }
                break;
            }
            case 4: {
                if(bstSize(bst) > 0) {
                    bstPostOrderMap(bst, printStructBST, NULL);
                } else {
                    printf("L'albero è vuoto!\n");
                }
                break;
            }
            case 5: {
                if(bstSize(bst) > 0) {
                    bstBreadthMap(bst, printStructBST, NULL);
                } else {
                    printf("L'albero è vuoto!\n");
                }
                break;
            }

            case 6: {
                printf("Valore da inserire: ");
                adtReadFromKeyboard(dataPtr);
                bstInsert(bst, dataPtr);
                printf("Valore inserito!\n");
                break;
            }

            case 7: {
                printf("Valore da rimuovere: ");
                adtReadFromKeyboard(dataPtr);
                bstRemove(bst, dataPtr);
                printf("Valore rimosso!");
                break;
            }

            case 8: {
                if((dataPtr = bstGetMin(bst)) != NULL) {
                    printf("Elemento minimo nell'albero: ");
                    adtWriteToMonitor(dataPtr);
                } else {
                    printf("\nL'albero è vuoto!\n");
                }
                break;
            }
            case 9: {
                if(bstSize(bst) > 0) {
                    bstRemoveMin(bst);
                    printf("\nElemento minimo rimosso!\n");
                } else {
                    printf("\nL'albero è vuoto!\n");
                }
                break;
            }
            case 10: {
                if((dataPtr = bstGetNRemoveMin(bst)) != NULL) {
                    printf("Elemento minimo nell'albero: ");
                    adtWriteToMonitor(dataPtr);
                    printf("\nElemento rimosso.\n");
                } else {
                    printf("\nL'albero è vuoto!\n");
                }
                break;
            }

            case 11: {
                if((dataPtr = bstGetMax(bst)) != NULL) {
                    printf("Elemento massimo nell'albero: ");
                    adtWriteToMonitor(dataPtr);
                } else {
                    printf("\nL'albero è vuoto!\n");
                }
                break;
            }
            case 12: {
                if(bstSize(bst) > 0) {
                    bstRemoveMax(bst);
                    printf("\nElemento massimo rimosso!\n");
                } else {
                    printf("\nL'albero è vuoto!\n");
                }
                break;
            }
            case 13: {
                if((dataPtr = bstGetNRemoveMax(bst)) != NULL) {
                    printf("Elemento massimo nell'albero: ");
                    adtWriteToMonitor(dataPtr);
                    printf("\nElemento rimosso.\n");
                } else {
                    printf("\nL'albero è vuoto!\n");
                }
                break;
            }

            case 14: {
                printf("Elemento di cui si vuole sapere il predecessore: ");
                adtReadFromKeyboard(dataPtr);
                if((dataPtr = bstGetPredecessor(bst, dataPtr))) {
                    printf("Il predecessore è ");
                    adtWriteToMonitor(dataPtr);
                    printf("\n");
                } else {
                    printf("Non esiste predecessore\n");
                }
                break;
            }
            case 15: {
                if(bstSize(bst) > 0) {
                    printf("Elemento di cui si vuole rimuovere il predecessore: ");
                    adtReadFromKeyboard(dataPtr);
                    bstRemovePredecessor(bst, dataPtr);
                    printf("\nPredecessore rimosso!\n");
                } else {
                    printf("\nL'albero è vuoto!\n");
                }
                break;
            }
            case 16: {
                printf("Elemento di cui si vuole sapere il predecessore: ");
                adtReadFromKeyboard(dataPtr);
                if((dataPtr = bstGetNRemovePredecessor(bst, dataPtr))) {
                    printf("Il predecessore è ");
                    adtWriteToMonitor(dataPtr);
                    printf("\nElemento rimosso\n");
                } else {
                    printf("Non esiste predecessore\n");
                }
                break;
            }
            case 17: {
                printf("Elemento di cui si vuole sapere il successore: ");
                adtReadFromKeyboard(dataPtr);
                if((dataPtr = bstGetSuccessor(bst, dataPtr))) {
                    printf("Il successore è ");
                    adtWriteToMonitor(dataPtr);
                    printf("\n");
                } else {
                    printf("Non esiste successore\n");
                }
                break;
            }
            case 18: {
                if(bstSize(bst) > 0) {
                    printf("Elemento di cui si vuole rimuovere il successore: ");
                    adtReadFromKeyboard(dataPtr);
                    bstRemoveSuccessor(bst, dataPtr);
                    printf("\nSuccessore rimosso!\n");
                } else {
                    printf("\nL'albero è vuoto!\n");
                }
                break;
            }
            case 19: {
                printf("Elemento di cui si vuole sapere il successore: ");
                adtReadFromKeyboard(dataPtr);
                if((dataPtr = bstGetNRemoveSuccessor(bst, dataPtr))) {
                    printf("Il successore è ");
                    adtWriteToMonitor(dataPtr);
                    printf("\nElemento rimosso\n");
                } else {
                    printf("Non esiste successore\n");
                }
                break;
            }

            case 20: {
                if(bstEmpty(bst)) {
                    printf("L'albero è vuoto\n");
                } else {
                    printf("L'albero NON è vuoto\n");
                }
                break;
            }
            case 21: {
                printf("Il numero di nodi contenuti nell'albero è: %d\n", bstSize(bst));
                break;
            }
            case 22: {
                bstClear(bst);
                printf("Albero svuotato!\n");
                break;
            }
            case 23: {
                printf("Inserire valore da cercare: ");
                adtReadFromKeyboard(dataPtr);

                if(bstExists(bst, dataPtr)) {
                    printf("Il valore è presente nell'albero\n");
                } else {
                    printf("Il valore NON è presente nell'albero\n");
                }
                break;
            }
            case 24: {
                BSTObject* clone = bstClone(bst);
                bstPreOrderMap(clone, printStructBST, NULL);
                printf("\nControllo di uguaglianza tra il clone dell'albero e l'albero principale: ");
                if(bstEqual(clone, bst)) {
                    printf("VERO\n");
                } else {
                    printf("FALSO\n");
                }

                printf("\nAggiunta di un ulteriore elemento al clone\n");
                adtRandomValue(dataPtr);
                bstInsert(clone, dataPtr);
                bstPreOrderMap(clone, printStructBST, NULL);

                printf("\nControllo di uguaglianza tra il clone dell'albero e l'albero principale: ");
                if(bstEqual(clone, bst)) {
                    printf("VERO\n");
                } else {
                    printf("FALSO\n");
                }

                bstDestruct(clone);
                break;
            }
            case 0: {
                bstDestruct(bst);
                break;
            }
            default: {
                printf("Opzione non valida!\n");
                break;
            }
        }
    } while (scelta != 0);
}
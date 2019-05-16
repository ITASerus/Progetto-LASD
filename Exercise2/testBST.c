
#include "testBST.h"

void printStructBST(DataObject* dat, void* _) {
    printf("> ");
    adtWriteToMonitor(dat);
    printf("\n");
}

void testBST() {
    BSTType* bstTyp = ConstructBSTRecursive();
    DataType* dataType = ConstructIntDataType();

    BSTObject* bst = bstConstruct(bstTyp);
    DataObject* dataPtr = adtConstruct(dataType);


    int number;
    printf("\n\nNumero di elementi da inserire nell'albero: ");
    scanf("%d", &number);

    for(int i = 0; i < number; i++) {
        adtRandomValue(dataPtr);
        bstInsert(bst, dataPtr);
    }
    printf("Elementi inseriti!\n\n");

    bstPreOrderMap(bst, printStructBST, NULL);

    printf("\n************************************\n\n");

    printf("Inserisco due volte lo stesso elemento\n");
    int* valore = malloc(sizeof(int));
    *valore = 8;
    adtSetValue(dataPtr,valore);
    bstInsert(bst, dataPtr);
    bstInsert(bst, dataPtr);
    printf("\n");
    bstPreOrderMap(bst, printStructBST, NULL);

    printf("\n************************************\n\n");

    *valore = 4;
    adtSetValue(dataPtr,valore);
    adtWriteToMonitor(dataPtr);
    if(bstExists(bst, dataPtr)) {
        printf(" - Il valore esiste nell'albero\n");
    } else {
        printf(" - Il valore NON esiste nell'albero\n");
    }

    printf("\n************************************\n\n");

    BSTObject* bst2;
    printf("Albero clonato:\n");
    bst2 = bstClone(bst);
    bstPreOrderMap(bst2, printStructBST, NULL);

    if(bstEqual(bst, bst2)) {
        printf("\nGli alberi sono uguali\n");
    } else {
        printf("\nGli alberi NON sono uguali\n");
    }

    printf("\n************************************\n\n");

    adtWriteToMonitor(dataPtr);
    bstInsert(bst2, dataPtr);
    printf(" - Aggiunto l'elemento all'albero clone\n");
    printf("BST:\n");
    bstPreOrderMap(bst, printStructBST, NULL);
    printf("BST CLONE:\n");
    bstPreOrderMap(bst2, printStructBST, NULL);
    if(bstEqual(bst, bst2)) {
        printf("Gli alberi sono uguali\n");
    } else {
        printf("Gli alberi NON sono uguali\n");
    }

    printf("\n************************************\n");

    printf("\nNodo con valore minimo: ");
    adtWriteToMonitor(bstGetMin(bst));
    printf("\nNodo con valore massimo: ");
    adtWriteToMonitor(bstGetMax(bst));

    printf("\n\n************************************\n");

    printf("\nRimuovo il nodo ");
    adtWriteToMonitor(bstGetMin(bst));
    printf(":\nPRIMA:\n");
    bstPreOrderMap(bst, printStructBST, NULL);
    bstRemove(bst, bstGetMin(bst));
    printf("DOPO:\n");
    bstPreOrderMap(bst, printStructBST, NULL);

    printf("\n************************************\n");
    printf("\nAlbero:\n");
    bstPreOrderMap(bst, printStructBST, NULL);

    printf("\nCerco, restituisco e rimuovo il minimo.\n");
    if((dataPtr = bstGetNRemoveMin(bst)) != NULL) {
        printf("Minimo: ");
        adtWriteToMonitor(dataPtr);

        printf("\nAlbero dopo la getNRemoveMin:\n");
        bstPreOrderMap(bst, printStructBST, NULL);
    } else {
        printf("L'albero è vuoto!\n");
    }

    printf("\n************************************\n");
    printf("\nAlbero:\n");
    bstPreOrderMap(bst, printStructBST, NULL);

    printf("\nCerco, restituisco e rimuovo il massimo.\n");
    if((dataPtr = bstGetNRemoveMax(bst)) != NULL) {
        printf("Massimo: ");
        adtWriteToMonitor(dataPtr);

        printf("\nAlbero dopo la getNRemoveMax:\n");
        bstPreOrderMap(bst, printStructBST, NULL);
    } else {
        printf("L'albero è vuoto!\n");
    }

    printf("\n************************************\n");
    printf("\nAlbero:\n");
    bstPreOrderMap(bst, printStructBST, NULL);

    printf("\nCerco e rimuovo il minimo.\n");
    bstRemoveMin(bst);

    printf("\nAlbero dopo la removeMin:\n");
    bstPreOrderMap(bst, printStructBST, NULL);

    printf("\n************************************\n");
    printf("\nAlbero:\n");
    bstPreOrderMap(bst, printStructBST, NULL);

    printf("\nCerco e rimuovo il massimo.\n");
    bstRemoveMax(bst);

    printf("\nAlbero dopo la removeMax:\n");
    bstPreOrderMap(bst, printStructBST, NULL);


    bstDestruct(bst);
    bstDestruct(bst2);
}
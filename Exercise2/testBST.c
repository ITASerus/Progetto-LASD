
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
    printf("Numero di elementi da inserire nell'albero: ");
    scanf("%d", &number);

    for(int i = 0; i < number; i++) {
        adtRandomValue(dataPtr);
        bstInsert(bst, dataPtr);
    }
    printf("Elementi inseriti!\n\n");

    bstPreOrderMap(bst, printStructBST, NULL);

    int* valore = malloc(sizeof(int));
    *valore = 4;
    adtSetValue(dataPtr,valore);
    adtWriteToMonitor(dataPtr);
    if(bstExists(bst, dataPtr)) {
        printf(" - Il valore esiste nell'albero\n\n");
    } else {
        printf(" - Il valore NON esiste nell'albero\n\n");
    }

    BSTObject* bst2;
    bst2 = bstClone(bst);
    bstPreOrderMap(bst2, printStructBST, NULL);
    printf("Albero clonato.\n");
    if(bstEqual(bst, bst2)) {
        printf("Gli alberi sono uguali\n\n");
    } else {
        printf("Gli alberi NON sono uguali\n\n");
    }

    adtWriteToMonitor(dataPtr);
    bstInsert(bst2, dataPtr);
    printf(" - Aggiunto l'elemento all'albero clone\n");
    printf("BST:\n");
    bstPreOrderMap(bst, printStructBST, NULL);
    printf("\nBST2:\n");
    bstPreOrderMap(bst2, printStructBST, NULL);
    if(bstEqual(bst, bst2)) {
        printf("Gli alberi sono uguali\n\n");
    } else {
        printf("Gli alberi NON sono uguali\n\n");
    }

    printf("Nodo con valore minimo: ");
    adtWriteToMonitor(bstGetMin(bst));
    printf("\nNodo con valore massimo: ");
    adtWriteToMonitor(bstGetMax(bst));

    printf("\n\nRimuovo il nodo ");
    adtWriteToMonitor(bstGetMin(bst));
    printf(":\nPRIMA:\n");
    bstPreOrderMap(bst, printStructBST, NULL);
    bstRemove(bst, bstGetMin(bst));
    printf("DOPO:\n");
    bstPreOrderMap(bst, printStructBST, NULL);

    bstDestruct(bst);
    bstDestruct(bst2);
}
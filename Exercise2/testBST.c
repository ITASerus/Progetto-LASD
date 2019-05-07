
#include "testBST.h"

void printStructBST(DataObject* dat, void* _) {
    printf("- ");
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
    printf("Elementi inseriti!\n");

    bstPreOrderMap(bst, printStructBST, NULL);
    printf("Elementi stampati!\n");
}
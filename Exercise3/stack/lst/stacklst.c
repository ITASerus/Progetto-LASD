/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "stacklst.h"

/* ************************************************************************** */

void* stkLstConstruct() {
    StackLst* obj = (StackLst*)malloc(sizeof(StackLst));

    obj->element = NULL;
    obj->next = NULL;

    return obj;
}

void stkLstDestruct(void* stack) {
    StackLst* stackList = stack;

    while(stackList->element != NULL) {
        adtDestruct(stackList->element);
        stackList = stackList->next;
    }

    free(stack);
}


bool stkLstEmpty(void* stack) {
    if(((StackLst*)stack)->next == NULL) {
        return true;
    } else {
        return false;
    }
}

void* stkLstTop(void* stack) {
    if(!stkLstEmpty(stack)) {
        return adtClone(((StackLst *) stack)->next->element);
    } else {
        return NULL;
    }
}

void stkLstPop(void* stack) {
    if(!stkLstEmpty(stack)) {
        StackLst *stackList = stack;

        adtDestruct(stackList->next->element);
        ((StackLst *) stack)->next = ((StackLst *) stack)->next->next;
    }
}

void* stkLstTopNPop(void* stack) {
    if(!stkLstEmpty(stack)) {
        StackLst* stackList = stack;

        DataObject *poppedElement = adtClone(stackList->next->element);
        stkLstPop(stackList);

        return poppedElement;
    } else {
        return NULL;
    }
}

void stkLstPush(void* stack, void* elem) {
    StackLst* newObj = (StackLst*)malloc(sizeof(StackLst));

    newObj->element = adtClone(elem);
    newObj->next = ((StackLst*)stack)->next;
    ((StackLst*)stack)->next = newObj;
}

void stkLstClear(void* stack) {
    if(!stkLstEmpty(stack)) {
        StackLst* stackList = ((StackLst*)stack)->next;

        while(stackList != NULL) {
            ((StackLst*)stack)->next = stackList->next;
            adtDestruct(stackList->element);
            free(stackList);
            stackList = ((StackLst*)stack)->next;
        }
    }
}


void* stkLstClone(void* stack) {
    StackLst* clonedStack = stkLstConstruct();

    StackLst* sentinelStackList = stack;
    StackLst* sentinelClonedStack = clonedStack;

    while(sentinelStackList->next != NULL) {
        StackLst* newNode = (StackLst*)malloc(sizeof(StackLst));
        newNode->element = adtClone(sentinelStackList->next->element);
        newNode->next = NULL;

        printf("Clono: ");
        adtWriteToMonitor(newNode->element);
        printf("\n");

        sentinelClonedStack->next = newNode;

        sentinelClonedStack = sentinelClonedStack->next;
        sentinelStackList = sentinelStackList->next;
    }

    return clonedStack;
}

bool stkLstEqual(void* firstStack, void* secondStack) {
    StackLst* firstStackList = firstStack;
    StackLst* secondStackList = secondStack;

    while(firstStackList->next != NULL && secondStackList->next != NULL) {
        if(adtCompare(firstStackList->next->element, secondStackList->next->element) != 0) {
            return false;
        }
        secondStackList = secondStackList->next;
        firstStackList = firstStackList->next;
    }

    if((firstStackList->next == NULL && secondStackList->next != NULL) || (firstStackList->next != NULL && secondStackList->next == NULL)) {
        return false;
    }

    return true;
}

void stkLstMap(void* stack, MapFun function, void* param) {
    StackLst* stackList = stack;

    while(stackList->next != NULL) {
        function(stackList->next->element, param);
        stackList = stackList->next;
    }
}

void stkLstFold(void* stack, FoldFun function, void* accumulator, void* param) {
    StackLst* stackList = stack;

    while(stackList->next != NULL) {
        function(stackList->next->element, accumulator, param);
        stackList = stackList->next;
    }
}

StackType* ConstructStackLstType() {
    StackType* type = (StackType*)malloc(sizeof(StackType));

    type->construct = stkLstConstruct;
    type->destruct = stkLstDestruct;

    type->isEmpty = stkLstEmpty;
    type->top = stkLstTop;
    type->pop = stkLstPop;
    type->topNPop = stkLstTopNPop;
    type->push = stkLstPush;
    type->clear = stkLstClear;

    type->clone = stkLstClone;
    type->equal = stkLstEqual;
    type->map  = stkLstMap;
    type->fold = stkLstFold;

    return type;
}

void DestructStackLstType(StackType* stackType) {
    free(stackType);
}
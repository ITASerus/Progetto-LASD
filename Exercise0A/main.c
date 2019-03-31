
#include "utility.h"

/* ************************************************************************** */

#include "stack/stack.h"

#include "queue/queue.h"

/* ************************************************************************** */

int main()
{
    srand(time(NULL));

    char * elemx = (char *) malloc(sizeof(char) * 20);
    char * elemy = NULL;
    int val = 0;

    /* ************************************************************************ */

    printf("Creazione Oggetto Stack\n\n");
    StackObject * stack = stkConstruct();

    strcpy(elemx, "stringaProva");
    stkPush(stack, elemx);

    for(uint i = 0; i < 17; i++)
    {
        strcpy(elemx, rndStr(rndNum(1, 10)));
        printf("Inserimento nello stack: %s\n", elemx);
        stkPush(stack, elemx);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("Stack at index: %s\n\n", stack->elements[stack->index]);

    for(uint i = 0; i < 10; i++)
    {
        elemy = (char *) stkTopNPop(stack);
        printf("Rimozione dallo stack: %s\n", elemy);
        free(elemy);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n\n", stkSize(stack));
/*
    for(uint i = 0; i < 15; i++)
    {
        elemx = rndStr(rndNum(1, 20));
        printf("Inserimento nello stack: %s\n", elemx);
        stkPush(stack, elemx);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    elemy = (int *) stkTop(stack);
    printf("Rimozione della testa dello stack dopo gli inserimenti: %d\n\n", *elemy);
    stkPop(stack);

    printf("Esistenza del valore 25 nello stack : %d\n\n", stkExists(stack, (int *) 25));

    StackObject * stackx = stkClone(stack);
    printf("Controllo di uguaglianza tra il clone dello stack e lo stack stesso: %d\n\n", stkEqual(stack, stackx));

    stkMap(stackx, &mapPosZerNeg, NULL);
    val = 1;
    stkFold(stack, &foldParity, &val, NULL);
    printf("Parità degli elementi contenuti nello stack: %d\n\n", val);

    while(!stkEmpty(stack))
    {
        elemy = (int *) stkTopNPop(stack);
        printf("Rimozione dallo stack: %d\n", *elemy);
        free(elemy);
        elemy = (int *) stkTopNPop(stackx);
        printf("Rimozione dal clone dello stack: %d\n", *elemy);
        free(elemy);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
    printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

    printf("Distruzione Oggetti StackVec\n\n");
    stkDestruct(stackx);
    stkDestruct(stack);

    printf("*****************************************************************\n\n");

    printf("Creazione Oggetto QueueVec\n\n");
    QueueObject * queue = queConstruct();

    for(uint i = 0; i < 17; i++)
    {
        *elemx = rndNum(-50, 50);
        printf("Inserimento nella queue: %d\n", *elemx);
        queEnqueue(queue, elemx);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    for(uint i = 0; i < 10; i++)
    {
        elemy = (int *) queHeadNDequeue(queue);
        printf("Rimozione dalla queue: %d\n", *elemy);
        free(elemy);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n\n", queSize(queue));

    *elemx = 25;
    queEnqueue(queue, elemx);

    for(uint i = 0; i < 15; i++)
    {
        *elemx = rndNum(0, 100);
        printf("Inserimento nella queue: %d\n", *elemx);
        queEnqueue(queue, elemx);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    elemy = (int *) queHead(queue);
    printf("Rimozione della testa della queue dopo gli inserimenti: %d\n\n", *elemy);
    queDequeue(queue);

    printf("Esistenza del valore 25 nella queue : %d\n\n", queExists(queue, (int *) 25));

    QueueObject * queuex = queClone(queue);
    printf("Controllo di uguaglianza tra il clone della queue e lo queus stessa: %d\n\n", queEqual(queue, queuex));

    queMap(queue, &mapPosZerNeg, NULL);
    val = 1;
    queFold(queue, &foldParity, &val, NULL);
    printf("Parità degli elementi contenuti nella queue: %d\n\n", val);

    while(!queEmpty(queue))
    {
        elemy = (int *) queHeadNDequeue(queue);
        printf("Rimozione dalla queue: %d\n", *elemy);
        free(elemy);
        elemy = (int *) queHeadNDequeue(queuex);
        printf("Rimozione dal clone della queue: %d\n", *elemy);
        free(elemy);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n", queSize(queue));
    printf("Numero di elementi nel clone della queue dopo le estrazioni: %d\n\n", queSize(queuex));

    printf("Distruzione Oggetti QueueVec\n\n");
    queDestruct(queuex);
    queDestruct(queue);

    printf("*****************************************************************\n\n");

    */
    free(elemx);
    stkDestruct(stack);

    return 0;
}

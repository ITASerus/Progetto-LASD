
#include "utility.h"

/* ************************************************************************** */

#include "stack/stack.h"

#include "queue/queue.h"

/* ************************************************************************** */

int main()
{
    srand(time(NULL));

    char* elemx = (char*) malloc(sizeof(char) * 20);
    char* elemy = NULL;
    char* val = NULL;
/*
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

    for(uint i = 0; i < 10; i++)
    {
        elemy = (char *) stkTopNPop(stack);
        printf("Rimozione dallo stack: %s\n", elemy);
        free(elemy);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n\n", stkSize(stack));

    for(uint i = 0; i < 15; ++i)
    {
        elemx = rndStr(rndNum(1, 20));
        printf("Inserimento nello stack: %s\n", elemx);
        stkPush(stack, elemx);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    elemy = (char *) stkTop(stack);
    printf("Rimozione della testa dello stack dopo gli inserimenti: %s\n\n", elemy);
    stkPop(stack);
    free(elemy);

    printf("Esistenza del valore ciao nello stack : %d\n\n", stkExists(stack, "stringaProva"));

    StackObject * stackx = stkClone(stack);
    printf("Controllo di uguaglianza tra il clone dello stack e lo stack stesso: %d\n\n", stkEqual(stack, stackx));

    stkMap(stackx, turnToChar, "b");

    val = (char*)malloc(sizeof(char)*1000);
    stkFold(stack, strConcat, val, NULL);
    printf("Valore finale accumulatore: %s\n\n", val);

    while(!stkEmpty(stack))
    {
        elemy = stkTopNPop(stack);
        printf("Rimozione dallo stack: %s\n", elemy);
        free(elemy);
        elemy = stkTopNPop(stackx);
        printf("Rimozione dal clone dello stack: %s\n", elemy);
        free(elemy);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
    printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

    printf("Distruzione Oggetti StackVec\n\n");
    stkDestruct(stackx);
    stkDestruct(stack);

    printf("*****************************************************************\n\n");
*/

    printf("Creazione Oggetto QueueVec\n\n");
    QueueObject * queue = queConstruct();

    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    queEnqueue(queue, "1");
    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    queEnqueue(queue, "2");
    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    queDequeue(queue);
    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    queEnqueue(queue, "3");
    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    queEnqueue(queue, "4");
    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    /*
    for(uint i = 0; i < 17; i++)
    {
        strcpy(elemx, rndStr(10));
        printf("Inserimento nella queue: %s\n", elemx);
        queEnqueue(queue, elemx);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    for(uint i = 0; i < 10; i++)
    {
        elemy = (char *) queHeadNDequeue(queue);
        printf("Rimozione dalla queue: %s\n", elemy);
        free(elemy);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n\n", queSize(queue));

    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    strcpy(elemx, "ciao");
    queEnqueue(queue, elemx);

    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    for(uint i = 0; i < 15; i++)
    {
        strcpy(elemx, rndStr(15));
        printf("Inserimento nella queue: %s\n", elemx);
        queEnqueue(queue, elemx);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);

    strcpy(elemy, queHead(queue));
    printf("Rimozione della testa della queue dopo gli inserimenti: %s\n\n", elemy);
    queDequeue(queue);

    queuePrint(queue);
    printf("Front: %d - Rear: %d - NumElem: %d\n", queue->front, queue->rear, queue->numElem);


    printf("Esistenza del valore ciao nella queue : %d\n\n", queExists(queue, "ciao"));


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

    free(elemx);
    */
    return 0;
}

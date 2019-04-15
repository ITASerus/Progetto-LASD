
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

    printf("Creazione Oggetto Stack\n\n");
    StackObject * stack = stkConstruct();

    strcpy(elemx, "stringaProva");
    stkPush(stack, elemx);
    free(elemx);

    for(uint i = 0; i < 17; i++)
    {
        elemx = rndStr(rndNum(1, 10));
        printf("Inserimento nello stack: %s\n", elemx);
        stkPush(stack, elemx);
        free(elemx);
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
        elemx = rndStr(rndNum(1, 15));
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
/*
    val = (char*)malloc(sizeof(char)*1000);
    stkFold(stack, strConcat, val, NULL);
    printf("Valore finale accumulatore: %s\n\n", val);
*/
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

    printf("Creazione Oggetto QueueVec\n\n");
    QueueObject * queue = queConstruct();

    for(uint i = 0; i < 17; i++)
    {
        elemx = rndStr(10);
        printf("%d) Inserimento nella queue: %s\n", i, elemx);
        queEnqueue(queue, elemx);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    for(uint i = 0; i < 10; i++)
    {
        elemy = queHeadNDequeue(queue);
        printf("Rimozione dalla queue: %s\n", elemy);
        free(elemy);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n\n", queSize(queue));

    strcpy(elemx, "ciao");
    printf("Inserimento nella queue: %s\n", elemx);
    queEnqueue(queue, elemx);

    for(uint i = 0; i < 15; i++)
    {
        elemx = rndStr(15);
        printf("Inserimento nella queue: %s\n", elemx);
        queEnqueue(queue, elemx);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    elemy = queHead(queue);
    printf("Rimozione della testa della queue dopo gli inserimenti: %s\n\n", elemy);
    queDequeue(queue);

    printf("Esistenza del valore ciao nella queue : ");
    bool result = queExists(queue, "ciao");
    if(result == true) {
        printf("TRUE\n\n");
    } else {
        printf("FALSE\n\n");
    }

    QueueObject * queuex = queClone(queue);

    printf("Controllo di uguaglianza tra il clone della queue e la queue stessa: ");
    result = queEqual(queue, queuex);
    if(result == true) {
        printf("TRUE\n\n");
    } else {
        printf("FALSE\n\n");
    }

    queMap(queuex, turnToChar, "a");
    printf("QueueX dopo la Map:\n");
    queuePrint(queuex);
/*
    val = (char*)malloc(sizeof(char)*500);
    queFold(queue, elemConcat, val, NULL);
    printf("Parità degli elementi contenuti nella queue: %s\n\n", val);
*/
    while(!queEmpty(queue))
    {
        elemy =  queHeadNDequeue(queue);
        printf("Rimozione dalla queue: %s\n", elemy);
        free(elemy);
        elemy =  queHeadNDequeue(queuex);
        printf("Rimozione dal clone della queue: %s\n", elemy);
        free(elemy);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d - front: %d - rear: %d\n", queSize(queue), queue->front, queue->rear);
    printf("Numero di elementi nel clone della queue dopo le estrazioni: %d - front: %d - rear: %d\n\n", queSize(queuex), queuex->front, queuex->rear);

    printf("Distruzione Oggetti QueueVec\n\n");
    queDestruct(queuex);
    printf("QueueX distrutta\n");
    queDestruct(queue);
    printf("Queue distrutta\n");

    printf("*****************************************************************\n\n");

    free(elemx);
    return 0;
}

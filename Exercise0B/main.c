
#include "utility.h"

/* ************************************************************************** */

#include "adt/adt.h"
#include "adt/int/adtint.h"
#include "adt/flt/adtflt.h"
#include "adt/str/adtstr.h"
#include "adt/rec/adtrec.h"

#include "stack/stack.h"

#include "queue/queue.h"

/* ************************************************************************** */

void intMapPosZerNeg(DataObject * dat, void * _)
{
  assert(dat != NULL);
  int* elm = adtGetValue(dat);
  int val = (elm > 0) ? 1 : ((elm == 0) ? 0 : -1);
  adtSetValue(dat, &val);
  free(elm);
}

void intFoldParity(DataObject * dat, void * val, void * _)
{
  assert(dat != NULL);
  assert(val != NULL);
  int* elm = adtGetValue(dat);
  int valx = *((int *) val);
  *((int *) val) = (elm >= 0) ? valx : -valx;
  free(elm);
}

void turnToChar(DataObject* dat, void* character) {
    assert(dat != NULL);
    strcpy(dat->value, character);
}

void strConcat(DataObject* elm, void* accumulator, void* _) {
    char* resultString = (char*)malloc(sizeof(char)*(strlen(accumulator)+strlen(elm->value)));
    strcpy(resultString, strcat(accumulator, elm->value));
}

void floatMapPosZerNeg(DataObject * dat, void * _)
{
    assert(dat != NULL);
    float* elm = adtGetValue(dat);
    float val = (elm > 0) ? 1 : ((elm == 0) ? 0 : -1);
    adtSetValue(dat, &val);
    free(elm);
}

void floatFoldParity(DataObject * dat, void * val, void * _)
{
    assert(dat != NULL);
    assert(val != NULL);
    float* elm = adtGetValue(dat);
    float valx = *((float *) val);
    *((float *) val) = (elm >= 0) ? valx : -valx;
    free(elm);
}

/* ************************************************************************** */

void testStackInt(DataObject * data)
{
  int val = 0;
  int elem = -25;
  DataObject * dataptr = NULL;

  printf("Creazione Oggetto Stack\n\n");
  StackObject * stack = stkConstruct();

  adtSetValue(data, &elem); //Usa lo & perchè serve passare l'indirizzo dell'intero, e visto che elem è dichiarato in maniera statica, serve riferirsi al suo indirizzo con il &
  printf("VALUE: ");
  adtWriteToMonitor(data);
  printf("\n\n");

  stkPush(stack, data);

  for(uint i = 0; i < 17; i++)
  {
    printf("\n");
    adtRandomValue(data);
    printf("Inserimento nello stack:");
    adtWriteToMonitor(data);
    printf("\n");
    stkPush(stack, data);
  }
  printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

  printf("STACK (%d):\n", stack->index);
  for(int i=0; i<stack->index; i++) {
      printf("- %d\n", *(int*)stack->elements[i]->value);
  }
  printf("\n");

  for(uint i = 0; i < 10; i++)
  {
    dataptr = stkTopNPop(stack);
    printf("Rimozione dallo stack: ");
    adtWriteToMonitor(dataptr);
    printf("\n");
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nello stack dopo le estrazioni: %d\n\n", stkSize(stack));

  printf("STACK (%d):\n", stack->index);
  for(int i=0; i<stack->index; i++) {
      printf("- %d\n", *(int*)stack->elements[i]->value);
  }
  printf("\n");

  for(uint i = 0; i < 15; i++)
  {
    adtRandomValue(data);
    printf("Inserimento nello stack: ");
    adtWriteToMonitor(data);
    printf("\n");
    stkPush(stack, data);
  }
  printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

  printf("STACK (%d):\n", stack->index);
  for(int i=0; i<stack->index; i++) {
      printf("- %d\n", *(int*)stack->elements[i]->value);
  }
  printf("\n");

  dataptr = stkTop(stack);
  printf("Rimozione della testa dello stack dopo gli inserimenti: ");
  adtWriteToMonitor(dataptr);
  printf("\n");
  adtDestruct(dataptr);
  stkPop(stack);

  printf("STACK (%d):\n", stack->index);
  for(int i=0; i<stack->index; i++) {
      printf("- %d\n", *(int*)stack->elements[i]->value);
  }
  printf("\n");

  adtSetValue(data, &elem);
  printf("Esistenza del valore %d nello stack: %d\n\n", elem, stkExists(stack, data));

  StackObject * stackx = stkClone(stack);
  printf("Controllo di uguaglianza tra il clone dello stack e lo stack stesso: %d\n\n", stkEqual(stack, stackx));

  printf("STACK (%d):\n", stack->index);
  for(int i=0; i<stack->index; i++) {
      printf("- %d\n", *(int*)stack->elements[i]->value);
  }
  printf("\n");

  printf("STACKX (%d):\n", stackx->index);
  for(int i=0; i<stackx->index; i++) {
      printf("- %d\n", *(int*)stackx->elements[i]->value);
  }
  printf("\n");

  stkMap(stack, &intMapPosZerNeg, NULL);
  printf("STACK (%d):\n", stack->index);
  for(int i=0; i<stack->index; i++) {
      printf("- %d\n", *(int*)stack->elements[i]->value);
  }
  printf("\n");
  val = 1;

  stkFold(stack, &intFoldParity, &val, NULL);
  printf("Parità degli elementi contenuti nello stack: %d\n\n", val);

  while(!stkEmpty(stack))
  {
    dataptr = stkTopNPop(stack);
    printf("Rimozione dallo stack: ");
    adtWriteToMonitor(dataptr);
    printf("\n");
    adtDestruct(dataptr);

    dataptr = stkTopNPop(stackx);
    printf("Rimozione dallo stack: ");
    adtWriteToMonitor(dataptr);
    printf("\n");
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
  printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

  printf("STACK (%d):\n", stack->index);
  for(int i=0; i<stack->index; i++) {
      printf("- %d\n", *(int*)stack->elements[i]->value);
  }
  printf("\n");

  printf("Distruzione Oggetti Stack\n\n");
  stkDestruct(stackx);
  stkDestruct(stack);
}

void testStackString(DataObject * data)
{
    char* val = NULL;
    char* elem = (char*)malloc(sizeof(char)*strlen("ciaone!")+1);
    strcpy(elem, "ciaone!");
    DataObject * dataptr = NULL;

    printf("Creazione Oggetto Stack\n\n");
    StackObject * stack = stkConstruct();

    adtSetValue(data, elem);
    printf("VALUE: ");
    adtWriteToMonitor(data);
    printf("\n");

    stkPush(stack, data);

    for(uint i = 0; i < 17; i++)
    {
        printf("\n");
        adtRandomValue(data);
        printf("Inserimento nello stack: ");
        adtWriteToMonitor(data);
        printf("\n");
        stkPush(stack, data);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- ");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    for(uint i = 0; i < 10; i++)
    {
        dataptr = stkTopNPop(stack);
        printf("Rimozione dallo stack: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- ");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");


    for(uint i = 0; i < 15; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nello stack: ");
        adtWriteToMonitor(data);
        printf("\n");
        stkPush(stack, data);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- ");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    dataptr = stkTop(stack);
    printf("Rimozione della testa dello stack dopo gli inserimenti: ");
    adtWriteToMonitor(dataptr);
    printf("\n\n");
    adtDestruct(dataptr);
    stkPop(stack);

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- ");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    adtSetValue(data, elem);
    printf("Esistenza del valore %s nello stack: %d\n\n", elem, stkExists(stack, data));

    StackObject * stackx = stkClone(stack);
    printf("Controllo di uguaglianza tra il clone dello stack e lo stack stesso: %d\n\n", stkEqual(stack, stackx));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- ");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    printf("STACKX (%d):\n", stackx->index);
    for(int i=0; i<stackx->index; i++) {
        printf("- ");
        adtWriteToMonitor(stackx->elements[i]);
        printf("\n");
    }
    printf("\n");

    stkMap(stack, turnToChar, "b");
    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- ");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    printf("STACKX (%d):\n", stackx->index);
    for(int i=0; i<stackx->index; i++) {
        printf("- ");
        adtWriteToMonitor(stackx->elements[i]);
        printf("\n");
    }
    printf("\n");

    val = (char*)malloc(sizeof(char)*1000);
    stkFold(stackx, strConcat, val, NULL);
    printf("Concatenazioni degli elementi contenuti nello stack: %s\n\n", val);

    while(!stkEmpty(stack))
    {
        dataptr = stkTopNPop(stack);
        printf("Rimozione dallo stack: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
        dataptr = stkTopNPop(stackx);
        printf("Rimozione dallo stack: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
    printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

    printf("Distruzione Oggetti Stack\n\n");
    stkDestruct(stackx);
    stkDestruct(stack);
}

void testStackFloat(DataObject * data)
{
    float val = 0.0;
    float elem = -25.5;
    DataObject * dataptr = NULL;

    printf("Creazione Oggetto Stack\n\n");
    StackObject * stack = stkConstruct();

    adtSetValue(data, &elem); //Usa lo & perchè serve passare l'indirizzo del float, e visto che elem è dichiarato in maniera statica, serve riferirsi al suo indirizzo con il &
    printf("VALUE: ");
    adtWriteToMonitor(data);
    printf("\n\n");

    stkPush(stack, data);

    for(uint i = 0; i < 17; i++)
    {
        printf("\n");
        adtRandomValue(data);
        printf("Inserimento nello stack: ");
        adtWriteToMonitor(data);
        printf("\n");
        stkPush(stack, data);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- %f\n", *(float*)stack->elements[i]->value);
    }
    printf("\n");

    for(uint i = 0; i < 10; i++)
    {
        dataptr = stkTopNPop(stack);
        printf("Rimozione dallo stack: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- %f\n", *(float*)stack->elements[i]->value);
    }
    printf("\n");

    for(uint i = 0; i < 15; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nello stack: \n");
        adtWriteToMonitor(data);
        printf("\n");
        stkPush(stack, data);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- %f\n", *(float*)stack->elements[i]->value);
    }
    printf("\n");

    dataptr = stkTop(stack);
    printf("Rimozione della testa dello stack dopo gli inserimenti: ");
    adtWriteToMonitor(dataptr);
    printf("\n\n");
    adtDestruct(dataptr);
    stkPop(stack);

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- %f\n", *(float*)stack->elements[i]->value);
    }
    printf("\n");

    adtSetValue(data, &elem);
    printf("Esistenza del valore %f nello stack: %d\n\n", elem, stkExists(stack, data));

    StackObject * stackx = stkClone(stack);
    printf("Controllo di uguaglianza tra il clone dello stack e lo stack stesso: %d\n\n", stkEqual(stack, stackx));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- %f\n", *(float*)stack->elements[i]->value);
    }
    printf("\n");

    printf("STACKX (%d):\n", stackx->index);
    for(int i=0; i<stackx->index; i++) {
        printf("- %f\n", *(float*)stackx->elements[i]->value);
    }
    printf("\n");

    stkMap(stack, &floatMapPosZerNeg, NULL);
    printf("STACK (%d):\n", stackx->index);
    for(int i=0; i<stack->index; i++) {
        printf("- %f\n", *(float*)stack->elements[i]->value);
    }
    printf("\n");

    val = 1;
    stkFold(stack, &floatFoldParity, &val, NULL);
    printf("Parità degli elementi contenuti nello stack: %f\n\n", val);

    while(!stkEmpty(stack))
    {
        dataptr = stkTopNPop(stack);
        printf("Rimozione dallo stack: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
        dataptr = stkTopNPop(stackx);
        printf("Rimozione dallo stack: ");
        adtWriteToMonitor(data);
        printf("\n");
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
    printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

    printf("Distruzione Oggetti Stack\n\n");
    stkDestruct(stackx);
    stkDestruct(stack);
}

void testStackRecord(DataObject * data)
{
    Record* val = NULL;
    Record* elem = (Record*)malloc(sizeof(Record));
    elem->name = (char*)malloc(sizeof(char)*20);
    strcpy(elem->name, "Ernesto");
    elem->surname = (char*)malloc(sizeof(char)*20);
    strcpy(elem->surname, "De Crecchio");
    DataObject * dataptr = NULL;

    printf("Creazione Oggetto Stack\n\n");
    StackObject * stack = stkConstruct();

    adtSetValue(data, elem);
    printf("VALUE: \n");
    adtWriteToMonitor(data);
    printf("\n");

    stkPush(stack, data);

    for(uint i = 0; i < 17; i++)
    {
        printf("\n");
        adtRandomValue(data);
        printf("Inserimento nello stack:\n");
        adtWriteToMonitor(data);
        stkPush(stack, data);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("---------\n");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    for(uint i = 0; i < 10; i++)
    {
        dataptr = stkTopNPop(stack);
        printf("Rimozione dallo stack:\n");
        adtWriteToMonitor(dataptr);
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nello stack dopo le estrazioni: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("---------\n");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    for(uint i = 0; i < 15; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nello stack:\n");
        adtWriteToMonitor(data);
        stkPush(stack, data);
    }
    printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("---------\n");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    dataptr = stkTop(stack);
    printf("Rimozione della testa dello stack dopo gli inserimenti:\n");
    adtWriteToMonitor(dataptr);
    adtDestruct(dataptr);
    stkPop(stack);

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("---------\n");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    adtSetValue(data, elem);
    strcpy(((Record*)data->value)->surname, "haha");
    printf("Esistenza del valore:\n");
    adtWriteToMonitor(data);
    printf("\nnello stack: %d\n\n", stkExists(stack, data));

    StackObject * stackx = stkClone(stack);
    printf("Controllo di uguaglianza tra il clone dello stack e lo stack stesso: %d\n\n", stkEqual(stack, stackx));

    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("---------\n");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    printf("STACKX (%d):\n", stackx->index);
    for(int i=0; i<stackx->index; i++) {
        printf("---------\n");
        adtWriteToMonitor(stackx->elements[i]);
        printf("\n");
    }
    printf("\n");
/*
    stkMap(stack, turnToChar, "b"); //TODO: DA IMPLEMENTARE
    printf("STACK (%d):\n", stack->index);
    for(int i=0; i<stack->index; i++) {
        printf("- ");
        adtWriteToMonitor(stack->elements[i]);
        printf("\n");
    }
    printf("\n");

    printf("STACKX (%d):\n", stackx->index);
    for(int i=0; i<stackx->index; i++) {
        printf("---------\n");
        adtWriteToMonitor(stackx->elements[i]);
        printf("\n");
    }
    printf("\n");

    val = (char*)malloc(sizeof(char)*1000);
    stkFold(stackx, strConcat, val, NULL);
    printf("Concatenazioni degli elementi contenuti nello stack: %s\n\n", val);
*/
    while(!stkEmpty(stack))
    {
        dataptr = stkTopNPop(stack);
        printf("\n\nRimozione dallo stack:\n");
        adtWriteToMonitor(dataptr);
        adtDestruct(dataptr);
        dataptr = stkTopNPop(stackx);
        printf("\nRimozione dallo stack:\n");
        adtWriteToMonitor(dataptr);
        adtDestruct(dataptr);
    }
    printf("\nNumero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
    printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

    printf("Distruzione Oggetti Stack\n\n");
    stkDestruct(stackx);
    stkDestruct(stack);
}


void testQueueInt(DataObject * data)
{
  int val = 0;
  int elem = 75;
  DataObject * dataptr = NULL;

  printf("Creazione Oggetto Queue\n\n");
  QueueObject * queue = queConstruct();

  for(uint i = 0; i < 17; i++)
  {
    adtRandomValue(data);
    printf("Inserimento nella queue: ");
    adtWriteToMonitor(data);
    printf("\n");
    queEnqueue(queue, data);
  }
  printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

  queuePrint(queue);

  for(uint i = 0; i < 10; i++)
  {
    dataptr = queHeadNDequeue(queue);
    printf("Rimozione dalla queue: ");
    adtWriteToMonitor(dataptr);
    printf("\n");
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nella queue dopo le estrazioni: %d\n\n", queSize(queue));

  queuePrint(queue);

  adtSetValue(data, &elem);
  queEnqueue(queue, data);

  for(uint i = 0; i < 15; i++)
  {
    adtRandomValue(data);
    printf("Inserimento nella queue: ");
    adtWriteToMonitor(data);
    printf("\n");
    queEnqueue(queue, data);
  }
  printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

  queuePrint(queue);

  dataptr = queHead(queue);
  printf("Rimozione della testa dello stack dopo gli inserimenti: ");
  adtWriteToMonitor(dataptr);
  printf("\n\n");
  adtDestruct(dataptr);
  queuePrint(queue);
  queDequeue(queue);

  adtSetValue(data, &elem);
  printf("Esistenza del valore %d nella queue: %d\n\n", elem, queExists(queue, data));

  QueueObject * queuex = queClone(queue);
  queuePrint(queue);
  queuePrint(queuex);
  printf("Controllo di uguaglianza tra il clone della queue e la queue stessa: %d\n\n", queEqual(queue, queuex));
/*
  queMap(queue, &mapPosZerNeg, NULL);
  val = 1;
  queFold(queue, &foldParity, &val, NULL);
  printf("Parità degli elementi contenuti nella queue: %d\n\n", val);
*/
  while(!queEmpty(queue))
  {
    dataptr = queHeadNDequeue(queue);
    printf("Rimozione dalla queue: ");
    adtWriteToMonitor(dataptr);
    printf("\n");
    adtDestruct(dataptr);
    dataptr = queHeadNDequeue(queuex);
    printf("Rimozione dal clone della queue: ");
    adtWriteToMonitor(dataptr);
    printf("\n");
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nella queue dopo le estrazioni: %d\n", queSize(queue));
  printf("Numero di elementi nel clone della queue dopo le estrazioni: %d\n\n", queSize(queuex));

  printf("Distruzione Oggetti Queue\n\n");
  queDestruct(queuex);
  queDestruct(queue);
}

void testQueueString(DataObject * data)
{
    char* val = NULL;
    char* elem = (char*)malloc(sizeof(char)*8);
    strcpy(elem, "ciaone!");
    DataObject * dataptr = NULL;

    printf("Creazione Oggetto Queue\n\n");
    QueueObject * queue = queConstruct();

    for(uint i = 0; i < 17; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nella queue: ");
        adtWriteToMonitor(data);
        printf("\n");
        queEnqueue(queue, data);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    queuePrint(queue);

    for(uint i = 0; i < 10; i++)
    {
        dataptr = queHeadNDequeue(queue);
        printf("Rimozione dalla queue: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n\n", queSize(queue));

    queuePrint(queue);

    adtSetValue(data, elem);
    queEnqueue(queue, data);
    queuePrint(queue);

    for(uint i = 0; i < 15; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nella queue: ");
        adtWriteToMonitor(data);
        printf("\n");
        queEnqueue(queue, data);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    queuePrint(queue);

    dataptr = queHead(queue);
    printf("Rimozione della testa dello stack dopo gli inserimenti: ");
    adtWriteToMonitor(dataptr);
    printf("\n");
    adtDestruct(dataptr);
    queDequeue(queue);
    queuePrint(queue);

    adtSetValue(data, elem);
    printf("Esistenza del valore %s nella queue: %d\n\n", elem, queExists(queue, data));

    QueueObject * queuex = queClone(queue);
    queuePrint(queue);
    queuePrint(queuex);
    printf("Controllo di uguaglianza tra il clone della queue e la queue stessa: %d\n\n", queEqual(queue, queuex));
/*
  queMap(queue, &mapPosZerNeg, NULL);
  val = 1;
  queFold(queue, &foldParity, &val, NULL);
  printf("Parità degli elementi contenuti nella queue: %d\n\n", val);
*/
    while(!queEmpty(queue))
    {
        dataptr = queHeadNDequeue(queue);
        printf("Rimozione dalla queue: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
        dataptr = queHeadNDequeue(queuex);
        printf("Rimozione dal clone della queue: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n", queSize(queue));
    printf("Numero di elementi nel clone della queue dopo le estrazioni: %d\n\n", queSize(queuex));

    printf("Distruzione Oggetti Queue\n\n");
    queDestruct(queuex);
    queDestruct(queue);
}

void testQueueFloat(DataObject * data)
{
    float val = 0.0;
    float elem = 75.5;
    DataObject * dataptr = NULL;

    printf("Creazione Oggetto Queue\n\n");
    QueueObject * queue = queConstruct();

    for(uint i = 0; i < 17; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nella queue: ");
        adtWriteToMonitor(data);
        printf("\n");
        queEnqueue(queue, data);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    queuePrint(queue);

    for(uint i = 0; i < 10; i++)
    {
        dataptr = queHeadNDequeue(queue);
        printf("Rimozione dalla queue: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n\n", queSize(queue));

    queuePrint(queue);

    adtSetValue(data, &elem);
    queEnqueue(queue, data);

    for(uint i = 0; i < 15; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nella queue: ");
        adtWriteToMonitor(data);
        printf("\n");
        queEnqueue(queue, data);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    queuePrint(queue);

    dataptr = queHead(queue);
    printf("Rimozione della testa dello stack dopo gli inserimenti: ");
    adtWriteToMonitor(dataptr);
    printf("\n\n");
    adtDestruct(dataptr);
    queuePrint(queue);
    queDequeue(queue);

    adtSetValue(data, &elem);
    printf("Esistenza del valore %f nella queue: %d\n\n", elem, queExists(queue, data));

    QueueObject * queuex = queClone(queue);
    queuePrint(queue);
    queuePrint(queuex);
    printf("Controllo di uguaglianza tra il clone della queue e la queue stessa: %d\n\n", queEqual(queue, queuex));
/*
  queMap(queue, &mapPosZerNeg, NULL);
  val = 1;
  queFold(queue, &foldParity, &val, NULL);
  printf("Parità degli elementi contenuti nella queue: %d\n\n", val);
*/
    while(!queEmpty(queue))
    {
        dataptr = queHeadNDequeue(queue);
        printf("Rimozione dalla queue: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
        dataptr = queHeadNDequeue(queuex);
        printf("Rimozione dal clone della queue: ");
        adtWriteToMonitor(dataptr);
        printf("\n");
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n", queSize(queue));
    printf("Numero di elementi nel clone della queue dopo le estrazioni: %d\n\n", queSize(queuex));

    printf("Distruzione Oggetti Queue\n\n");
    queDestruct(queuex);
    queDestruct(queue);
}

void testQueueRecord(DataObject * data)
{
    Record* val = NULL;
    Record* elem = (Record*)malloc(sizeof(Record));
    elem->name = (char*)malloc(sizeof(char)*20);
    strcpy(elem->name, "Ernesto");
    elem->surname = (char*)malloc(sizeof(char)*20);
    strcpy(elem->surname, "De Crecchio");
    DataObject * dataptr = NULL;

    printf("Creazione Oggetto Queue\n\n");
    QueueObject * queue = queConstruct();

    for(uint i = 0; i < 17; i++)
    {
        printf("\n");
        adtRandomValue(data);
        printf("Inserimento nella queue:\n");
        adtWriteToMonitor(data);
        queEnqueue(queue, data);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    queuePrint(queue);

    for(uint i = 0; i < 10; i++)
    {
        dataptr = queHeadNDequeue(queue);
        printf("Rimozione dalla queue:\n");
        adtWriteToMonitor(dataptr);
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n\n", queSize(queue));

    queuePrint(queue);

    adtSetValue(data, elem);
    queEnqueue(queue, data);

    for(uint i = 0; i < 15; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nella queue:\n");
        adtWriteToMonitor(data);
        queEnqueue(queue, data);
    }
    printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    queuePrint(queue);

    dataptr = queHead(queue);
    printf("Rimozione della testa dello stack dopo gli inserimenti:\n");
    adtWriteToMonitor(dataptr);
    adtDestruct(dataptr);
    queDequeue(queue);
    queuePrint(queue);

    adtSetValue(data, elem);
    printf("Esistenza del valore\n");
    adtWriteToMonitor(data);
    printf("nella queue: %d\n\n", queExists(queue, data));

    QueueObject * queuex = queClone(queue);
    queuePrint(queue);
    queuePrint(queuex);
    printf("Controllo di uguaglianza tra il clone della queue e la queue stessa: %d\n\n", queEqual(queue, queuex));
/*
  queMap(queue, &mapPosZerNeg, NULL);
  val = 1;
  queFold(queue, &foldParity, &val, NULL);
  printf("Parità degli elementi contenuti nella queue: %d\n\n", val);
*/
    while(!queEmpty(queue))
    {
        dataptr = queHeadNDequeue(queue);
        printf("\n\nRimozione dalla queue:\n");
        adtWriteToMonitor(dataptr);
        adtDestruct(dataptr);
        dataptr = queHeadNDequeue(queuex);
        printf("\nRimozione dal clone della queue:\n");
        adtWriteToMonitor(dataptr);
        adtDestruct(dataptr);
    }
    printf("Numero di elementi nella queue dopo le estrazioni: %d\n", queSize(queue));
    printf("Numero di elementi nel clone della queue dopo le estrazioni: %d\n\n", queSize(queuex));

    printf("Distruzione Oggetti Queue\n\n");
    queDestruct(queuex);
    queDestruct(queue);
}

/* ************************************************************************** */

int main()
{
  srand(time(NULL));

  /* ************************************************************************ */

  printf("Creazione ADT per Intero\n\n");
  DataType * intdatatype = ConstructIntDataType();

  printf("Creazione Oggetto Dato \n\n");
  DataObject * data = adtConstruct(intdatatype);

  //testStackInt(data);

  //testQueueInt(data);

  printf("Distruzione Oggetto Dato\n\n");
  adtDestruct(data);

  printf("Distruzione ADT per Intero\n");
  DestructIntDataType(intdatatype);

  printf("*****************************************************************\n\n");

  printf("Creazione ADT per String\n\n");
  DataType * stringdatatype = ConstructStringDataType();

  printf("Creazione Oggetto Dato \n\n");
  data = adtConstruct(stringdatatype);

  testStackString(data);

  //testQueueString(data);

  printf("Distruzione Oggetto Dato\n\n");
  adtDestruct(data);

  printf("Distruzione ADT per Stringhe\n");
  DestructStringDataType(stringdatatype);

  printf("*****************************************************************\n\n");

  printf("Creazione ADT per Float\n\n");
  DataType * floatdatatype = ConstructFloatDataType();

  printf("Creazione Oggetto Dato \n\n");
  data = adtConstruct(floatdatatype);

 // testStackFloat(data);

 // testQueueFloat(data);

  printf("Distruzione Oggetto Dato\n\n");
  adtDestruct(data);

  printf("Distruzione ADT per Float\n");
  DestructFloatDataType(floatdatatype);

  printf("*****************************************************************\n\n");

  printf("Creazione ADT per Record\n\n");
  DataType * recorddatatype = ConstructRecordDataType();

  printf("Creazione Oggetto Dato \n\n");
  data = adtConstruct(recorddatatype);

  //testStackRecord(data);

  //testQueueRecord(data);

  printf("Distruzione Oggetto Dato\n\n");
  adtDestruct(data);

  printf("Distruzione ADT per Record\n");
  DestructRecordDataType(recorddatatype);

  printf("*****************************************************************\n\n");

  /* ************************************************************************ */
  return 0;
}

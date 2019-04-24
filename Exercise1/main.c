
#include "utility.h"

/* ************************************************************************** */

#include "adt/adt.h"
#include "adt/int/adtint.h"
#include "adt/flt/adtflt.h"
#include "adt/str/adtstr.h"
#include "adt/rec/adtrec.h"

#include "stack/stack.h"
#include "stack/vec/stackvec.h"
#include "stack/lst/stacklst.h"

#include "queue/queue.h"
#include "queue/vec/queuevec.h"
#include "queue/lst/queuelst.h"

/* ************************************************************************** */

void mapPosZerNeg(DataObject * dat, void * _)
{
  assert(dat != NULL);
  int elm = *((int *) (adtGetValue(dat)));
  int val = (elm > 0) ? 1 : ((elm == 0) ? 0 : -1);
  adtSetValue(dat, &val);
}

void foldParity(DataObject * dat, void * val, void * _)
{
  assert(dat != NULL);
  assert(val != NULL);
  int elm = *((int *) (adtGetValue(dat)));
  int valx = *((int *) val);
  *((int *) val) = (elm >= 0) ? valx : -valx;
}

void testStack(StackType * stktyp, DataObject * data)
{
  int val = 0;
  int elem = -25;
  DataObject * dataptr = NULL;

  printf("Creazione Oggetto Stack\n\n");
  StackObject * stack = stkConstruct(stktyp);

  adtSetValue(data, &elem);
  stkPush(stack, data);

  for(uint i = 0; i < 17; i++)
  {
    adtRandomValue(data);
    printf("Inserimento nello stack: %d\n", *((int *) adtGetValue(data)));
    stkPush(stack, data);
  }
  printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));
/*
  for(uint i = 0; i < 10; i++)
  {
    dataptr = stkTopNPop(stack);
    printf("Rimozione dallo stack: %d\n", *((int *) adtGetValue(dataptr)));
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nello stack dopo le estrazioni: %d\n\n", stkSize(stack));

  for(uint i = 0; i < 15; i++)
  {
    adtRandomValue(data);
    printf("Inserimento nello stack: %d\n", *((int *) adtGetValue(data)));
    stkPush(stack, data);
  }
  printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

  dataptr = stkTop(stack);
  printf("Rimozione della testa dello stack dopo gli inserimenti: %d\n\n", *((int *) adtGetValue(dataptr)));
  adtDestruct(dataptr);
  stkPop(stack);

  adtSetValue(data, &elem);
  printf("Esistenza del valore %d nello stack: %d\n\n", elem, stkExists(stack, data));

  StackObject * stackx = stkClone(stack);
  printf("Controllo di uguaglianza tra il clone dello stack e lo stack stesso: %d\n\n", stkEqual(stack, stackx));

  stkMap(stack, &mapPosZerNeg, NULL);
  val = 1;
  stkFold(stack, &foldParity, &val, NULL);
  printf("Parità degli elementi contenuti nello stack: %d\n\n", val);

  while(!stkEmpty(stack))
  {
    dataptr = stkTopNPop(stack);
    printf("Rimozione dallo stack: %d\n", *((int *) adtGetValue(dataptr)));
    adtDestruct(dataptr);
    dataptr = stkTopNPop(stackx);
    printf("Rimozione dallo stack: %d\n", *((int *) adtGetValue(dataptr)));
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
  printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

  printf("Distruzione Oggetti Stack\n\n");
  stkDestruct(stackx);
  stkDestruct(stack);
  */
}

/*void testQueue(QueueType * quetyp, DataObject * data)
{
  int val = 0;
  int elem = 75;
  DataObject * dataptr = NULL;

  printf("Creazione Oggetto Queue\n\n");
  QueueObject * queue = queConstruct(quetyp);

  for(uint i = 0; i < 17; i++)
  {
    adtRandomValue(data);
    printf("Inserimento nella queue: %d\n", *((int *) adtGetValue(data)));
    queEnqueue(queue, data);
  }
  printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

  for(uint i = 0; i < 10; i++)
  {
    dataptr = queHeadNDequeue(queue);
    printf("Rimozione dalla queue: %d\n", *((int *) adtGetValue(dataptr)));
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nella queue dopo le estrazioni: %d\n\n", queSize(queue));

  adtSetValue(data, &elem);
  queEnqueue(queue, data);

  for(uint i = 0; i < 15; i++)
  {
    adtRandomValue(data);
    printf("Inserimento nella queue: %d\n", *((int *) adtGetValue(data)));
    queEnqueue(queue, data);
  }
  printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

  dataptr = queHead(queue);
  printf("Rimozione della testa dello stack dopo gli inserimenti: %d\n\n", *((int *) adtGetValue(dataptr)));
  adtDestruct(dataptr);
  queDequeue(queue);

  adtSetValue(data, &elem);
  printf("Esistenza del valore %d nella queue: %d\n\n", elem, queExists(queue, data));

  QueueObject * queuex = queClone(queue);
  printf("Controllo di uguaglianza tra il clone della queue e la queue stessa: %d\n\n", queEqual(queue, queuex));

  queMap(queue, &mapPosZerNeg, NULL);
  val = 1;
  queFold(queue, &foldParity, &val, NULL);
  printf("Parità degli elementi contenuti nella queue: %d\n\n", val);

  while(!queEmpty(queue))
  {
    dataptr = queHeadNDequeue(queue);
    printf("Rimozione dalla queue: %d\n", *((int *) adtGetValue(dataptr)));
    adtDestruct(dataptr);
    // dataptr = queHeadNDequeue(queuex);
    // printf("Rimozione dal clone della queue: %d\n", *((int *) adtGetValue(dataptr)));
    // adtDestruct(dataptr);
  }
  printf("Numero di elementi nella queue dopo le estrazioni: %d\n", queSize(queue));
  // printf("Numero di elementi nel clone della queue dopo le estrazioni: %d\n\n", queSize(queuex));

  printf("Distruzione Oggetti Queue\n\n");
  // queDestruct(queuex);
  queDestruct(queue);
}
*/
/* ************************************************************************** */

int main()
{
  srand(time(NULL));

  /* ************************************************************************ */

  printf("Creazione ADT per Intero\n\n");
  DataType * intdatatype = ConstructIntDataType();

  printf("Creazione Oggetto Dato\n\n");
  DataObject * data = adtConstruct(intdatatype);

  printf("*****************************************************************\n\n");

  printf("Creazione Tipo StackVec\n\n");
  StackType * stktyp = ConstructStackVecType();

  testStack(stktyp, data);

  printf("Distruzione Tipo StackVec\n\n");
  DestructStackVecType(stktyp);

  /*printf("*****************************************************************\n\n");

  printf("Creazione Tipo StackLst\n\n");
  stktyp = ConstructStackLstType();

  testStack(stktyp, data);

  printf("Distruzione Tipo StackLst\n\n");
  DestructStackLstType(stktyp);

  printf("*****************************************************************\n\n");

  printf("Creazione Tipo QueueVec\n\n");
  QueueType * quetyp = ConstructQueueVecType();

  testQueue(quetyp, data);

  printf("Distruzione Tipo QueueVec\n\n");
  DestructQueueVecType(quetyp);

  printf("*****************************************************************\n\n");

  printf("Creazione Tipo QueueLst\n\n");
  quetyp = ConstructQueueLstType();

  testQueue(quetyp, data);

  printf("Distruzione Tipo QueueLst\n\n");
  DestructQueueLstType(quetyp);

  printf("*****************************************************************\n\n");

  printf("Distruzione Oggetto Dato\n\n");
  adtDestruct(data);

  printf("Distruzione ADT per Intero\n");
  DestructIntDataType(intdatatype);
*/
  /* ************************************************************************ */

  return 0;
}

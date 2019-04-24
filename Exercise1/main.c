
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
    printf("Rimozione dallo stackx: %d\n", *((int *) adtGetValue(dataptr)));
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
  printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

  printf("Distruzione Oggetti Stack\n\n");
  stkDestruct(stackx);
  stkDestruct(stack);
}

void testQueue(QueueType * quetyp, DataObject * data)
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
    dataptr = queHeadNDequeue(queuex);
    printf("Rimozione dal clone della queue: %d\n", *((int *) adtGetValue(dataptr)));
    adtDestruct(dataptr);
  }
  printf("Numero di elementi nella queue dopo le estrazioni: %d\n", queSize(queue));
  printf("Numero di elementi nel clone della queue dopo le estrazioni: %d\n\n", queSize(queuex));

  printf("Distruzione Oggetti Queue\n\n");
  queDestruct(queuex);
  queDestruct(queue);
}

/* ************************************************************************** */

void testStackVecInt() { printf("COMING SOON\n"); }
void testStackVecFloat() { printf("COMING SOON\n"); }
void testStackVecString() { printf("COMING SOON\n"); }
void testStackVecRecord() { printf("COMING SOON\n"); }

void testStackListInt() {
    printf("Creazione ADT per Intero\n\n");
    DataType * intdatatype = ConstructIntDataType();

    printf("Creazione Oggetto Dato\n\n");
    DataObject * data = adtConstruct(intdatatype);

    printf("Creazione Tipo StackLst\n\n");
    StackType * stktyp = ConstructStackLstType();

    printf("Creazione Oggetto Stack\n\n");
    StackObject * stack = stkConstruct(stktyp);

    printf("*****************************************************************\n\n");

    int elem = -25;
    DataObject* dataptr = NULL;

    printf("Stack vuoto ad inizio test: %d\n\n", stkEmpty(stack));

    adtSetValue(data, &elem);
    stkPush(stack, data);

    printf("\nSTACK:\n");
    StackLst* stampaStack = stack->stack;
    while(stampaStack->next != NULL) {
        adtWriteToMonitor(stampaStack->next->element);
        printf("\n");
        stampaStack = stampaStack->next;
    }
    printf("\n");

    for(uint i = 0; i < 17; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nello stack: %d\n", *((int *) adtGetValue(data)));
        stkPush(stack, data);
    }
    //printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("\nSTACK:\n");
    stampaStack = stack->stack;
    while(stampaStack->next != NULL) {
        adtWriteToMonitor(stampaStack->next->element);
        printf("\n");
        stampaStack = stampaStack->next;
    }
    printf("\n");

    for(uint i = 0; i < 10; i++)
    {
        dataptr = stkTopNPop(stack);
        printf("Rimozione dallo stack: %d\n", *((int *) adtGetValue(dataptr)));
        adtDestruct(dataptr);
    }
    //printf("Numero di elementi nello stack dopo le estrazioni: %d\n\n", stkSize(stack));

    printf("\nSTACK:\n");
    stampaStack = stack->stack;
    while(stampaStack->next != NULL) {
        adtWriteToMonitor(stampaStack->next->element);
        printf("\n");
        stampaStack = stampaStack->next;
    }
    printf("\n");

    for(uint i = 0; i < 15; i++) {
        adtRandomValue(data);
        printf("Inserimento nello stack: %d\n", *((int *) adtGetValue(data)));
        stkPush(stack, data);
    }
    //printf("Numero di elementi nello stack dopo gli inserimenti: %d\n\n", stkSize(stack));

    printf("\nSTACK:\n");
    stampaStack = stack->stack;
    while(stampaStack->next != NULL) {
        adtWriteToMonitor(stampaStack->next->element);
        printf("\n");
        stampaStack = stampaStack->next;
    }
    printf("\n");

    dataptr = stkTop(stack);
    printf("Rimozione della testa dello stack dopo gli inserimenti: %d\n\n", *((int *) adtGetValue(dataptr)));
    adtDestruct(dataptr);
    stkPop(stack);

    printf("\nSTACK:\n");
    stampaStack = stack->stack;
    while(stampaStack->next != NULL) {
        adtWriteToMonitor(stampaStack->next->element);
        printf("\n");
        stampaStack = stampaStack->next;
    }
    printf("\n");

    //adtSetValue(data, &elem);
    // printf("Esistenza del valore %d nello stack: %d\n\n", elem, stkExists(stack, data));

    StackObject * stackx = stkClone(stack);
    printf("\nSTACK CLONE:\n");
    stampaStack = stackx->stack;
    while(stampaStack->next != NULL) {
        adtWriteToMonitor(stampaStack->next->element);
        printf("\n");
        stampaStack = stampaStack->next;
    }
    printf("\n");
    printf("Controllo di uguaglianza tra il clone dello stack e lo stack stesso: %d\n\n", stkEqual(stack, stackx));

    /*stkMap(stack, &mapPosZerNeg, NULL);
    val = 1;
    stkFold(stack, &foldParity, &val, NULL);
    printf("Parità degli elementi contenuti nello stack: %d\n\n", val);
*/
    while(!stkEmpty(stack))
    {
        dataptr = stkTopNPop(stack);
        printf("Rimozione dallo stack: %d\n", *((int *) adtGetValue(dataptr)));
        adtDestruct(dataptr);
        dataptr = stkTopNPop(stackx);
        printf("Rimozione dallo stack: %d\n", *((int *) adtGetValue(dataptr)));
        adtDestruct(dataptr);
    }
    //printf("Numero di elementi nello stack dopo le estrazioni: %d\n", stkSize(stack));
    //printf("Numero di elementi nel clone dello stack dopo le estrazioni: %d\n\n", stkSize(stackx));

    printf("Distruzione Oggetti Stack\n\n");
    stkDestruct(stackx);
    stkDestruct(stack);

    printf("*****************************************************************\n\n");

    printf("Distruzione Tipo StackLst\n\n");
    DestructStackLstType(stktyp);

}
void testStackListFloat() { printf("COMING SOON\n"); }
void testStackListString() { printf("COMING SOON\n"); }
void testStackListRecord() { printf("COMING SOON\n"); }

void testQueueVecInt() { printf("COMING SOON\n"); }
void testQueueVecFloat() { printf("COMING SOON\n"); }
void testQueueVecString() { printf("COMING SOON\n"); }
void testQueueVecRecord() { printf("COMING SOON\n"); }

void testQueueListInt() {
    printf("Creazione ADT per Intero\n\n");
    DataType * intdatatype = ConstructIntDataType();

    printf("Creazione Oggetto Dato\n\n");
    DataObject * data = adtConstruct(intdatatype);

    printf("Creazione Tipo QueueLst\n\n");
    QueueType * quetyp = ConstructQueueLstType();

    printf("Creazione Oggetto Queue\n\n");
    QueueObject * queue = queConstruct(quetyp);

    printf("*****************************************************************\n\n");

    int val = 0;
    int elem = 75;
    DataObject * dataptr = NULL;

    for(uint i = 0; i < 17; i++)
    {
        adtRandomValue(data);
        printf("Inserimento nella queue: %d\n", *((int *) adtGetValue(data)));
        queEnqueue(queue, data);
    }
    //printf("Numero di elementi nella queue dopo gli inserimenti: %d\n\n", queSize(queue));

    /*
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
*/
    printf("*****************************************************************\n\n");

    printf("Distruzione Tipo QueueLst\n\n");
    DestructQueueLstType(quetyp);
}
void testQueueListFloat() { printf("COMING SOON\n"); }
void testQueueListString() { printf("COMING SOON\n"); }
void testQueueListRecord() { printf("COMING SOON\n"); }

/* ************************************************************************** */

void testMain() {
    int scelta;
    printf("Inserire tipologia di struttura da creare:\n(1) Stack\n(2) Queue\nScelta: ");
    scanf("%d", &scelta);
    switch (scelta) {
        case 1: {
            printf("Inserire tipologia di implementazione da utilizzare:\n(1) Vettore\n(2) Lista\nScelta: ");
            scanf("%d", &scelta);
            switch (scelta) {
                case 1: {
                    printf("Inserire tipologia dei dati da utilizzare per il vettore dello stack:\n(1) Intero\n(2) Float\n(3) Stringa\n(4) Record\nScelta: ");
                    scanf("%d", &scelta);
                    switch (scelta) {
                        case 1: {
                            testStackVecInt();
                            break;
                        }
                        case 2: {
                            testStackVecFloat();
                            break;
                        }
                        case 3: {
                            testStackVecString();
                            break;
                        }
                        case 4: {
                            testStackVecRecord();
                            break;
                        }
                        default: {
                            printf("Scelta non valida!\n");
                        }
                    }
                    break;
                }
                case 2: {
                    printf("Inserire tipologia dei dati da utilizzare per la lista dello stack:\n(1) Intero\n(2) Float\n(3) Stringa\n(4) Record\nScelta: ");
                    scanf("%d", &scelta);
                    switch (scelta) {
                        case 1: {
                            testStackListInt();
                            break;
                        }
                        case 2: {
                            testStackListFloat();
                            break;
                        }
                        case 3: {
                            testStackListString();
                            break;
                        }
                        case 4: {
                            testStackListRecord();
                            break;
                        }
                        default: {
                            printf("Scelta non valida!\n");
                        }
                    }
                    break;
                }
                default: {
                    printf("Scelta non valida!\n");
                }
            }
            break;
        }
        case 2: {
            printf("Inserire tipologia di implementazione da utilizzare per la Queue:\n(1) Vettore\n(2) Lista\nScelta: ");
            scanf("%d", &scelta);
            switch (scelta) {
                case 1: {
                    printf("Inserire tipologia dei dati da utilizzare per il vettore della queue:\n(1) Intero\n(2) Float\n(3) Stringa\n(4) Record\nScelta: ");
                    scanf("%d", &scelta);
                    switch (scelta) {
                        case 1: {
                            testQueueVecInt();
                            break;
                        }
                        case 2: {
                            testQueueVecFloat();
                            break;
                        }
                        case 3: {
                            testQueueVecString();
                            break;
                        }
                        case 4: {
                            testQueueVecRecord();
                            break;
                        }
                        default: {
                            printf("Scelta non valida!\n");
                        }
                    }
                    break;
                }
                case 2: {
                    printf("Inserire tipologia dei dati da utilizzare per la lista della queue:\n(1) Intero\n(2) Float\n(3) Stringa\n(4) Record\nScelta: ");
                    scanf("%d", &scelta);
                    switch (scelta) {
                        case 1: {
                            testQueueListInt();
                            break;
                        }
                        case 2: {
                            testQueueListFloat();
                            break;
                        }
                        case 3: {
                            testQueueListString();
                            break;
                        }
                        case 4: {
                            testQueueListRecord();
                            break;
                        }
                        default: {
                            printf("Scelta non valida!\n");
                        }
                    }
                    break;
                }
                default: {
                    printf("Scelta non valida!\n");
                }
            }
            break;
        }
        default: {
            printf("Scelta non valida!\n");
        }
    }



}

int main()
{
  srand(time(NULL));

  //testMain();
  //testStackListInt();
  testQueueListInt();

  return 0;
}

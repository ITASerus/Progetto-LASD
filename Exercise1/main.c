
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

void printStruct(DataObject* dat, void* _) {
    printf("- ");
    adtWriteToMonitor(dat);
    printf("\n");
}

void mapDoubleInteger(DataObject* dat, void* _) {
    *(int*)dat->value *= 2;
}

void mapSquareFloat(DataObject* dat, void* _) {
    *(float*)dat->value = (*(float*)dat->value)*(*(float*)dat->value);
}

void mapLowerCase(DataObject* dat, void* _) {
   for(int i = 0; i<strlen((char*)dat->value); i++) {
       if((((char*)dat->value)[i] >= 65) && (((char*)dat->value)[i]<=90)) {
           ((char*)dat->value)[i] += 32;
       }
   }
}

void mapUpperCase(DataObject* dat, void* _) {
    for(int i = 0; i<strlen((char*)dat->value); i++) {
        if((((char*)dat->value)[i] >= 97) && (((char*)dat->value)[i]<=122)) {
            ((char*)dat->value)[i] -= 32;
        }
    }
}

void foldSumLesserThanN(DataObject * dat, void *val, void *n) {
    if((*(int*)dat->value < *(int*)n)) {
        *(int*)val += *(int*)dat->value;
    }
}

void foldProdGreaterThanN(DataObject * dat, void *val, void *n) {
    printf("Comparo %f con %f\n", *(float*)dat->value, *(float*)n);
    if((*(float*)dat->value > *(float*)n)) {
        *(float*)val *= *(float*)dat->value;
        printf("Vero, quindi val vale %f\n", *(float*)val);
    }
}

void foldConcatLessOrEqThanN(DataObject * dat, void *val, void *n) {
    printf("Confronto %s con %d\n", (char*)dat->value, *(int*)n);
    if((strlen((char*)dat->value) <= *(int*)n)) {
        printf("Compatibile, realloco\n", strlen(val));

        val = realloc((char*)val, sizeof(char)*(strlen(val) + (strlen(dat->value) + 1)));

        strcat((char*)val, (char*)dat->value);
        printf("Nuova stringa %s\n", (char*)val);
    } else {
        printf("Non compatibile\n");
    }
}

/* ************************************************************************** */

void testStack() {
    StackType* stkTyp = NULL;
    DataType* datatype = NULL;

    int scelta, number;
    printf("Inserire tipologia di implementazione della pila da utilizzare\n(1) Vettore\n(2) Lista\n");
    do {
        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                stkTyp = ConstructStackVecType();
                break;
            }
            case 2: {
                stkTyp = ConstructStackLstType();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Vettore\n(2) Lista\n");
                break;
            }
        }
    } while (scelta != 1 && scelta != 2);

    int tipoScelto;
    printf("Inserire tipologia di dato da gestire\n(1) Intero\n(2) Float\n(3) Stringhe\n(4) Record\n");
    do {
        printf("Scelta: ");
        scanf("%d", &tipoScelto);
        switch (tipoScelto) {
            case 1: {
                datatype = ConstructIntDataType();
                break;
            }
            case 2: {
                datatype = ConstructFloatDataType();
                break;
            }
            case 3: {
                datatype = ConstructStringDataType();
                break;
            }
            case 4: {
                datatype = ConstructRecordDataType();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Intero\n(2) Float\n(3) Stringhe\n(4) Record\n");
                break;
            }
        }
    } while( (tipoScelto<1) || (tipoScelto >4));

    StackObject* stack = stkConstruct(stkTyp);
    DataObject* dataPtr = adtConstruct(datatype);

    do {
        printf("\n***********************************************************************************************\n\n");
        printf("Menu':\n(1) Popolamento randomico della struttura con N elementi\n"
               "(2) Visualizzazione del contenuto della struttura\n");
        switch (tipoScelto) {
            case 1: {
                printf("(3) Somma valori minori di N\n(4) Applicazione 2n per ogni elemento\n");
                break;
            }
            case 2: {
                printf("(3) Prodotto valori maggiori di N\n(4) Applicazione n^2 per ogni elemento\n");
                break;
            }
            case 3: {
                printf("(3) Concatenazione dei valori di lunghezza minore o uguale a N\n(4) Applicazione funzione uppercase/lowercase\n");
                break;
            }
            default: {
                printf("(3) N/A\n(4) N/A\n");
                break;
            }
        }
        printf("(5) Inserimento manuale di un elemento\n"
               "(6) Rimozione dell'elemento in testa alla struttura\n"
               "(7) Stampa elemento in testa alla struttura\n"
               "(8) Ricerca di un elemento\n"
               "(9) Numero degli elementi memorizzati nella struttura\n"
               "(10) Svuotamento della struttura\n"
               "(11) Creazione e stampa di un clone della struttura e\n"
               "     controllo uguaglianza con la struttura principale\n"
               "(0) Deallocazione della stuttura ed uscita dal programma\n"
               "Scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                printf("Numero di elementi da inserire nella struttura: ");
                scanf("%d", &number);

                for(int i = 0; i < number; i++) {
                    adtRandomValue(dataPtr);
                    stkPush(stack, dataPtr);
                }

                printf("Elementi inseriti!\n");
                break;
            }
            case 2: {
                if(!stkEmpty(stack)) {
                    stkMap(stack, printStruct, NULL);
                } else {
                    printf("La pila è vuota!\n");
                }
                break;
            }
            case 3: {
                switch (tipoScelto) {
                    case 1: {
                        int* value = (int*)malloc(sizeof(int));
                        *value = 0;
                        int* n = (int*)malloc(sizeof(int));

                        printf("Inserire N: ");
                        scanf("%d", n);
                        stkFold(stack, foldSumLesserThanN, value, n);
                        printf("Risultato: %d\n", *value);

                        free(value);
                        free(n);

                        break;
                    }
                    case 2: {
                        float* value = (float*)malloc(sizeof(float));
                        *value = 1;
                        float* n = (float*)malloc(sizeof(float));

                        printf("Inserire N: ");
                        scanf("%f", n);
                        stkFold(stack, foldProdGreaterThanN, value, n);
                        printf("Risultato: %f\n", *value);

                        free(value);
                        free(n);

                        break;
                    }
                    case 3: {
                        char* value = (char*)malloc(sizeof(char)); //TODO: Ogni tanto crasha
                        strcpy(value, "");
                        int* n = (int*)malloc(sizeof(int));

                        printf("Inserire N: ");
                        scanf("%d", n);
                        stkFold(stack, foldConcatLessOrEqThanN, value, n);
                        printf("Risultato: %s\n", value);

                        free(value);
                        free(n);

                        break;
                    }
                    default: break;
                }
                break;
            }
            case 4: {
                switch (tipoScelto) {
                    case 1: {
                        stkMap(stack, mapDoubleInteger, NULL);
                        break;
                    }
                    case 2: {
                        stkMap(stack, mapSquareFloat, NULL);
                        break;
                    }
                    case 3: {
                        printf("(1) Applica funzione upperCase\n(2) Applica funzione lowerCase\nScelta: ");
                        scanf("%d", &scelta);
                        switch (scelta) {
                            case 1: {
                                stkMap(stack, mapUpperCase, NULL);
                                break;
                            }
                            case 2: {
                                stkMap(stack, mapLowerCase, NULL);
                                break;
                            }
                            default: {
                                printf("Scleta non valida\n");
                                break;
                            }
                        }
                    }
                    default: {
                        printf("Il tipo di dato scelto non ha funzioni speciali disponibili\n");
                        break;
                    }
                }
                break;
            }
            case 5: {
                printf("Valore da inserire: ");
                adtReadFromKeyboard(dataPtr);
                stkPush(stack, dataPtr);
                break;
            }
            case 6: {
                DataObject* head = stkTopNPop(stack);

                if(head != NULL) {
                    printf("Elemento in testa alla struttura: \n");
                    adtWriteToMonitor(head);
                    printf("\nElemento rimosso!");
                    adtDestruct(head);
                } else {
                    printf("La struttura e' vuota!");
                }

                break;
            }
            case 7: {
                printf("Elemento in testa alla struttura: ");
                dataPtr = stkTop(stack);

                if(dataPtr != NULL) {
                    adtWriteToMonitor(dataPtr);
                    printf("\n");
                } else {
                    printf("La struttura è vuota!\n");
                }
                break;
            }
            case 8: {
                printf("Inserire valore da cercare: ");
                adtReadFromKeyboard(dataPtr);

                if(stkExists(stack, dataPtr)) {
                    printf("Il valore è presente nella struttura\n");
                } else {
                    printf("Il valore NON è presente nella struttura\n");
                }
                break;
            }
            case 9: {
                printf("Il numero di elementi attualmente contenuto nella struttura e': %d\n", stkSize(stack));
                break;
            }
            case 10: {
                stkClear(stack);
                printf("Stack svuotato\n");
                break;
            }
            case 11: {
                StackObject* stackClone = stkClone(stack);
                stkMap(stackClone, printStruct, NULL);
                printf("Controllo di uguaglianza tra il clone dello stack e lo stack principale: ");
                if(stkEqual(stackClone, stack)) {
                    printf("VERO\n");
                } else {
                    printf("FALSO\n");
                }

                printf("Aggiunta di un ulteriore elemento al clone\n");
                adtRandomValue(dataPtr);
                stkPush(stackClone, dataPtr);
                stkMap(stackClone, printStruct, NULL);

                printf("Controllo di uguaglianza tra il clone della queue e la queue principale: ");
                if(stkEqual(stackClone, stack)) {
                    printf("VERO\n");
                } else {
                    printf("FALSO\n");
                }

                stkDestruct(stackClone);
                break;
            }
            case 0: {
                stkDestruct(stack);
                printf("Stack deallocato");
                break;
            }
            default: {
                printf("Opzione non valida!\n");
                break;
            }
        }
    } while (scelta != 0);

    DestructStackLstType(stkTyp);

    switch (tipoScelto) {
        case 1: {
            DestructIntDataType(datatype);
            break;
        }
        case 2: {
           DestructFloatDataType(datatype);
            break;
        }
        case 3: {
            DestructStringDataType(datatype);
            break;
        }
        case 4: {
            DestructRecordDataType(datatype);
            break;
        }
    }
}

void testQueue() {
    QueueType* queTyp = NULL;
    DataType* datatype = NULL;

    int scelta, number;
    printf("Inserire tipologia di implementazione della coda da utilizzare\n(1) Vettore\n(2) Lista\n");
    do {
        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                queTyp = ConstructQueueVecType();
                break;
            }
            case 2: {
                queTyp = ConstructQueueLstType();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Vettore\n(2) Lista\n");
                break;
            }
        }
    } while (scelta != 1 && scelta != 2);

    int tipoScelto;
    printf("Inserire tipologia di dato da gestire\n(1) Intero\n(2) Float\n(3) Stringhe\n(4) Record\n");
    do {
        printf("Scelta: ");
        scanf("%d", &tipoScelto);
        switch (tipoScelto) {
            case 1: {
                datatype = ConstructIntDataType();
                break;
            }
            case 2: {
                datatype = ConstructFloatDataType();
                break;
            }
            case 3: {
                datatype = ConstructStringDataType();
                break;
            }
            case 4: {
                datatype = ConstructRecordDataType();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Intero\n(2) Float\n(3) Stringhe\n(4) Record\n");
                break;
            }
        }
    } while( (tipoScelto<1) || (tipoScelto >4));

    QueueObject* queue = queConstruct(queTyp);
    DataObject* dataPtr = adtConstruct(datatype);

    do {
        printf("\n***********************************************************************************************\n\n");
        printf("Menu':\n(1) Popolamento randomico della struttura con N elementi\n"
               "(2) Visualizzazione del contenuto della struttura\n");
        switch (tipoScelto) {
            case 1: {
                printf("(3) Somma valori minori di N\n(4) Applicazione 2n per ogni elemento\n");
                break;
            }
            case 2: {
                printf("(3) Prodotto valori maggiori di N\n(4) Applicazione n^2 per ogni elemento\n");
                break;
            }
            case 3: {
                printf("(3) Concatenazione dei valori di lunghezza minore o uguale a N\n(4) Applicazione funzione uppercase/lowercase\n");
                break;
            }
            default: {
                printf("(3) N/A\n(4) N/A\n");
                break;
            }
        }
        printf("(5) Inserimento manuale di un elemento\n"
               "(6) Rimozione dell'elemento in testa alla struttura\n"
               "(7) Stampa elemento in testa alla struttura\n"
               "(8) Ricerca di un elemento\n"
               "(9) Numero degli elementi memorizzati nella struttura\n"
               "(10) Svuotamento della struttura\n"
               "(11) Creazione e stampa di un clone della struttura e\n"
               "     controllo uguaglianza con la struttura principale\n"
               "(0) Deallocazione della stuttura ed uscita dal programma\n"
               "Scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                printf("Numero di elementi da inserire nella struttura: ");
                scanf("%d", &number);

                for(int i = 0; i < number; i++) {
                    adtRandomValue(dataPtr);
                    queEnqueue(queue, dataPtr);
                }

                printf("Elementi inseriti!\n");
                break;
            }
            case 2: {
                if(!queEmpty(queue)) {
                    queMap(queue, printStruct, NULL);
                } else {
                    printf("La coda è vuota!\n");
                }
                break;
            }
            case 3: {
                switch (tipoScelto) {
                    case 1: {
                        int* value = (int*)malloc(sizeof(int));
                        *value = 0;
                        int* n = (int*)malloc(sizeof(int));

                        printf("Inserire N: ");
                        scanf("%d", n);
                        queFold(queue, foldSumLesserThanN, value, n);
                        printf("Risultato: %d\n", *value);

                        free(value);
                        free(n);

                        break;
                    }
                    case 2: {
                        float* value = (float*)malloc(sizeof(float));
                        *value = 1;
                        float* n = (float*)malloc(sizeof(float));

                        printf("Inserire N: ");
                        scanf("%f", n);
                        queFold(queue, foldProdGreaterThanN, value, n);
                        printf("Risultato: %f\n", *value);

                        free(value);
                        free(n);

                        break;
                    }
                    case 3: {
                        char* value = (char*)malloc(sizeof(char)); //TODO: Ogni tanto crasha
                        strcpy(value, "");
                        int* n = (int*)malloc(sizeof(int));

                        printf("Inserire N: ");
                        scanf("%d", n);
                        queFold(queue, foldConcatLessOrEqThanN, value, n);
                        printf("Risultato: %s\n", value);

                        free(value);
                        free(n);

                        break;
                    }
                    default: break;
                }
                break;
            }
            case 4: {
                switch (tipoScelto) {
                    case 1: {
                        queMap(queue, mapDoubleInteger, NULL);
                        break;
                    }
                    case 2: {
                        queMap(queue, mapSquareFloat, NULL);
                        break;
                    }
                    case 3: {
                        printf("(1) Applica funzione upperCase\n(2) Applica funzione lowerCase\nScelta: ");
                        scanf("%d", &scelta);
                        switch (scelta) {
                            case 1: {
                                queMap(queue, mapUpperCase, NULL);
                                break;
                            }
                            case 2: {
                                queMap(queue, mapLowerCase, NULL);
                                break;
                            }
                            default: {
                                printf("Scleta non valida\n");
                                break;
                            }
                        }
                    }
                    default: {
                        printf("Il tipo di dato scelto non ha funzioni speciali disponibili\n");
                        break;
                    }
                }
                break;
            }
            case 5: {
                printf("Valore da inserire: ");
                adtReadFromKeyboard(dataPtr);
                queEnqueue(queue, dataPtr);
                break;
            }
            case 6: {
                dataPtr = queHeadNDequeue(queue);

                if(dataPtr != NULL) {
                    printf("Elemento in testa alla struttura: \n");
                    adtWriteToMonitor(dataPtr);
                    printf("\nElemento rimosso!");

                } else {
                    printf("La struttura e' vuota!");
                }

                break;
            }
            case 7: {
                printf("Elemento in testa alla struttura: ");
                dataPtr = queHead(queue);

                if(dataPtr != NULL) {
                    adtWriteToMonitor(dataPtr);
                    printf("\n");
                } else {
                    printf("La struttura è vuota!\n");
                }

                break;
            }
            case 8: {
                printf("Inserire valore da cercare: ");
                adtReadFromKeyboard(dataPtr);

                if(queExists(queue, dataPtr)) {
                    printf("Il valore è presente nella struttura\n");
                } else {
                    printf("Il valore NON è presente nella struttura\n");
                }
                break;
            }
            case 9: {
                printf("Il numero di elementi attualmente contenuto nella struttura e': %d\n", queSize(queue));
                break;
            }
            case 10: {
                queClear(queue);
                printf("Queue svuotata\n");
                break;
            }
            case 11: {
                QueueObject* queueClone = queClone(queue);

                queMap(queueClone, printStruct, NULL);

                printf("Controllo di uguaglianza tra il clone della queue e la queue principale: ");
                if(queEqual(queueClone, queue)) {
                    printf("VERO\n");
                } else {
                    printf("FALSO\n");
                }

                printf("Aggiunta di un ulteriore elemento al clone\n");
                adtRandomValue(dataPtr);
                queEnqueue(queueClone, dataPtr);
                queMap(queueClone, printStruct, NULL);

                printf("Controllo di uguaglianza tra il clone della queue e la queue principale: ");
                if(queEqual(queueClone, queue)) {
                    printf("VERO\n");
                } else {
                    printf("FALSO\n");
                }

                queDestruct(queueClone);
                break;
            }
            case 0: {
                queDestruct(queue);
                printf("Stack deallocato");
                break;
            }
            default: {
                printf("Opzione non valida!\n");
                break;
            }
        }
    } while (scelta != 0);

    DestructQueueLstType(queTyp);

    switch (tipoScelto) {
        case 1: {
            DestructIntDataType(datatype);
            break;
        }
        case 2: {
            DestructFloatDataType(datatype);
            break;
        }
        case 3: {
            DestructStringDataType(datatype);
            break;
        }
        case 4: {
            DestructRecordDataType(datatype);
            break;
        }
    }
}

/* ************************************************************************** */

void testMain() {
    int scelta;

    char* buffer = (char*)malloc(sizeof(char)* MaxStrLen);

    printf("Inserire tipologia di struttra da utilizzare\n(1) Pila\n(2) Coda\n");
    do {
        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: {
                testStack();
                break;
            }
            case 2: {
                testQueue();
                break;
            }
            default: {
                printf("Opzione non valida.\nOpzioni possibili:\n(1) Pila\n(2) Coda\n");
                break;
            }
        }
    } while (scelta != 1 && scelta != 2);
}

int main()
{
  srand(time(NULL));

  testMain();

  return 0;
}

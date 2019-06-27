/**
 * @name Progetto per il corso di Algoritmi e Strutture Dati A/A 2017/2018 - Corso di Laurea in Informatica
 * @author Ernesto De Crecchio - N86001596
 * @date 16/06/2019
 */

#include "utility.h"
#include "testBST.h"
#include "testGraph.h"

/* ************************************************************************** */

int main()
{
  srand(time(NULL));

  /* ************************************************************************ */

  char* buffer = (char*)malloc(sizeof(char) * MaxStrLen); //Buffer riservato all'input dell'utente
  int scelta;
  printf("Inserire struttura da analizzare:\n(1) Abstract Data Type\n(2) Alberi\n(3) Grafi\n");
  do {
    printf("Scelta: ");
    getStr(buffer, MaxStrLen);
    scelta = strtol(buffer, NULL, 10);
    switch (scelta) {
      case 1: {
        //
        break;
      }
      case 2: {
        testBST();
        break;
      }
      case 3: {
        testGraph();
        break;
      }
      default: {
        printf("Opzione non valida.\nOpzioni possibili:\n(1) Abstract Data Type\n(2) Alberi\n(3) Grafi");
        break;
      }
    }
  } while (scelta != 1 && scelta != 2 && scelta!= 3);

  /* ************************************************************************ */

  return 0;
}

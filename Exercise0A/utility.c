
#include "utility.h"

/* ************************************************************************** */

void mapPosZerNeg(void * elm, void * _)
{
  assert(elm != NULL);
  int elmx = *((int *) elm);
  *((int *) elm) = (elmx > 0) ? 1 : ((elmx == 0) ? 0 : -1);
}

void foldParity(void * elm, void * val, void * _)
{
  assert(elm != NULL);
  assert(val != NULL);
  int elmx = *((int *) elm);
  int valx = *((int *) val);
  *((int *) val) = (elmx >= 0) ? valx : -valx;
}

/* ************************************************************************** */

int rndNum(int a, int b)
{
  assert(a <= b);
  return (a + (rand() % (b - a + 1)));
}

char* rndStr(int numChar) { //TODO: rndStr - Il prof non vuole charset ma generazione tramite ASCII
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* newString = (char*)malloc(sizeof(char)*(numChar+1));

    for(uint i = 0; i<numChar; ++i) {
        newString[i] = charset[rndNum(0, 61)];
    }
    newString[numChar] = '\0';

    return newString;
}

/* ************************************************************************** */

void getStr(char * str, uint len)
{
  assert(str != NULL);
  uint i;
  char c;
  for(i = 0; (i < len) && ((c = getchar()) != '\n') && (c != EOF); ++i)
    {
      str[i] = c;
    }
  str[i] = '\0';
}

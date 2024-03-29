
#include "utility.h"

/* ************************************************************************** */

int rndNum(int a, int b)
{
  assert(a <= b);
  return (a + (rand() % (b - a + 1)));
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

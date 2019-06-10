#include "myEqual.h"
#include <string.h>
int myEqualDefault(void * a, void *b)
{
  return a == b;
}
int myEqualInt(void * a, void *b)
{
  int *aa = (int*) a;
  int *bb = (int *) b;
  return *aa == *bb;
}
int myEqualChar(void * a, void *b)
{
  char *aa = (char *) a;
  char *bb = (char *) b;
  return *aa == *bb;
}
int myEqualString(void * a, void *b)
{
  char *aa = (char *) a;
  char *bb = (char *) b;
  return strcmp(aa, bb)==0;
}

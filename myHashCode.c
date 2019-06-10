#include "myHashCode.h"
int myHashCodeDefault(void * a){
  return (int&) a;//错误(int)
}
int myHashCodeInt(void * a){
  int * aa = (int *) a;
  return *aa;
}
int myHashCodeChar(void * a){
  char *aa = (char *) a;
  return *aa;
}
int myHashCodeString(void * a){
  int re = 0;
  char *aa = (char *) a;
  while (*aa){
    re += HASHCODE_MULT * *aa;
    aa++;
  }
  return re;
}

#ifndef MYHASHCODE_H_INCLUDED
#define MYHASHCODE_H_INCLUDED
#include <string.h>
#define HASHCODE_MULT 31
int myHashCodeDefault(void * a);
int myHashCodeInt(void * a);//Int
int myHashCodeChar(void * a);//Char
int myHashCodeString(void * a);//String
#endif // MYHASHCODE_H_INCLUDED

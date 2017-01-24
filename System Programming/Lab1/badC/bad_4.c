#include <stdio.h>
#include <stdlib.h>

int* function1();

int main ()
{
  int *ptr=function1();

  printf("%d",*ptr);

  return 0;
}

int* function1 ()
{
  int a=3;
  int *pointer=&a;  

  return pointer;
}


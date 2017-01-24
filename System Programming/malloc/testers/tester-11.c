// Malloc
// CS 241 Fall 2015
// University of Illinois at Urbana-Champaign

#include <stdio.h>
#include <stdlib.h>


#define M (1024L * 1024L)
#define SIZE (2L * 1024L * M)
#define ITERS 10000

int main() {
  // not sure why we need to do this, but all the other testers perform this
  // initial malloc
  malloc(1);
//printf("I'm at tester 11 line %d\n",__LINE__);
  int i;
  for (i = 0; i < ITERS; i++) {
    char *a = malloc(SIZE);
    if (!a)
      return 1;
//printf("I'm at tester 11 line %d\n",__LINE__);
    *a = 'c';
    if (*a != 'c')
      return 1;
//printf("I'm at tester 11 line %d\n",__LINE__);
    free(a);
//printf("I'm at tester 11 line %d\n",__LINE__);
    a = malloc(SIZE / 2);
//printf("I'm at tester 11 line %d\n",__LINE__);
    char *b = malloc(SIZE / 4);
    if (!a || !b)
      return 1;
//printf("I'm at tester 11 line %d\n",__LINE__);
    *a = 'c';
    if (*a != 'c')
      return 1;
//printf("I'm at tester 11 line %d\n",__LINE__);
    *b = 'c';
    if (*b != 'c')
      return 1;
//printf("I'm at tester 11 line %d\n",__LINE__);
    free(a);
    free(b);
  }

  printf("Memory was allocated, used, and freed!\n");
  return 0;
}

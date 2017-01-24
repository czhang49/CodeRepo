// Malloc
// CS 241 Fall 2015
// University of Illinois at Urbana-Champaign

#include <stdio.h>
#include <stdlib.h>

#define M (1024 * 1024)
#define K (1024)

#ifdef PART2
#define TOTAL_ALLOCS 5 * M
#else
#define TOTAL_ALLOCS 50 * K
#endif

int main() {
  malloc(1);

  int i;
  int **arr = malloc(TOTAL_ALLOCS * sizeof(int *));

  if (arr == NULL) {
    printf("Memory failed to allocate!\n");
    return 1;
  }
//printf("I'm at tester 2 line %d\n",__LINE__);
  for (i = 0; i < TOTAL_ALLOCS; i++) {
//printf("I'm at tester 2 line %d\n",__LINE__);
    arr[i] = malloc(sizeof(int));
//printf("I'm at tester 2 line %d\n",__LINE__);
    if (arr[i] == NULL) {
      printf("Memory failed to allocate!\n");
      return 1;
    }
//printf("I'm at tester 2 line %d\n",__LINE__);
    *(arr[i]) = i;
//printf("I'm at tester 2 line %d\n",__LINE__);
  }
//printf("I'm at tester 2 line %d\n",__LINE__);

  for (i = 0; i < TOTAL_ALLOCS; i++) {

    if (*(arr[i]) != i) {
      printf("Memory failed to contain correct data after many allocations!\n");
      return 2;
    }
  }
//printf("I'm at tester 2 line %d\n",__LINE__);

  for (i = 0; i < TOTAL_ALLOCS; i++){
	//printf("I'm at tester 2 line %d\n",__LINE__);
    free(arr[i]);
}


  free(arr);
  printf("Memory was allocated, used, and freed!\n");
  return 0;
}

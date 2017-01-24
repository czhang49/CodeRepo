#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include "common.h"


// used in descriptors_* functions
static int *descriptors_array = NULL;
static int descriptors_array_size;
static int descriptors_array_capacity;


/**
 * Returns a hash of the given string.
 */
unsigned int hashKey(char * key) {
    unsigned char *p = (unsigned char *) key;
    unsigned h = 2166136261;

    while (*p) {
        h = (h * 16777619) ^ *p++;
    }

    return h;
}


/**
 * Add to the array of additional file descriptors.
 */
void descriptors_add(int fd) {
  if (!descriptors_array) {
    descriptors_array_capacity = 10;
    descriptors_array_size = 0;
    descriptors_array = (int*) malloc(sizeof(int) *
				      descriptors_array_capacity);
      
    assert(descriptors_array);
  }

  if (descriptors_array_size == descriptors_array_capacity) {
    descriptors_array_capacity *= 2;
    descriptors_array = (int*) realloc(descriptors_array, sizeof(int) *
				       descriptors_array_capacity);
  }

  descriptors_array[descriptors_array_size++] = fd;
}
    

/**
 * Close all the file descriptors passed to descriptors_add();
 */
void descriptors_closeall() {
  int i;
  for (i=0; i < descriptors_array_size; i++) {
    close(descriptors_array[i]);
    // fprintf(stderr, "[%d] close %d\n", getpid(), descriptors_array[i]);
  }
}


/**
 * Deallocate the memory used to start the file descriptor list.
 */
void descriptors_destroy() {
  free(descriptors_array);
  descriptors_array = NULL;
}

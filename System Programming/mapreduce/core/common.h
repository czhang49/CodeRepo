#ifndef COMMON_H_MR
#define COMMON_H_MR

/**
 * Returns a hash of the given string.
 */
unsigned int hashKey(char * key);


/**
 * Add to the array of additional file descriptors.
 */
void descriptors_add(int fd);

/**
 * Close all the file descriptors passed to descriptors_add();
 */
void descriptors_closeall();

/**
 * Deallocate the memory used to start the file descriptor list.
 */
void descriptors_destroy();

#endif /* COMMON_H_MR */

// Shell
// CS 241 Fall 2015
#ifndef __CS241_VECTOR_H__
#define __CS241_VECTOR_H__
#include <stdlib.h>
/* An automatically-expanding array of strings.
   As strings are added to it, the array will automatically grow.
   (sort of like a C++ vector<string> or Java ArrayList<String>)

   'size' is the number of elements in array[] that may be accessed
   by Vector_set() and Vector_get(). Calling Vector_set() or Vector_get()
   with index < 0 or index >= size is an error and should cause
   an assertion failure (Google is your friend).

   The size of the array can be changed with Vector_resize() or
   Vector_add().

   'capacity' is number of elements currently allocated for array.
   'size' will always be less than or equal to 'capacity'.

   The reason size and capacity are two different variables is so that
   we don't have to reallocate every time a string is added to the
   array.

   It is initialized with a capacity of 10 and size of 0.  The user
   can add up to 10 strings and array will not need to be
   reallocated-- just change 'size'.  When the user wants to add the
   11th string, the array will be reallocated to hold 20 strings. If
   that fills up, reallocate it to hold 40 strings, and so on.

   Why double the size each time rather than just adding another 10
   elements? Reallocations can be expensive, and the performance
   will probably suffer if you do a lot of them.
 */
typedef struct {
  /* An array of pointers to the strings in the array.
     NULL values are allowed.
   */
  char **array;

  /* The current size of the 'array'. */
  size_t size;

  /* The allocated size of the 'array'. */
  size_t capacity;
} Vector;

/* Allocate and return a new Vector structure. */
Vector *Vector_create();

/* Deallocate a Vector structure.
   Every non-NULL entry in array from array[0] to array[size-1] will
   need to be free()d.
   Also free the vector itself.
 */
void Vector_destroy(Vector *vtr);

/* Return the number of entries in use in this array. */
int Vector_size(Vector *vtr);

/* Sets the size of the array.

   If the array grows, new entries will be initialized to NULL.
   If the array shrinks, entries past the new end of the array
   will be deallocated.

   If the new size is larger than the capacity of the array, the
   capacity will need to be increased, meaning the array will need to
   be reallocated.  The new capacity should be at least twice as big
   as it was before.
 */
void Vector_resize(Vector *vtr, size_t new_size);

/* Allocate a copy of 'str' and store it in array[index].
   If 'str' is NULL, just store NULL in array[index].
   Note that if the vector is allocating memory for the string,
   then it should also be the freeing it (hint,hint)
 */
void Vector_set(Vector *vtr, size_t index, const char *str);

/* Returns the string stored at array[index].
   If array[index]==NULL, this will return NULL.

   This does not return a copy of the string; it returns the actual
   char* stored at array[index]. This means the caller must not
   deallocate the string.
*/
const char *Vector_get(Vector *vtr, size_t index);

/* Apppends a copy of 'str', or NULL if str is NULL
   to the end of the array. */
void Vector_append(Vector *vtr, const char *str);

size_t nextpowtwo(size_t val);
#endif /* __CS241_VECTOR_H__ */

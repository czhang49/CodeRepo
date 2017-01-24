#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libds.h"


/*
  This program provides a wrapper around a reducer() function that
  reads the input data and feeds each pair of values to reducer().
  Compile it with your favorite reducer() function to make a reducer
  executable.
*/

/**
 * A function defined elsewhere which takes to values as input, and reduces
 * them. Returns a malloced string that needs to be freed
 */
extern char * reducer(const char * value1, const char * value2);

void print_ds(const char * key, const char * value) {
    printf("%s: %s\n", key, value);
    fflush(stdout);
}

int main() {
    datastore_t my_datastore;
    datastore_init(&my_datastore);

    char * line = NULL;
    size_t size = 0;

    while (getline(&line, &size, stdin) != -1) {
        char * split = strstr(line, ": ");

        if (!split) {
            fprintf(stderr, "reducer input is malformed: %s\n", line);
            continue;
        }

        *split = '\0';
        char * key = line;
        char * value = split + 2; // account for the extra space
        value[strlen(value)-1] = '\0'; // remove the newline

        // datastore_get returns a copy of the string
        const char * curr_val = datastore_get(&my_datastore, key);
        if (curr_val) {
            char * new_value = reducer(curr_val, value);
            datastore_update(&my_datastore, key, new_value);

            free((char*)curr_val);
            free(new_value);
        } else {
            datastore_put(&my_datastore, key, value);
        }
    }

    datastore_iterate(&my_datastore, print_ds);
    datastore_destroy(&my_datastore);
    free(line);

    return 0;
}

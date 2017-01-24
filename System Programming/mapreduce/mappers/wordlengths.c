#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mapper(const char * data) {
    char * data_copy = strdup(data);

    char * datum = strtok(data_copy, " ");
    while (datum) {
        printf("%zu: 1\n", strlen(datum));
        datum = strtok(NULL, " ");
    }

    free(data_copy);
}

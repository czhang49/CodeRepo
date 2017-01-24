#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void replace_chars(char *str, char from, char to) {
    while (*str) {
	if (*str == from) *str = to;
	str++;
    }
}


void mapper(const char * data) {
    char * data_copy = strdup(data);

    char * datum = strtok(data_copy, " ");

    while (datum) {
	// the difference is just a few pixels :-)
	replace_chars(datum, ':', ';');
        printf("%s: 1\n", datum);
        datum = strtok(NULL, " ");
    }

    free(data_copy);
}

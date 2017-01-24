#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void mapper(const char * data) {
    while (*data) {
	int c = *data++;
	if (isalpha(c)) {
	    printf("letters: 1\n");
	}
    }    
}

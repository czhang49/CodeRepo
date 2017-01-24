#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


/*
  This program provides a wrapper around a mapper() function that
  reads the input data and feeds a line at a time to mapper().
  Compile it with your favorite mapper() function to make a mapper
  executable.
*/


/**
 * A function defined elsewhere which takes a line of input, performs some sort
 * of processing, and sends its output to the specified file descriptor
 */
extern void mapper(const char * data);

int main() {
    // read input from stdin
    char * line = NULL;
    size_t len = 0;
    ssize_t str_len;

    while (-1 != (str_len = getline(&line, &len, stdin))) {
	// remove newline
	if (str_len > 0 && line[str_len-1] == '\n') {
	    line[--str_len] = '\0';

	    // and carriage return
	    if (str_len > 0 && line[str_len-1] == '\r') {
		line[--str_len] = '\0';
	    }
	}
        mapper(line);
	fflush(stdout);
    }

    free(line);
    return 0;
}

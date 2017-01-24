#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void mapper(const char *data) {
  while (*data) {
    int c = *data++;
    if (isalpha(c)) {
      c = tolower(c);
      printf("%c: 1\n", c);
    }
  }
}

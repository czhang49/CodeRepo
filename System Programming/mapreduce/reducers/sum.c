#include <stdlib.h>
#include <stdio.h>

const char * reducer(const char * value1, const char * value2) {
    int count1 = atoi(value1);
    int count2 = atoi(value2);

    char * res;
    asprintf(&res, "%d", count1 + count2);
    return res;
}

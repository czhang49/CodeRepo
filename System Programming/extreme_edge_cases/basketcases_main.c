#include <stdio.h>
#include <stdlib.h>
#include "basketcases.h"
#include "basketcases_tests.h"

int main() {
    if(test_basketcases(&handle_baskets)) {
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }
}

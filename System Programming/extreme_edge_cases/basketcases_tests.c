#include <string.h>
#include "basketcases_tests.h"
#include "basketcases.h"

/**
 * Test various implementations of `handle_baskets`. You are passed the function pointer `func`; you should compare the output of `func`
 * to your implementation of `handle_baskets` for various inputs...
 *
 * @param   func    An implementation of `handle_baskets` that may or may not be correct.
 */
int test_basketcases(basket_report_t *(*func)(basket_t[], size_t)) {
    char *original_string1 = "abcd1";
    char *original_string2 = "abcd2";
    char *original_string3 = "abcd3";

    basket_t *baskets = (basket_t*) calloc(3, sizeof(basket_t));
    baskets[0].label = malloc((strlen(original_string1) + 1) * sizeof(char));
    baskets[1].label= malloc((strlen(original_string2) + 1) * sizeof(char));
    baskets[2].label = malloc((strlen(original_string3) + 1) * sizeof(char));

    strcpy(baskets[0].label, original_string1);
    strcpy(baskets[1].label, original_string2);
    strcpy(baskets[2].label, original_string3);

    basket_report_t *report = handle_baskets(baskets, 3);

    // TODO return 1 if `handle_baskets` worked correctly

    free(baskets[0].label);
    free(baskets[1].label);
    free(baskets[2].label);
    free(baskets);
    free (report);
    return 1;
}

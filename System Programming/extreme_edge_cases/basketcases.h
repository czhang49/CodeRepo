#ifndef __BASKETCASES_H
#define __BASKETCASES_H

#include <stdlib.h>

typedef struct {
    char *label;
    int offset;
} basket_t;

typedef struct {
    int triples_summed;
    basket_t *target_basket;
    basket_t *bad_batch;
} basket_report_t;

basket_report_t *handle_baskets (basket_t baskets[], size_t length);

#endif

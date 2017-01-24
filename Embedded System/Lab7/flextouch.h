#include <p33Fxxxx.h>
//do not change the order of the following 3 definitions
#define FCY 12800000UL
#include <libpic30.h>
#include "lcd.h"
#include "types.h"

void adc_init();
void touch_init();
void touch_select_dim(uint8_t dim);
uint16_t touch_adc();


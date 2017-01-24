#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "crc16.h"
#include "lcd.h"
#include "led.h"
#include "pc_crc16.h"

void uart2_init(uint16_t baud);

int uart2_putc(uint8_t c);

uint8_t uart2_getc();

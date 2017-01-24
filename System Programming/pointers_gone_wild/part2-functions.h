/** @file part2-functions.h */

/*
 * Machine Problem #0
 * CS 241 Fall 2015
 */

#ifndef __MP1_FUNCTIONS_H__
#define __MP1_FUNCTIONS_H__

typedef enum {INT, STRING, FLOAT, ERROR} type_t;

typedef union {
    int intval;
    float floatval;
    char* stringval;
} val_t;

typedef struct {
    type_t type;
    val_t value;
} data_t;

void first_step(int value);
void second_step(int *value);
void double_step(int **value);
void strange_step(void *value);
void empty_step(void *value);
void two_step(void *s, char *s2);
void three_step(char *first, char *second, char *third);
void step_step_step(char *first, char *second, char *third);
void it_may_be_odd(char *a, int b);
void tok_step(char *str);
void tricky_step(data_t* (*(*func)(char*))(data_t*,data_t*));
void the_end(void *orange, void *blue);

#endif

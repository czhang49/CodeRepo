/** @file part2-functions.c */

/*
 * Machine Problem #0
 * CS 241 Fall 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "part2-functions.h"
#include "string.h"

void first_step(int value)
{
    if (value == 81)
        printf("1: Illinois\n");
    else
        printf("1: ERROR\n");
}

void second_step(int *value)
{
    if (*value == 132)
        printf("2: Illinois\n");
    else
        printf("2: ERROR\n");
}

void double_step(int **value)
{
    if (*value[0] == 8942)
        printf("3: Illinois\n");
    else
        printf("3: ERROR\n");
}

void strange_step(void* value)
{
    if(*(int*)(value+5) == 15)
        printf("4: Illinois\n");
    else
        printf("4: ERROR\n");
}

void empty_step(void *value)
{
    /* Sanity check to prevent a seg fault */
    if (value == NULL) {
        printf("5: ERROR\n");
        return;
    }

    if (((char *)value)[3] == 0)
        printf("5: Illinois\n");
    else
        printf("5: ERROR\n");
}

void two_step(void *s, char *s2)
{
    /* Sanity check to prevent a seg fault */
    if (s2 == NULL) {
        printf("6: ERROR\n");
        return;
    }

    if (s == s2 && s2[3] == 'u')
        printf("6: Illinois\n");
    else
        printf("6: ERROR\n");
}

void three_step(char *first, char *second, char *third)
{
    if (third == second + 2 && second == first + 2)
        printf("7: Illinois\n");
    else
        printf("7: ERROR\n");
}

void step_step_step(char *first, char *second, char *third)
{
    if (third[3] == second[2] + 8 && second[2] == first[1] + 8)
        printf("8: Illinois\n");
    else
        printf("8: ERROR\n");
}

void it_may_be_odd(char *a, int b)
{
    /* Sanity check to prevent a seg fault */
    if (a == NULL) {
        printf("9: ERROR\n");
        return;
    }

    if (*a == b && b > 0)
    {
        printf("9: Illinois\n");
    }
    else
        printf("9: ERROR\n");
}

void tok_step(char* str)
{
    char* a = strtok(str, ",");
    a = strtok(NULL, ",");
    if(strcmp(a, "CS241")==0)
        printf("10: Illinois\n");
    else
        printf("10: ERROR\n");
}

void tricky_step(data_t*(*(*func)(char*))(data_t*,data_t*)) {

    data_t* int1 = malloc(sizeof(data_t));
    data_t* int2 = malloc(sizeof(data_t));
    data_t* float1 = malloc(sizeof(data_t));
    data_t* str1 = malloc(sizeof(data_t));

    int1->type = INT;
    int1->value.intval = 5;

    int2->type = INT;
    int2->value.intval = 10;

    float1->type = 	FLOAT;
    float1->value.floatval = 4.2;

    str1->type = STRING;
    str1->value.stringval = "Hello ";

    printf("line %d before first plus symbol operated\n",__LINE__);
    data_t* intresult = func("+")(int1,int2);
    printf("line %d first plus symbol operated\n",__LINE__);
    printf("%d\n",intresult->value.intval);
    if(intresult->value.intval != 15) {
        printf("11: ERROR int int \n");
        exit(1);
    }
    printf("%d",intresult->value.intval);
    printf("tricky step function line %d operated\n",__LINE__);
    free(int1);
    printf("tricky step function line %d operated\n",__LINE__);
    free(int2);
    printf("tricky step function line %d operated\n",__LINE__);

    data_t* floatresult = func("-")(intresult, float1);
    if((floatresult->value.floatval-10.800000) > 0.00001) {
        printf("%f \n",floatresult->value.floatval);
        printf("11: ERROR int float\n");
        exit(1);
    }
    free(intresult);

    printf("tricky step function line %d operated\n",__LINE__);
    printf("the passed in float value is %f\n",floatresult->value.floatval);
    data_t* strresult = func("+")(str1,floatresult);
    printf("tricky step function line %d operated\n",__LINE__);
    if(strcmp(strresult->value.stringval,"Hello 10.80")) {
        printf("11: ERROR string float plus\n");
        exit(1);
    }
    printf("tricky step function line %d operated\n",__LINE__);
    free(str1);
    free(floatresult);

    printf("tricky step function line %d operated\n",__LINE__);
    data_t* error = func("-")(strresult,float1);
    if(error->type == ERROR) {
        printf("11: Illinois\n");
    } else {
        printf("11: ERROR string float minus\n");
    }
    printf("tricky step function line %d operated\n",__LINE__);
    free(strresult->value.stringval);
    free(strresult);
    free(float1);
    free(error);
}

void the_end(void *orange, void *blue)
{
    printf("the char is %c; and the int is %d\n",((char*)blue)[0],*((int*)orange));
    if (orange != NULL && orange == blue && ((char *)blue)[0] == '1' && *((int *)orange) % 3 == 0)
    {
        printf("12: Illinois\n");
    }
    else
        printf("12: ERROR\n");
}

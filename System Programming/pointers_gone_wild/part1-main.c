/** @file part1-main.c */

/*
 * Machine Problem #0
 * CS 241 Fall 2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "part1-functions.h"

int main()
{
    printf("== one() ==\n");
    one(3, 4);
    one(10, 10);


    printf("== two() ==\n");
    const char* a = "20";
    two(a);
    const char* b = "100";
    two(b);

    printf("== three() ==\n");
    three();


    printf("== four() ==\n");
    four(0.5);
    four(1.5);


    printf("== five() ==\n");
    const int num1 = 3;
    const int num2 = 3;
    five(&num1, &num2);

    const int num3 = 4;
    five(&num1, &num3);


    printf("== six() ==\n");
    float *p_six;
    int i4 = 4, i432 = 432;

    p_six = six(&i4);
    printf("%d == %f\n", i4, *p_six);
    free(p_six);

    p_six = six(&i432);
    printf("%d == %f\n", i432, *p_six);
    free(p_six);


    printf("== seven() ==\n");
    const char s = 'S';
    seven(&s);
    const char t = '_';
    seven(&t);


    printf("== eight() ==\n");
    eight();


    printf("== nine() ==\n");
    nine();


    printf("== ten() ==\n");
    int i_ten = 100;
    ten(&i_ten);
    printf("%d == 0?\n", i_ten);


    printf("== eleven() ==\n");
    eleven("World!");


    printf("== twelve() ==\n");
    twelve();


    printf("== thirteen() ==\n");
    thirteen(10);


    printf("== fourteen() ==\n");
    fourteen("red");
    fourteen("orange");
    fourteen("blue");
    fourteen("green");


    printf("== fifteen() ==\n");
    fifteen(1);
    fifteen(2);
    fifteen(3);


    printf("== sixteen() ==\n");
    char *str = sixteen();
    printf("%s\n", str);
    free(str);


    printf("== seventeen() ==\n");
    seventeen(35);
    seventeen(20);


    printf("== eighteen() ==\n");
    eighteen(3);
    eighteen(5);


    printf("== clear_bits() ==\n");
    long int result;

    result = clear_bits(0xFF, 0x55);
    printf("%ld\n", result);

    result = clear_bits(0x00, 0xF0);
    printf("%ld\n", result);

    result = clear_bits(0xAB, 0x00);
    printf("%ld\n", result);

    result = clear_bits(0xCA, 0xFE);
    printf("%ld\n", result);

    result = clear_bits(0x14, 0x00);
    printf("%ld\n", result);

    result = clear_bits(0xBB, 0xBB);
    printf("%ld\n", result);

    return 0;
}

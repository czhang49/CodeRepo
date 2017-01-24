/** @file part2-main.c */

/*
 * Machine Problem #0
 * CS 241 Fall 2015
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "part2-functions.h"
typedef data_t* (*DataPointer)(data_t*, data_t*);
typedef DataPointer (*funcPointer)(char*);

data_t* addData(data_t* first, data_t* second){
  printf("addData Called\n");
  data_t* data_return = malloc(sizeof(data_t));
  if (first->type==INT && second->type==INT){
    printf("addData INT INT called\n");
    data_return->type=INT;
    data_return->value.intval=first->value.intval+second->value.intval;
    printf("first int:%d, second int:%d, return int:%d \n",first->value.intval,second->value.intval,data_return->value.intval);
  }  
    
  if (first->type==STRING && second->type==FLOAT){
    printf("add Data String Float is called\n");
    data_return->type=STRING;
    data_return->value.stringval= malloc(sizeof(char)*40);
    sprintf(data_return->value.stringval,"%s%.2f",first->value.stringval,second->value.floatval);
  }  
  return data_return;
}
 
data_t* substractData(data_t* first, data_t* second){
  
  data_t* data_return = malloc(sizeof(data_t));
  if (first->type==INT && second->type==FLOAT){
    data_return->type=FLOAT;
    data_return->value.floatval=first->value.intval-second->value.floatval;
  }  
    
  if (first->type==STRING && second->type==FLOAT){
    data_return->type=ERROR;
  }  
  return data_return;
}

DataPointer SymbolManip (char* symbol){
  DataPointer funcPointer;
  printf("%s \n",symbol);
  if (*symbol=='+'){
    funcPointer=&addData;
  }else{
    funcPointer=&substractData;
  }

  return funcPointer;
}

/**
 * (Edit this function to print out the twelve "Illinois" lines in part2-functions.c in order.)
 */
int main()
{   //1
    int for_first=81;
    first_step(for_first);
    //2
    int for_second=132;
    second_step(&for_second);    
    //3
    int** for_double= (int**)malloc(sizeof(int*));
    *for_double= (int*)malloc(sizeof(int));
    for_double[0][0]=8942;
    double_step(for_double);
    free(for_double[0]);
    free(for_double);
    //4
    int trial=15;
    void* for_strange=malloc (10);
    *(int*)(for_strange+5)=trial;
    strange_step(for_strange);
    free(for_strange);
    //5
    void* for_empty= malloc(10);
    *(char*)(for_empty+3)=0;
    empty_step(for_empty);
    free(for_empty);    
    //6
    char* for_two_char= (char*) malloc(10*sizeof(char));
    for_two_char[3]='u';
    void* for_two_void= for_two_char;
    two_step(for_two_void,for_two_char);
    free(for_two_char);
    //7
    char for_three_nothing[5];
    char* for_three_first=for_three_nothing;
    char* for_three_second= for_three_first +2;
    char* for_three_third= for_three_second+2;
    three_step(for_three_first,for_three_second,for_three_third);
    //8
    char s_s_s_first[4];
    char s_s_s_second[4];
    char s_s_s_third[4];
    s_s_s_first[1]=0;
    s_s_s_second[2]=s_s_s_first[1]+8;
    s_s_s_third[3]=s_s_s_second[2]+8;
    step_step_step(s_s_s_first,s_s_s_second,s_s_s_third);
    //9  
    char odd[1];
    int b=1;
    *odd =b;
    it_may_be_odd(odd,b);
    //10
    char tok[]="jj,CS241,";
    tok_step(tok);
    //11
printf("main function line %d \n",__LINE__);
    funcPointer trialPointer=&SymbolManip;
printf("main function line %d \n",__LINE__);   
    tricky_step(trialPointer);  
printf("main function line %d \n",__LINE__);   
    //12
    void* for_end = malloc(sizeof(char)*8);
    *(char*) for_end=49;
    *(char*) (for_end+1)=29;
    *(char*) (for_end+2)=0;
    *(char*) (for_end+3)=0;
    *(char*) (for_end+4)=1;
    *(char*) (for_end+5)=0;
    *(char*) (for_end+6)=0;
    *(char*) (for_end+7)=0;
    void* for_end_2=for_end;
    the_end(for_end,for_end_2);

    return 0;
}

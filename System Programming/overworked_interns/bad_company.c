// Overworked Interns
// CS 241 Fall 2015

#define _GNU_SOURCE
#include "company.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Bad solution that will deadlock
void *work_interns(void *p) {
  CompanyData *company = (CompanyData *)p;
  pthread_mutex_t *intern_left, *intern_right;
  while (running) {
    intern_left = company->intern_left;
    intern_right = company->intern_right;
    printf("Company %d needs their interns!\n", company->number);
    pthread_mutex_lock(intern_left);
    usleep(10);
    pthread_mutex_lock(intern_right);
    printf("Company %d is working\n", company->number);
    usleep(1 + rand() % 3);
    company->hire_count++;
    pthread_mutex_unlock(intern_right);
    pthread_mutex_unlock(intern_left);
    printf("Company %d has finished working with us\n", company->number);
  }
  return NULL;
}

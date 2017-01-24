// Overworked Interns
// CS 241 Fall 2015

#define _GNU_SOURCE
#include "company.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int running = 1; // Flag for keeping the simulator on (dont touch it!)
// Roughly based on code from http://rosettacode.org/
int main(int argc, char *argv[]) {
  // Standard Argument Parsing
  if (argc != 3) {
    printf("Please provide the number of companies and interns you want for "
           "this simulation\n");
    exit(1);
  }
  // Error checking the number of companies and interns
  int num_companies = atoi(argv[1]);
  int num_interns = atoi(argv[2]);
  if (num_companies <= 0 || num_interns <= 0) {
    // Exercise for the reader: what if there is only one intern?
    printf("Please provide a postive number of companies and interns\n");
    exit(1);
  }

  printf("Running simulation with %d companies and %d interns\n", num_companies,
         num_interns);
  srand(0); // Make rand()/scheduling somewhat repeatable

  // One mutex per intern
  // Since humans are inherently a critical section. // this provide some thought into how to create mutex , aka critical section
  pthread_mutex_t interns[num_interns];
  CompanyData companies[num_companies];

  // Initializing said mutexes
  for (int i = 0; i < num_interns; i++) {
    int failed = pthread_mutex_init(&interns[i], NULL);
    if (failed) {
      printf("Failed to initialize mutexes.");
      exit(1);
    }
  }

  // Creating the companies and assigning their interns
  for (int i = 0; i < num_companies; i++) {
    CompanyData *company;
    company = &companies[i];
    company->number = i;
    company->intern_left = &interns[i % num_interns];
    company->intern_right = &interns[(i + 1) % num_interns];
    company->hire_count = 0;
    company->running_time = i * 10;
    company->fail =
        pthread_create(&company->thread, NULL, work_interns, company);
  }

  sleep(20); // Billing cycle
  running = 0;
  printf("cleanup time\n");

  // Time to collect money from companies
  int total = 0; // Number of billable days
  for (int i = 0; i < num_companies; i++) {
    CompanyData *company = &companies[i];
    if (!company->fail && pthread_join(company->thread, NULL)) {
      // WHOOPS!
      printf("error joining thread for %d", company->number);
      exit(1);
    } else {
      // Mo Money Mo Problems!
      printf("Company %d used our services for %d billable days.\n",
             company->number, company->hire_count);
      total += company->hire_count;
    }
  }
  printf("\nTotal Billable days : %d\n", total);
  return 0;
}

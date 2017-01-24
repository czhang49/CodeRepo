// Overworked Interns
// CS 241 Fall 2015

#include <pthread.h>
extern volatile int running;
typedef struct CompanyData {
  pthread_mutex_t *intern_left, *intern_right;
  int number;
  pthread_t thread;
  int running_time;
  int fail;
  int hire_count;
} CompanyData;
// This is the start_ruotine that the company uses to grab the intern to the
// left and right
void *work_interns(void *p);

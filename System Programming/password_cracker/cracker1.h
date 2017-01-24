#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <crypt.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

#include "common.h"
#include "thread_status.h"

typedef struct task_node{
	
	char username[9];
	char hash[14];
	char password_prefix[9];	

} task_node;

typedef struct thread_pool{

	pthread_mutex_t lock;
	queue_t* task_queue;
	pthread_t* worker_threads;
	size_t taskqueue_maxsize;
	int thread_count;
	bool ifquit;
	int success_crack;
	int fail_crack;

} thread_pool;


int start(int thread_count);

// create all the variables in the thread pool, but does not start running the thread yet.
thread_pool* thpl_create(int thread_count);

// destroy all the variables in the thread pool, including mutex, condition variable and heap allocated variables.
void thpl_destroy(thread_pool* pool);

// The function to run for each thread
void* thpl_thread(void* pool);

// user-did crack password wrapper function
bool crack_password (task_node* tasknd, int thread_number);

// start all the threads
void thpl_start(thread_pool* pool);

// creack password function copied from cracker0.c
bool crackPassword(const char *username, const char *target_hash,
                   const char *partial_pw, int thread_number);


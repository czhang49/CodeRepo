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
	
	int start_num;
	int num_iter;	

} task_node;

typedef struct task_hash{
	char username[9];
	char hash[14];
	char password_prefix[9];

} task_hash;

// because task is grabbed one by one. no queue. 
// the reusable barrier made sure of the sychronization. the taskqueue is just a preallocated junk of memory.
typedef struct thread_pool{

	pthread_mutex_t lock;

	barrier_t* task_bar;
	task_node* task_queue;
	task_hash* word_info;
	pthread_t* worker_threads;

	int thread_count;
	bool ifquit;
	bool iffound;
	char password[20];
	int num_hash;

} thread_pool;


int start(int thread_count);

// create all the variables in the thread pool, but does not start running the thread yet.
thread_pool* thpl_create(int thread_count);

// destroy all the variables in the thread pool, including mutex, condition variable and heap allocated variables.
void thpl_destroy(thread_pool* pool);

// The function to run for each thread
void* thpl_thread(void* pool);

// start all the threads
void thpl_start(thread_pool* pool);

// creack password function copied from cracker0.c
void crackPassword(const char *username, const char *target_hash, const char *partial_pw, int thread_number, task_node* tasknd_ptr, void* pool);


void thpl_create_parjobs(const char* username, const char* hash, const char* password_prefix, thread_pool* pool_ptr);

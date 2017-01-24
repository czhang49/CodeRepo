#define _GNU_SOURCE
#include <time.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "common.h"

/* Returns a "wall clock" timer value in seconds.
   This timer keeps ticking even when the thread or process is idle. */
double getTime() {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return t.tv_sec + 1e-9 * t.tv_nsec;
}

/* Returns a process-wide CPU time value in seconds.
   This will tick faster than getTime() if mutiple threads are busy. */
double getCPUTime() {
  struct timespec t;
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
  return t.tv_sec + 1e-9 * t.tv_nsec;
}

/* Return a thread-specific CPU time value in seconds.
   This timer only ticks when the current thread is not idle. */
double getThreadCPUTime() {
  struct timespec t;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t);
  return t.tv_sec + 1e-9 * t.tv_nsec;
}

/* Given a string like "abc.....", return the number of letters in it. */
int getPrefixLength(const char *str) {
  char *first_dot = strchr(str, '.');
  if (first_dot)
    return first_dot - str;
  else
    return strlen(str);
}

/* Set 'result' to the string that you'd get after replacing every
   character with 'a' and calling incrementString() on it 'n' times. */
void setStringPosition(char *result, long n) {
  char *p = result + strlen(result) - 1;

  while (p >= result) {
    *p-- = 'a' + (n % 26);
    n /= 26;
  }
}

/* Increment the letters in 'str'.
   Returns 1 if the increment is successful.
   Returns 0 if all the letters in the string are 'z'. */
int incrementString(char *str) {
  assert(str);

  char *p = str + strlen(str) - 1;

  // find the last character after the prefix that is not a z
  while (p >= str && *p == 'z')
    p--;

  // if we found one, increment it
  if (p >= str) {

    // increment this character and move to the next one
    (*p++)++;

    // and set all the remaining characters to 'a'
    while (*p)
      *p++ = 'a';

    return 1;

  } else {

    // reached the end
    return 0;
  }
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// This part is the thread-safe queue that is produced in the lab

/**
 *  Given a queue_element, place it on the queue.  Can be called by multiple threads.
 *  Blocks if the number of items on the queue is equal to the queue's max size
 */
void queue_push(queue_t* queue, void* data) {

	pthread_mutex_lock(&(queue->m));
	while (queue->count == queue->maxSize){
		pthread_cond_wait(&(queue->cv),&(queue->m));
	}
	
	queue_node_t* curr = queue->head;
	while (curr!=NULL){
		curr = curr->next;
	}
	
	curr = malloc (sizeof(queue_node_t));
	curr->next =NULL;
	curr->data = data;
	
	if (queue->tail !=NULL){
		queue->tail->next = curr;
	}
	queue->tail = curr;
	if (queue->head==NULL){
		queue->head = curr;
	}
	queue->count++;
	
	pthread_cond_broadcast(&(queue->cv));
	pthread_mutex_unlock(&(queue->m));
	
}

/**
 *  Retrieve the queue_element at the front of the queue.  Can be called by multiple threads.
 *  Blocks if there are no tasks on the queue.
 */
void* queue_pull(queue_t* queue) {

	pthread_mutex_lock(&(queue->m));
	while(queue->count == 0){
		pthread_cond_wait(&(queue->cv),&(queue->m));
	}	
	
	//printf("This is queue.c line %d, head pointer is %p\n",__LINE__,queue->head);
	void* data_return = queue->head->data;
	
	//printf("This is queue.c line %d\n",__LINE__);
	queue_node_t* curr = queue->head;
	if (queue->head->next == NULL){
		queue->head=NULL;
		queue->tail=NULL;
	}else{	
		queue->head = queue->head->next;
		//printf("This is queue.c line %d, head pointer is %p\n",__LINE__,queue->head);
	}
	free(curr);
	queue->count--;
	//printf("This is queue.c line %d\n",__LINE__);
	pthread_cond_broadcast(&(queue->cv));
	pthread_mutex_unlock(&(queue->m));
	return data_return;
}

/**
 *  Initializes the queue
 */
void queue_init(queue_t* queue, int maxSize){

	queue->head = NULL;
	queue->tail = NULL;
	queue->maxSize = maxSize;
	queue->count = 0;
	pthread_mutex_init(&(queue->m),NULL);
	pthread_cond_init(&(queue->cv),NULL);
}

/**
 *  Destorys the queue, freeing any remaining nodes in it.
 */
void queue_destroy(queue_t* queue){

	queue_node_t* curr=queue->head;
	queue_node_t* prev;

	while(curr!=NULL){
		prev=curr;
		//free(curr->data); The data does not need to be freed. The user need to free the data, because the form of the data is designated by the user
		curr = curr->next;
		free(prev);
	}

	pthread_mutex_destroy(&(queue->m));
	pthread_cond_destroy(&(queue->cv));

	//free(queue); The queue itself do not need to be freed. The user is responsible to destroy the queue, because the form of the queue is designated by the user. The destroy queue only destroy the nodes in the queue
	//  there are three levels of stuff, the first level is the queue structure, the second level is the nodes in the queue, the third level is the data itself. Because only the nodes in the queue are created by the functions in this file, so its only need to destroy the nodes, the queue itself and the data are user designated, so the user are responsible for the deletion of their stuff.
}

// This above part is the thread-safe queue that is produced in the lab
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// This is the reusable barrier code
/**
 * In this file you will implement a reusable barrier. This means that if I
 * call barrier_wait a second time on this barrier it will still function.  We
 * recommend you implement a throwaway barrier first. You can do this by
 * implementing just barrier_waitup. The functions waitup and waitdown are just
 * hints. You do not HAVE to use them. You may also change barrier_wait as
 * well.
 *
 * The return values are for indicating error. These are only for your own
 * testing purposes and will not be autograded.
 */

/**
 * Initialize your barrier.
 * @param num_threads: The number of threads that must reach the barrier
 *                     in order to release the rest.
 */
int barrier_init(barrier_t *barrier, unsigned num_threads)
{
	int error=0;
	int mx_init, cond_init;
	mx_init=pthread_mutex_init(&(barrier->mtx),NULL);
	cond_init=pthread_cond_init(&(barrier->cv),NULL);	

	barrier->n_threads = num_threads;
	//barrier->done=0;
	barrier->count_up=0;
	barrier->count_down=0;

	if(mx_init || cond_init){
		error=1;
	}

    	return error;
}

/**
 * Destroy your barrier.
 */
int barrier_destroy(barrier_t *barrier)
{
	int error=0;
	int mx_destro, cond_destro;
	mx_destro=pthread_mutex_destroy(&(barrier->mtx));
	cond_destro=pthread_cond_destroy(&(barrier->cv));	


	if(mx_destro || cond_destro){
		error=1;
	}

    	return error;
}

/**
 * Helper function for first step of barrier_wait. As the name it implies, it
 * probably does something in an upwards direction...
 */
int barrier_waitup(barrier_t *barrier)
{
	pthread_mutex_lock(&(barrier->mtx));
	barrier->count_up ++;
	if (barrier->count_up%(barrier->n_threads)==0){
		pthread_cond_broadcast(&(barrier->cv));
	}
	while (barrier->count_up%(barrier->n_threads)){
		pthread_cond_wait(&(barrier->cv),&(barrier->mtx));
	}
	
	pthread_mutex_unlock(&(barrier->mtx));

	
	return 0;
}

/**
 * Helper function for second step of barrier_wait. As the name it implies, it
 * probably does something in a downwards direction...
 */
int barrier_waitdown(barrier_t *barrier)
{
	pthread_mutex_lock(&(barrier->mtx));
	barrier->count_down ++;
	if (barrier->count_down%(barrier->n_threads)==0){
		pthread_cond_broadcast(&(barrier->cv));
	}
	while (barrier->count_down%(barrier->n_threads)){
		pthread_cond_wait(&(barrier->cv),&(barrier->mtx));
	}
	
	pthread_mutex_unlock(&(barrier->mtx));

	return 0;
}

/**
 * With the intended solution we have in mind, you do not have to change this
 * function. However, as stated before, you may implement this function
 * differently if you wish.
 */
int barrier_wait(barrier_t *barrier)
{
    barrier_waitup(barrier);
    barrier_waitdown(barrier);
    return 0;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

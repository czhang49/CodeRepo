#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "semamore.h"


/** 
 * Initializes the Semamore. Important: the struct is assumed to have been malloc'ed by the user.
 * Example:
 * 	Semamore *s = malloc(sizeof(Semamore));
 * 	semm_init(s, 5, 10);
 * There is no need to modify this function. 
 */ 

void semm_init(Semamore *s, int value, int max_val){

	s->value = value;
	s->max_val = max_val;

	pthread_mutex_init(&s->m, NULL);
	pthread_cond_init(&s->cv, NULL);

}

/** 
 *  Should block when the value in the Semamore struct (See semamore.h) is at 0. 
 *  Otherwise, should decrement the value. 
 */ 

void semm_wait(Semamore *s){

	pthread_mutex_lock(&(s->m));
	while((s->value)==0){ 
		pthread_cond_wait(&(s->cv),&(s->m));
	}

	s->value --;
	pthread_cond_broadcast(&(s->cv));
	pthread_mutex_unlock(&(s->m));

}

/** 
 *  Should block when the value in the Semamore struct (See semamore.h) is at max_value. 
 *  Otherwise, should increment the value. 
 */ 

void semm_post(Semamore *s){

	pthread_mutex_lock(&(s->m));
	while((s->value)==s->max_val){ 
		pthread_cond_wait(&(s->cv),&(s->m));
	}

	s->value ++;
	pthread_cond_broadcast(&(s->cv));
	pthread_mutex_unlock(&(s->m));

}

/**
 * Takes a pointer to a Semamore struct to help cleanup some members of the struct.
 * The actual Semamore struct must be freed by the user.
 * Example:
 *	semm_destroy(s);
 *	free(s);
 */

void semm_destroy(Semamore *s){
	
	pthread_mutex_destroy(&(s->m));
	pthread_cond_destroy(&(s->cv));
}



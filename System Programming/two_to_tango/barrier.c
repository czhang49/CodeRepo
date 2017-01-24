#include "barrier.h"

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

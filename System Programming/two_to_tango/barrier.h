#include <pthread.h>
#include <stdbool.h>

/**
 * You may modify this struct as you wish. We have left some fields and
 * suggested usage that you may find useful.
 */
typedef struct barrier_t
{
    pthread_mutex_t mtx;
    pthread_cond_t cv;
    // Total number of threads
    unsigned n_threads;
    // Increasing or decreasing count
    // Hint: Why is there both a barrier_waitdown & a barrier_waitup barrier.c?
    unsigned count_up;
    unsigned count_down;
    // Indicates when all threads have arrived
    //bool done;
} barrier_t;

/**
 * You may not modify the function signatures of the 3 functions in this header
 * file and you must implement them in your barrier.c.
 */
int barrier_destroy(barrier_t *barrier);
int barrier_init(barrier_t *barrier, unsigned num_threads);
int barrier_wait(barrier_t *barrier);

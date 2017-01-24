#ifndef __CRACKER_COMMON_H__
#define __CRACKER_COMMON_H__

/* Returns a "wall clock" timer value in seconds.
   This timer keeps ticking even when the thread or process is idle. */
double getTime();

/* Returns a process-wide CPU time value in seconds.
   This will tick faster than getTime() if mutiple threads are busy. */
double getCPUTime();

/* Return a thread-local CPU time value in seconds.
   This timer only ticks when the current thread is not idle. */
double getThreadCPUTime();

/* Given a string like "abc.....", return the number of letters in it. */
int getPrefixLength(const char *str);

/* Set 'result' to the string that you'd get after replacing every
   character with 'a' and calling incrementString() on it 'n' times. */
void setStringPosition(char *result, long n);

/* Increment the letters in 'str'.
   Returns 1 if the increment is successful.
   Returns 0 if all the letters in the string are 'z'.

   For example:
     If str=="howdy", str will be changed to "howdz"
       and the function will return 1.
     If str=="jazz", str will be changed to "jbaa"
       and the function will return 1.
     If str=="zzzzzz", str will be unchanged and the
       function will return 0.

   'str' must contain only lowercase letters, and it will contain only
   lowercase letters when the function returns.
*/

int incrementString(char *str);



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// This part is the thread-safe queue that is produced in the lab


typedef struct queue_node_t {

  struct queue_node_t *next;
  void* data;
} queue_node_t;

typedef struct {

  queue_node_t *head, *tail;
  int count;
  int maxSize;
  pthread_cond_t cv;
  pthread_mutex_t m;
} queue_t;

/* Put a task onto the queue. */
void queue_push(queue_t* queue, void* data);

/* If the queue is empty, then this call will block until a put call completes. */
void* queue_pull(queue_t* queue);

void queue_init(queue_t* queue, int maxSize);

void queue_destroy(queue_t* queue);

// This above part is the thread-safe queue that is produced in the lab
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//This is the reusable barrier.
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

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#endif /* __CRACKER_COMMON_H__ */

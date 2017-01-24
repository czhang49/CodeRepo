#include "barrier.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 5

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_t pthreads[NUM_THREADS];
barrier_t barrier;

long int count = 0;
int pass1, pass2;

void *thread_func_throwaway(void *var)
{
    sleep((unsigned)var);
    pthread_mutex_lock(&mtx);
    count++;
    pthread_mutex_unlock(&mtx);
    barrier_wait(&barrier);

    return (void *)count;
}

void *thread_func_reusable(void *var)
{
    usleep((unsigned)var);
    int i;
    for (i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&mtx);
        count++;
        pthread_mutex_unlock(&mtx);
        usleep((unsigned)var);
        barrier_wait(&barrier);
        pthread_mutex_lock(&mtx);
        printf("%ld\n", count);
        if (count % 5)
            pass2 = 0;
        pthread_mutex_unlock(&mtx);
        barrier_wait(&barrier);
    }

    return (void *)count;
}

int main()
{
    long int i, ret;
    pass1 = 1;
    pass2 = 1;

    pthread_mutex_init(&mtx, NULL);
    barrier_init(&barrier, NUM_THREADS);

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&pthreads[i], NULL, &thread_func_throwaway, (void *)i);
    }
    printf("Throwaway Test:\n");
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(pthreads[i], (void **)(&ret));
        printf("%ld\n", ret);
        /*Desired output:
         * 5
         * 5
         * 5
         * 5
         * 5
         */
        if (ret != 5)
            pass1 = 0;
    }

    printf("Reusable Test:\n");
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&pthreads[i], NULL, &thread_func_reusable, (void *)i);
    }

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(pthreads[i], (void **)(&ret));
        /*Desired output:
         * 10
         * 10
         * 10
         * 10
         * 10
         * 15
         * 15
         * 15
         * 15
         * 15
         * 20
         * 20
         * 20
         * 20
         * 20
         */
    }

    if (!pass1)
    {
        printf("Test 1 failed\n");
    }
    else
    {
        printf("Test 1 passed\n");
    }

    if (!pass2)
    {
        printf("Test 2 failed\n");
    }
    else
    {
        printf("Test 2 passed\n");
    }

    pthread_mutex_destroy(&mtx);
    barrier_destroy(&barrier);

    return 0;
}

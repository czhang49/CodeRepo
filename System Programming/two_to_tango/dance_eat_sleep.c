/*
 * CS241
 * University of Illinois
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "barrier.h"

/*
 * struct for each customer
 */
typedef struct _customer_t
{
    pthread_t thread;
    char *name;
    int id;
    barrier_t *barrier;
} customer_t;

customer_t *customers; // array of customers
////FOR TESTING
int num_eating;
int num_dancing;
int max_eating;
int max_dancing;
int num_customers;
int timer;
////FOR TESTING

////SYNCHRONIZATION CONSTRUCTS
sem_t dance_sem;
sem_t eat_sem;
barrier_t food_barrier;
barrier_t dance_barrier;
////SYNCHRONIZATION CONSTRUCTS

// mutexes for incrementing the # of people who are eating of dancing
pthread_mutex_t dance_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t eat_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t timer_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * This function is run by a thread which is ready to dance!
 */
void declareDancing(int custid)
{
    pthread_mutex_lock(&dance_mutex);
    num_dancing++;
    pthread_mutex_unlock(&dance_mutex);
    
    // TODO:
    // I need a barrier to make sure people enter dancing room together.
    customers[custid].barrier = & dance_barrier;
    //printf("This is line %d, customer name is :%s \n",__LINE__, customers[custid].name);
    barrier_wait(&dance_barrier);
    // I want to know who I am dancing with!
    ////THIS WHOLE FOLLOWING BLOCK IS FOR TESTING
    pthread_mutex_lock(&dance_mutex);
    int i;
    int counter = 0;
    char *friends[max_dancing - 1];
    for (i = 0; i < num_customers; i++)
    {
        if (customers[i].barrier == customers[custid].barrier && i != custid)
        {
            if (counter > max_dancing - 2)
            {
                printf("Wait? Why are you dancing here %s?\n",
                       customers[i].name);
            }
            else
            {
                friends[counter] = customers[i].name;
            }
            counter++;
        }
    }

    if (counter == max_dancing - 1)
    {
        pthread_mutex_lock(&print_mutex);
        int j;
        printf("%s is dancing with %s", customers[custid].name, friends[0]);
        for (j = 1; j < max_dancing - 1; j++)
        {
            printf(" and %s", friends[j]);
        }
        printf(".\n");
        pthread_mutex_unlock(&print_mutex);
    }
    else
    {
        printf("Your synchronization implementation is incorrect.\n");
	printf("Counter is :%d, and Max Dancing is :%d\n",counter,max_dancing);
    }

    if (num_dancing > max_dancing)
    {
        printf("You have too many people on the dance floor\n");
    }
    pthread_mutex_unlock(&dance_mutex);
    ////THIS WHOLE PRECEDING BLOCK IS FOR TESTING

    // TODO:
    // Wait until the people are done dancing, reset the customer's barrier to
    // NULL,
    // decrement num_dancing
    barrier_wait(&dance_barrier);
    customers[custid].barrier=NULL;
    pthread_mutex_lock(&dance_mutex);
    if(num_dancing!=0){
	num_dancing=0;
    }
    pthread_mutex_unlock(&dance_mutex);

    usleep(10);
}

/*
 * This function is run by a thread which is ready to eat!
 */
void declareEating(int custid)
{
    pthread_mutex_lock(&eat_mutex);
    num_eating++;
    pthread_mutex_unlock(&eat_mutex);

    // TODO: Make sure people are seated in groups (i.e. use a barrier)
    customers[custid].barrier = & food_barrier;
    barrier_wait(&food_barrier);
    // I want to print who I am eating with!
    ////THIS WHOLE FOLLOWING BLOCK IS FOR TESTING
    pthread_mutex_lock(&eat_mutex);
    int i;
    int counter = 0;
    char *friends[max_eating - 1];
    for (i = 0; i < num_customers; i++)
    {
        if (customers[i].barrier == customers[custid].barrier && i != custid)
        {
            if (counter > max_eating - 2)
            {
                printf("Wait? Why are you eating here %s?\n",
                       customers[i].name);
            }
            else
            {
                friends[counter] = customers[i].name;
            }
            counter++;
        }
    }

    if (counter == max_eating - 1)
    {
        pthread_mutex_lock(&print_mutex);
        int j;
        printf("%s is eating with %s", customers[custid].name, friends[0]);
        for (j = 1; j < max_eating - 1; j++)
        {
            printf(" and %s", friends[j]);
        }
        printf(".\n");
        pthread_mutex_unlock(&print_mutex);
    }
    else
    {
        printf("Your synchronization implementation is incorrect.\n");
	printf("Counter is :%d, and Max Eating is :%d\n",counter,max_eating);
    }

    if (num_eating > max_eating)
    {
        printf("You have too many people in the restaurant\n");
    }

    pthread_mutex_unlock(&eat_mutex);
    ////THIS WHOLE PRECEDING BLOCK IS FOR TESTING
    barrier_wait(&food_barrier);
    customers[custid].barrier=NULL;
    pthread_mutex_lock(&eat_mutex);
    if(num_eating!=0){
	num_eating=0;
    }
    pthread_mutex_unlock(&eat_mutex);
    // TODO:
    // Wait until both people are done eating, reset the barrier to NULL,
    // decrement num_eating

    usleep(5);
}

/*
 * It's Friday night and these customers want to dance, eat and sleep!
 * These are restrictions which you need to consider.
 * 1. Only one group of people can dance
 * 2. Only one group of people can eat
 * 3. Only people who danced can eat. Thus he or she must dance first!
 * 4. After eating, you will take a short nap before dancing again.
 * 5. You must handle an arbitrary group size for both dancing and eating
 * 6. The curfew begins at midnight, and students must go back to their houses.
 * :(
 */
void *fridayNight(void *customer_info)
{
    customer_t *thisCust = (customer_t *)(customer_info);
    printf("customer name: %s\n", thisCust->name);

    // TODO:Properly enforce the rule about the number of people allowed in a
    // room
    while (timer > 0)
    {
	//printf("This is line %d, customer name is :%s \n",__LINE__,thisCust->name);
        pthread_mutex_lock(&timer_mutex);
        timer--;
        pthread_mutex_unlock(&timer_mutex);

	//printf("This is line %d, customer name is :%s \n",__LINE__,thisCust->name);
	sem_wait(&dance_sem);
	//printf("This is line %d, customer name is :%s \n",__LINE__,thisCust->name);
        declareDancing(thisCust->id); // Time to dance!
	//printf("This is line %d, customer name is :%s \n",__LINE__,thisCust->name);
	sem_post(&dance_sem);
	

	sem_wait(&eat_sem);
        declareEating(thisCust->id); // Time to eat!
	sem_post(&eat_sem);

        // time to take a short nap before dancing!
        usleep(10);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("proper usage: %s \"# of customers\" \"max # of dancers\" \"max # of eaters\"\n", argv[0]);
        return 1;
    }

    num_customers = atoi(argv[1]);
    max_dancing = atoi(argv[2]);
    max_eating = atoi(argv[3]);
    timer = max_eating * max_dancing * 5;

    customers = malloc(sizeof(customer_t) * num_customers);
    customer_t *currCustomer;

    int i;
    num_eating = 0;
    num_dancing = 0;

    // TODO: properly init the barriers and semaphores
    sem_init(&dance_sem,0,max_dancing);
    sem_init(&eat_sem,0,max_eating);
    barrier_init(&dance_barrier,max_dancing);
    barrier_init(&food_barrier,max_eating);

    // for loop for initializing customers' information
    for (i = 0; i < num_customers; i++)
    {
        currCustomer = &(customers[i]);
        currCustomer->name = malloc(2 * sizeof(char));
        currCustomer->id = i;
        (currCustomer->name)[0] = (char)(65 + i);
        (currCustomer->name)[1] = '\0';
        pthread_create(&currCustomer->thread, NULL, fridayNight, currCustomer);
    }

    for (i = 0; i < num_customers; i++)
    {
        currCustomer = &customers[i];
        if (pthread_join(currCustomer->thread, NULL))
        {
            printf("error joining thread for %s\n", currCustomer->name);
            exit(1);
        }
    }

    for (i = 0; i < num_customers; i++)
    {
        free(customers[i].name);
    }

    // TODO:Properly free the semaphores and barriers
    sem_destroy(&dance_sem);
    sem_destroy(&eat_sem);
    barrier_destroy(&dance_barrier);
    barrier_destroy(&food_barrier);

    free(customers);
    return 0;
}

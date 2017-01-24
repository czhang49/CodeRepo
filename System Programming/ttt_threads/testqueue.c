// Original file by Lawrence Angrave 2015
// Modifications by Alec Kochevar-Cureton and Noel Fortman 2015
// Changes to this file will be ignored when your project is graded

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "queue.h"

static pthread_t tid1,tid2,tid3,tid4;

static int ip, ic; // producer consumer counts

static pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

#define OPS (10001)
int integers[OPS];
queue_t queue;


int counter;
void * test1_thread(void* unused) {
	while(counter ++ < 80)  (int*)queue_pull(&queue); 
	return NULL;
}


int test1()
{
	puts("Test 1:");
	// Should be able to put 63 entries without blocking 
	for(int i=1; i < 64; i++)
		queue_push(&queue, & integers[i]);

	// Pull two integers off the quueue
	int* t= (int*)queue_pull(&queue);
	//printf("This is line %d\n",__LINE__);
	assert(t && *t == 1);
	//printf("This is line %d\n",__LINE__);
	t= (int*)queue_pull(&queue);
	//printf("This is line %d\n",__LINE__);
	assert(t && *t == 2);

	// Pull 81 integers using a background queue
	pthread_create(&tid1, NULL, test1_thread,NULL);
	//printf("This is line %d\n",__LINE__);
	sleep(1);
	assert(counter == 62);

	for(int i=65; i < 125; i++)
		queue_push(&queue, & integers[i]);

	pthread_join(tid1, NULL);
	assert(counter == 81);

	t= (int*)queue_pull(&queue);
	assert(t && *t == 84);

	puts("Test 1 passed");
	return 0;
}

void* test2_consume(void*unused)
{
	sleep(1); // Let producer get ahead

	for(ic=1; ic < 3000; ic++)
	{
		int* t= (int*)queue_pull(&queue);
		assert(t && *t == ic);

		pthread_mutex_lock(&m);
		if(ip == 2000 && ic>=2000) pthread_cond_signal(&cv);
		pthread_mutex_unlock(&m);

	}
	return NULL;
}

void* test2_produce(void*unused) {
	for(ip = 1; ip < 3000; ip++) {
		queue_push(&queue, & integers[ip]);  

		pthread_mutex_lock(&m);
		while(ip == 2000 && ic < 2000) 
			pthread_cond_wait(&cv, &m);  // Let consumer catch up
			pthread_mutex_unlock(&m);
		}
	return NULL;
}


// ---- TEST 3
int test2() {
	puts("Test 2:");
	pthread_create(&tid1,0, test2_produce, NULL);
	pthread_create(&tid2,0, test2_consume, NULL);
	puts("Test 2, waiting on producer...");
	pthread_join(tid1,NULL);
	puts("Test 2, waiting on consumer...");
	pthread_join(tid2,NULL);
	puts("Test 2 passed");
	return 0;
	}

// ---- TEST 3
int test3() {
	puts("Test 3:");
	puts("Test 3, puting 64 integers...");
	for(ip=1; ip < 64; ip++)
		queue_push(&queue, & integers[ip]);
	puts("Test 3, dequeing 64 integers...");
	for(ic=1; ic < 64; ic++)
	{
		int* t = (int*)queue_pull(&queue);
		assert(t && *t == ic);
	}
	puts("Test 3, puting 'poison-pill' NULL task");
	queue_push(&queue, NULL);
	puts("Test 3, geting NULL task (should never block)");
	int* temp;
	for(int i = 0; i < OPS;i++) 
	{
		temp = (int*)queue_pull(&queue);
		assert( temp == NULL);
		queue_push(&queue, NULL);
	}
	puts("Test 3 passed");
return 0;
}

// ---- TEST 4

int producer_running = 2;

long sum;
int producer_started;
int* prod_integers[2];

void * test4_produce(void* thread_num) {
	puts("Producer starting");
	producer_started++;
	int num = *((int*)thread_num);
	prod_integers[num] = malloc(sizeof(int) * OPS);
	memcpy(prod_integers[num], integers, sizeof(int)*OPS);

	for(int i=1; i < OPS; i++)
		queue_push(&queue,& prod_integers[num][i] );

	pthread_mutex_lock(&m);
	producer_running --;
	// Am I the last consumer thread to finish? If so signal the other waiting threads
	if(producer_running ==0)
	{
		queue_push(&queue, NULL); // send the terminator_task
		pthread_cond_broadcast(&cv);
	}
	else 
	while(producer_running)  // I'm not the last, so keep waiting
	pthread_cond_wait(&cv, &m);
	pthread_mutex_unlock(&m);
	puts("Test 4, producer quiting");
	return NULL;
}
int total_consume_count;

void * test4_consume() 
{
	int value;
	int count = 0;

	while (!producer_started);  // Lets producers get ahead

	int* t;
	while((t = (int*)queue_pull(&queue)))
	{
		pthread_mutex_lock(&m);
		value = *t;
		sum += value;
		pthread_mutex_unlock(&m);
		if( ++ count > 20001)
		{
			fprintf(stderr,"Consumer Got too many values\n"); 
			exit(1); 
		}
	}
	queue_push(&queue, NULL);
	printf("Test 4, consumer got %d values\n",  count);
	pthread_mutex_lock(&m);
	total_consume_count += count;

	pthread_mutex_unlock(&m);
	puts("Test 4, consumer: NULL value-> quitting");
	return NULL;
}



int test4()
{
	puts("Test 4:");
	int p0 = 0;
	int p1 = 1;
	int err = pthread_create(&tid1,0, test4_produce, &p0);
	int err2 = pthread_create(&tid2,0, test4_produce, &p1);
	int err3 = pthread_create(&tid3,0, test4_consume, NULL);
	int err4 = pthread_create(&tid4,0, test4_consume, NULL);
	if(err || err2 || err3 || err4) printf("BIG UHOH\n");
	puts("Test 4, waiting on producer 1...");
	pthread_join(tid1,NULL);
	puts("Test 4, waiting on producer 2...");
	pthread_join(tid2,NULL);
	puts("Test 4, waiting on consumer 1...");
	pthread_join(tid3,NULL);
	puts("Test 4, waiting on consumer 2...");
	pthread_join(tid4,NULL);
	printf("Test 4, total consumed  %d values\n", total_consume_count );
	printf("Test 4, total sum %ld values\n", sum );
	free(prod_integers[0]);
	free(prod_integers[1]);

	// Sum of integers = N (N+1) / 2 
	// (and we have every integer 1..10000 twice)
	assert(sum == 100010000L);
	puts("Test 4 passed");
	return 0;
}

int test5()
{
	int i;
	int* value;
	//printf("This is line %d\n",__LINE__);
	for(i = 0; i < 10; i++)
	{
		queue_push(&queue, &integers[i]);
	}
	//printf("This is line %d\n",__LINE__);
	for(i = 0; i < 5; i++)
	{
		(int*)queue_pull(&queue);
	}
	//printf("This is line %d\n",__LINE__);
	queue_destroy(&queue);
	//printf("This is line %d\n",__LINE__);
	//printf("This is line %d\n",__LINE__);
	return 0;
}


int main(int argc, char** argv) {
	for( int i=0; i < OPS;i++)
		integers[i] = i;
	//printf("This is line %d\n",__LINE__);
	queue_init(&queue, 64);
	//printf("This is line %d\n",__LINE__);

	alarm(4);
	//printf("This is line %d\n",__LINE__);

	int doTest = argv[1] ? atoi( argv[1]) : 0;
	//printf("This is line %d\n",__LINE__);
	if(doTest==1) { exit( test1()); }
	//printf("This is line %d\n",__LINE__);
	if(doTest==2) { exit( test2()); }
	//printf("This is line %d\n",__LINE__);
	if(doTest==3) { exit( test3()); }
	if(doTest==4) { exit( test4()); }
	//printf("This is line %d\n",__LINE__);
	if(doTest==5) { exit( test5()); }
	printf("This is line %d\n",__LINE__);
	printf("Usage: %s 1|2|3|4|5\n", argv[0]);
	printf("This is line %d\n",__LINE__);
	exit(1);
}

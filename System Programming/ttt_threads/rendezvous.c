#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "semamore.h"

char* quote_A;
char* quote_B;

// Create a Mutex!

// Create some Semaphores!
//sem_t sem_A, sem_B
Semamore* semmA;
Semamore* semmB;

void* modifyB_printA();
void* modifyA_printB();

int main (int argc, char** argv)
{
	// Initialize your semaphores
//	sem_init(&sem_A,0,0); // Initialize to 0 is smart, because you know about the flow of the program, so make use of it. 
//	sem_init(&sem_B,0,0);

	semmA = malloc(sizeof(Semamore));
	semmB = malloc(sizeof(Semamore));

	semm_init(semmA, 0, 1);
	semm_init(semmB, 0, 1);

	quote_A = strdup("J!epo(u!lopx!ipx!nboz!pg!zpv!ibwf!fwfs!nfu!Ejkltusb-!cvu!zpv!qspcbcmz!lopx!uibu!bssphbodf!jo!dpnqvufs!tdjfodf!jt!nfbtvsfe!jo!obop.Ejkltusbt/!.!Bmbo!Lbz");
	quote_B = strdup("Uif!rvftujpo!pg!xifuifs!dpnqvufst!dbo!uijol!jt!mjlf!uif!rvftujpo!pg!xifuifs!tvcnbsjoft!dbo!txjn/ぞ!.!Fethfs!X/!Ejkltusb");
	
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, modifyA_printB, NULL);
	pthread_create(&tid2, NULL, modifyB_printA, NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	free(quote_B);
	free(quote_A);

	return 0;
}

void* modifyA_printB (void)
{
	int i = 0;

	while (quote_A[i])
	{
		usleep(rand() &15); // randomized slowdowns
		quote_A[i++] --;
	}
//	sem_post(&sem_A);
	semm_post(semmA);	
	semm_wait(semmB);
//	sem_wait(&sem_B);
	printf("quote_B:\t%s\n", quote_B);
//	sem_post(&sem_B);
	semm_post(semmB);

	return NULL;
}

void* modifyB_printA ()
{
	int i = 0;

	while (quote_B[i])
	{
		usleep(rand() &100); // randomized slowdowns
		quote_B[i++] --;
	}
//	sem_post(&sem_B);
	semm_post(semmB);
//	sem_wait(&sem_A);
	semm_wait(semmA);
	printf("quote_A:\t%s\n", quote_A);
//	sem_post(&sem_A);

	semm_post(semmA);
	return NULL;
}

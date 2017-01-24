// Overworked Interns
// CS 241 Fall 2015

#define _GNU_SOURCE
#include "company.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Your good solution needs to go here
void *work_interns(void *company) {

	pthread_mutex_t *left, *right;
	CompanyData* p = (CompanyData*) company;
	int left_stat, right_stat;
	int wait_multiplier = 1;
	int try_counter;
	while(running){
		printf("Company %d needs their interns!\n", p->number);
		left = p->intern_left;
		right = p->intern_right;

		do{
			try_counter=2;
			left_stat=pthread_mutex_trylock(left);
			while (left_stat){
				usleep(wait_multiplier*(rand()%10));
				left_stat = pthread_mutex_trylock(left);
				try_counter --;
				if (!try_counter && left_stat){
					pthread_mutex_t *temp;
					temp=left;
					left=right;
					right=temp;
					usleep(wait_multiplier*(rand()%10));
					break;
				}
			}
			if (left_stat){
				continue;
			}
			
			try_counter=2;
			right_stat=pthread_mutex_trylock(right);
			while (right_stat){
				usleep(wait_multiplier*(rand()%10));
				right_stat = pthread_mutex_trylock(right);
				try_counter --;
				if (!try_counter && right_stat){
					pthread_mutex_unlock(left);
					pthread_mutex_t *temp;
					temp=left;
					left=right;
					right=temp;
					usleep(wait_multiplier*(rand()%10));
					break;
				}
			}
			//printf("Thins are moving\n");
		} while (left_stat || right_stat);

		printf("Company %d is working\n", p->number);
		usleep(1 + rand() % 3);
		
		p->hire_count +=1;
		pthread_mutex_unlock(left);
		pthread_mutex_unlock(right);
		printf("Company %d has finished working with us\n", p->number);
	}

	return NULL;
}

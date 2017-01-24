#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"


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

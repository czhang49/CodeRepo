// Parmake
// CS 241 Fall 2015
// University of Illinois at Urbana-Champaign
#ifndef __QUEUE_H__
#define __QUEUE_H__

/**
 * Queue Data Structure
 */
typedef struct {
  struct queue_node *head; ///<Head of linked-list
  struct queue_node *tail; ///<Tail of linked-list
  unsigned int size;       ///<Number of nodes in linked-list
} queue_t;

void queue_init(queue_t *q);
void queue_destroy(queue_t *q);

void *queue_dequeue(queue_t *q);
void *queue_at(queue_t *q, int pos);
void *queue_remove_at(queue_t *q, int pos);
void queue_enqueue(queue_t *q, void *item);
unsigned int queue_size(queue_t *q);

void queue_iterate(queue_t *q, void (*iter_func)(void *, void *), void *arg);

#endif

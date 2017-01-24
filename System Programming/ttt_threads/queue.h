// Changes to this file will be ignored when your project is graded

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
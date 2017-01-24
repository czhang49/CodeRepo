#include "queue.h"

void queue_init(queue_t* queue) {
	queue->head_ = NULL;
	queue->size_ = 0;
}

void queue_destroy(queue_t* queue, int free_data) {
	queue_entry_t* entry = queue->head_;
	while (entry != NULL) {
		queue_entry_t* temp = entry->next_;
		if (free_data)
			free(entry->stamped_entry_.data_);

		free(entry);
		entry = temp;
	}
}

void queue_insert(queue_t* queue, unsigned long timestamp, void* data) {
	queue_entry_t* entry = malloc(sizeof(*entry));
	entry->stamped_entry_.data_ = data;
	entry->stamped_entry_.timestamp_ = timestamp;
	entry->next_ = queue->head_;
	queue->head_ = entry;

	queue->size_ ++;
}

int compare_timestamp(const void* v1, const void* v2) {
	return ((timestamp_entry*)v1)->timestamp_ < ((timestamp_entry*)v2)->timestamp_;
}

timestamp_entry* queue_gather(queue_t* queue, unsigned long start, unsigned long end, int (*selector)(void*),
				 			 int* return_size) {
	if (return_size == NULL || selector == NULL) return NULL;
	
	(*return_size) = 0;
	timestamp_entry* ret = malloc(sizeof(*ret));
	queue_entry_t* entry = queue->head_;
	while (entry != NULL) {
		if (entry->stamped_entry_.timestamp_ >= start && entry->stamped_entry_.timestamp_ < end &&
			selector(entry->stamped_entry_.data_) != 0) {
			ret[*return_size] = entry->stamped_entry_;
			(*return_size) ++;

			ret = realloc(ret, ((*return_size) + 1) * sizeof(*ret));
		}
		entry = entry->next_;
	}

	qsort(ret, *return_size, sizeof(timestamp_entry), compare_timestamp);
	return ret;
}

int queue_at(queue_t* queue, int entry_index, timestamp_entry* result) {
	if (entry_index >= queue->size_) return 0;

	size_t i;
	queue_entry_t* entry = queue->head_;
	for (i = 0;i < entry_index;i ++)
		entry = entry->next_;

	(*result) = entry->stamped_entry_;
	return 1;
}

int queue_size(queue_t* queue) {
	return queue->size_;
}

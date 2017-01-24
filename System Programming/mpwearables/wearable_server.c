#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#include <pthread.h>

#include "queue.h"

const char* TYPE1 = "heart_beat";
const char* TYPE2 = "blood_sugar";
const char* TYPE3 = "body_temp";

// The wearable server socket, which all wearables connect to.
int wearable_server_fd;

// A lock for your queue.
pthread_mutex_t queue_lock_;
// A queue for all received data.
queue_t receieved_data_;

typedef struct SampleData {

	char type_[50];
	int data_;

} SampleData;

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

/**
    Used to write out the statistics of a given results set (of timestamp_entry's).
    To generate the result set see queue_gather(). fd is the file descriptor to
    which the information is sent out. The type is the type of data that is written out
    (TYPE1, TYPE2, TYPE3). results is the array of timestamp_entrys, and size is 
    the size of that array. NOTE: that you should call method for every type 
    (TYPE1, TYPE2, TYPE3), and then write out the infomration "\r\n" to signify that
    you have finished sending out the results.
*/
void write_results(int fd, const char* type, timestamp_entry* results, int size) {
    long avg = 0;
    int i;

    char buffer[1024];
    int temp_array[size];
    sprintf(buffer, "Results for %s:\n", type);
    sprintf(buffer + strlen(buffer), "Size:%i\n", size);
    for (i = 0;i < size;i ++) {
        temp_array[i] = ((SampleData*)(results[i].data_))->data_;
        avg += ((SampleData*)(results[i].data_))->data_;
    }

    qsort(temp_array, size, sizeof(int), compare);

    if (size != 0) {
    	sprintf(buffer + strlen(buffer), "Median:%i\n", (size % 2 == 0) ?
            (temp_array[size / 2] + temp_array[size / 2 - 1]) / 2 : temp_array[size / 2]);
	} else { 
		sprintf(buffer + strlen(buffer), "Median:0\n");
	}

    sprintf(buffer + strlen(buffer), "Average:%li\n\n", (size == 0 ? 0 : avg / size));
    write(fd, buffer, strlen(buffer));
}

/**
    Given an input line in the form <timestamp>:<value>:<type>, this method 
    parses the infomration from the string, into the given timestamp, and
    mallocs space for SampleData, and stores the type and value within
*/
void extract_key(char* line, long* timestamp, SampleData** ret) {
	*ret = malloc(sizeof(SampleData));
	sscanf(line, "%zu:%i:%[^:]%:\\.*", timestamp, &((*ret)->data_), (*ret)->type_);
}

void* wearable_processor_thread(void* args) {
	int socketfd = *((int*)args);

	//Use a buffer of length 64!
	//TODO read data from the socket until -1 is returned by read
	
	//char buffer[64]
	//while (recev(socketfd, buffer, 64) > 0) ...


	close(socketfd);
	return NULL;
}

void* user_request_thread(void* args) {
	int socketfd = *((int*)args);
	int i, ret;

	//TODO read data from the socket until -1 is returned by read
	//Requests will be in the form
	//<timestamp1>:<timestamp2>, then write out statistics for data between
	//those timestamp ranges

	close(socketfd);
	return NULL;
}

//IMPLEMENT!
//given a string with the port value, set up a 
//serversocket file descriptor and return it
int open_server_socket(const char* port) {
	//TODO

	return 0;
}

void signal_received(int sig) {
	//TODO close server socket, free anything you don't free in main
}

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		printf("Invalid input size\n");
		exit(EXIT_FAILURE);
	}

	//TODO setup sig handler for SIGINT
	
	int request_server_fd = open_server_socket(argv[2]);
	wearable_server_fd = open_server_socket(argv[1]);

	pthread_t request_thread;
	int request_socket = accept(request_server_fd, NULL, NULL);
	pthread_create(&request_thread, NULL, user_request_thread, &request_socket);
	close(request_server_fd);

	queue_init(&receieved_data_);
	pthread_mutex_init(&queue_lock_, NULL);

	//TODO accept continous requests



	//TODO join all threads we spawned from the wearables

	pthread_join(request_thread, NULL);
	queue_destroy(&receieved_data_, 1);

	return 0;
}

#include "queue.h"

//Types of messages
extern const char* TYPE1;
extern const char* TYPE2;
extern const char* TYPE3;

//The port we will connect on
extern const char* wearable_gPort_;

//Holds a data type, and value
typedef struct SampleData {

	char* type_;
	int data_;

} SampleData;

//Holds the information for a wearable
typedef struct Wearable {
    //start offset (in millis) that this wearable will start to broadcast
	useconds_t start_sleep_;
    //the time (in millis) between transmittions
	useconds_t sample_interval_;

    //the total amount of data points
	int data_size_;
    //the data
	SampleData* data_;

    queue_t queued_results_;
	
} Wearable;


/*
Loads all wearables from a file.
Format is for a wearable is

BEGIN
START:<time until start (in millis)>
INTERVAL:<time between intervals (in millis)>
<type>:<transmit_variables>
...
END

*/
Wearable** get_wearables(const char* file_name,
                                int* wearable_count,
                                int** sample_times, 
                                int* sample_count,
                                int* latest_launch);

void free_wearable(Wearable* wearable);

void* wearable_thread(void* param);


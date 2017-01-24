#include "cracker1.h"

int start(int thread_count) {

	// parse the command line input string first
	FILE* inf = stdin;
	char username[9],hash[14], password_prefix[9]; 	

	// create and start threadpool.
	// the pool_ptr is not set as global variable, but as a local variable and will be passed to the worker threads via the pthread_create. 
	thread_pool *pool_ptr = thpl_create(thread_count);
	thpl_start(pool_ptr);
	// create the task queue  
	//printf("I'm at cracker1.c line %d\n",__LINE__);
	size_t buf_len=0;
	char* line=NULL;
	while (getline(&line, &buf_len, inf) != -1) {
    		
		sscanf(line, "%8s %13s %8s", username, hash, password_prefix);

		task_node* tasknd = (task_node*) malloc(sizeof(task_node)); // 
		strcpy(tasknd->username,username);
		strcpy(tasknd->hash,hash);
		strcpy(tasknd->password_prefix,password_prefix);
		//printf("username:%s, hash:%s, password_prefix:%s\n",tasknd->username,tasknd->hash,tasknd->password_prefix);
	
		queue_push(pool_ptr->task_queue,(void*) tasknd);
	} 
	
	//printf("I'm at cracker1.c line %d\n",__LINE__);
	
	task_node* tasknd = (task_node*) malloc(sizeof(task_node)); // this tasknd is malloced, and free-ed in the crack password function
	tasknd->username[0]='\0';
	tasknd->hash[0]='\0';
	tasknd->password_prefix[0]='\0';
	queue_push(pool_ptr->task_queue,(void*) tasknd);
	
	//printf("I'm at cracker1.c line %d\n",__LINE__);
	// wait for the threadpool to finish
	for (int i=0 ; i < pool_ptr->thread_count; i++){
	
		pthread_join(pool_ptr->worker_threads[i],NULL);
	}
	printf("%d passwords recovered, %d failed\n",pool_ptr->success_crack,pool_ptr->fail_crack);
	//printf("I'm at cracker1.c line %d\n",__LINE__);
	// This is to free the EOF node, since this node is not free-ed anywhere
	free(tasknd);
	// This is to free the buffer used in getline
	free(line);
	
	thpl_destroy(pool_ptr);
	return 0;
}

void* thpl_thread(void* pool){

	int thread_number;
	// taskpl is just a casted pool pointer;
	thread_pool* taskpl = (thread_pool*) pool ; 
	pthread_t mythread = pthread_self();

	pthread_mutex_lock(&(taskpl->lock));
	for (int i=0; i < taskpl->thread_count; i++){
		if (mythread == taskpl->worker_threads[i])
			thread_number = i+1;
	}
	pthread_mutex_unlock(&(taskpl->lock));
	//printf("I'm at cracker1.c line %d, New Thread Number %lu Started \n",__LINE__, mythread);
	pthread_mutex_lock(&(taskpl->lock));
	while(!(taskpl->ifquit)){
		pthread_mutex_unlock(&(taskpl->lock));

		task_node* tasknd = (task_node*) queue_pull (taskpl->task_queue);
		//printf("I'm at cracker1.c line %d \n",__LINE__);
		if (strlen(tasknd->username) == 0){
			pthread_mutex_lock(&(taskpl->lock));
			taskpl->ifquit=1;
			pthread_mutex_unlock(&(taskpl->lock));
			//printf("I'm at cracker1.c line %d \n",__LINE__);
			queue_push(taskpl->task_queue,tasknd);
			pthread_exit(0);
		}
		bool succ_crack = crack_password(tasknd,thread_number);
		if (succ_crack){
			pthread_mutex_lock(&(taskpl->lock));
			taskpl->success_crack++;
			pthread_mutex_unlock(&(taskpl->lock));
		} else{
			pthread_mutex_lock(&(taskpl->lock));
			taskpl->fail_crack++;
			pthread_mutex_unlock(&(taskpl->lock));
		}
		//printf("I'm at cracker1.c line %d \n",__LINE__);
		pthread_mutex_lock(&(taskpl->lock));
	}
	pthread_mutex_unlock(&(taskpl->lock));	

	pthread_exit(0);
}

bool crack_password (task_node* tasknd, int thread_number){

	char username[9], hash[13], password_prefix[9];
	strcpy(username,tasknd->username);
	strcpy(hash,tasknd->hash);
	strcpy(password_prefix,tasknd->password_prefix);
	//printf("username:%s, hash:%s, password_prefix:%s\n",username,hash,password_prefix);
	//printf("I'm at cracker1.c line %d \n",__LINE__);
	printf("Thread %d: Start %s\n",thread_number,username);
	free(tasknd);
	return crackPassword(username,hash,password_prefix, thread_number);
	//printf("I'm at cracker1.c line %d \n",__LINE__);
	
}




thread_pool* thpl_create(int thread_count){

	thread_pool* pool = (thread_pool*) malloc(sizeof (thread_pool)); 

	pthread_mutex_init(&(pool->lock),NULL);
	pool->ifquit = false;
	pool->taskqueue_maxsize=100;
	pool->thread_count = thread_count;
	pool->success_crack=0;
	pool->fail_crack=0;	
	
	pool->task_queue = (queue_t*) malloc(sizeof(queue_t));
	queue_init(pool->task_queue,pool->taskqueue_maxsize);
	
	pool->worker_threads = (pthread_t*) malloc(sizeof(pthread_t)*thread_count);
	
	return pool;
}

void thpl_destroy(thread_pool* pool){

	pthread_mutex_destroy(&(pool->lock));
	
	queue_destroy(pool->task_queue);
	
	free(pool->task_queue);
	free(pool->worker_threads);
	
	free(pool);
}

void thpl_start(thread_pool* pool){

	// the function to put to each thread is the same. But the actual function that runs can be grabbed from the task queue structure, so this thpl_thread function is just an opening . 
	int returnvalue;
	for (int i = 0 ; i < pool->thread_count; i++){
		returnvalue=pthread_create(&(pool->worker_threads[i]),NULL,thpl_thread,(void*) pool); // cast any pointer into void*	
		if (returnvalue){
			perror("Something happens in the pthread_create: ");
		}	
	}

}

//////////////// This function is taken from the cracker0.c to crack password

bool crackPassword(const char *username, const char *target_hash,
                   const char *partial_pw, int thread_number) {

  assert(strlen(username) <= 8);
  assert(strlen(target_hash) == 13);
  assert(strlen(partial_pw) <= 8);

  double start_time = getTime();

  char test_pw[9];
  strcpy(test_pw, partial_pw);

  // unknown_chars will point to the part of the password that is unknown
  char *unknown_chars = test_pw + getPrefixLength(test_pw);
  setStringPosition(unknown_chars, 0);

  int found = 0;
  int hash_count = 0;
  struct crypt_data cdata;
  cdata.initialized = 0;

  do {
    const char *hashed = crypt_r(test_pw, "xx", &cdata);

    // uncomment this if you want to see the hash function doing its thing
    // printf("%s -> %s\n", test_pw, hashed);

    hash_count++;
    found = !strcmp(hashed, target_hash);
  } while (!found && incrementString(unknown_chars));

  double elapsed = getTime() - start_time;

  if (found) {
    printf("Thread %d: Password for %s is %s (%d hashes in %.2f seconds)\n", thread_number,username,
           test_pw, hash_count, elapsed);
	return true;
  } else {
    printf("Thread %d: Password for %s not found (%d hashes in %.2f seconds)\n", thread_number,username,
           hash_count, elapsed);
	return false;
  }
}

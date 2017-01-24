#include "cracker2.h"


int start(int thread_count) {

	// parse the command line input string first
	FILE* inf = stdin;
	char username[9],hash[14], password_prefix[9]; 	

	// create and start threadpool.
	// the pool_ptr is not set as global variable, but as a local variable and will be passed to the worker threads via the pthread_create. 
	thread_pool *pool_ptr = thpl_create(thread_count);

	thpl_start(pool_ptr);
	// create the task queue  

	size_t buf_len=0;
	char* line=NULL;
	while (getline(&line, &buf_len, inf) != -1) {
    		sscanf(line, "%8s %13s %8s", username, hash, password_prefix);
		thpl_create_parjobs(username, hash, password_prefix,pool_ptr);

		pool_ptr->iffound=false;
		pool_ptr->num_hash=0;
		pool_ptr->password[0]='\0';
		printf("Start %s\n",username);

		// the uneven barrier wait is good. make sure one is waiting and one is executing. 
		double start_time = getTime();
  		double start_cpu_time = getCPUTime();
		barrier_wait(pool_ptr->task_bar);
		barrier_wait(pool_ptr->task_bar);		
		double elapsed = getTime() - start_time;
 		double total_cpu_time = getCPUTime() - start_cpu_time;

		if(pool_ptr->iffound){
			 printf("Password for %s is %s (%d hashes in %.2f seconds)\n",username, pool_ptr->password, pool_ptr->num_hash, elapsed);
  			 printf("Total CPU time: %.2f seconds.\n", total_cpu_time);
  			 printf("CPU usage: %.2fx\n", total_cpu_time / elapsed);
			
		} else{
			 printf("Password for %s is not found (%d hashes in %.2f seconds)\n",username, pool_ptr->num_hash, elapsed);
  			 printf("Total CPU time: %.2f seconds.\n", total_cpu_time);
  			 printf("CPU usage: %.2fx\n", total_cpu_time / elapsed);	
		}
	} 
	pool_ptr->ifquit=true;
	// this wait is critical , otherwise the others waiting will not wake up.
	barrier_wait(pool_ptr->task_bar);

	for (int i=0 ; i < pool_ptr->thread_count; i++){
		pthread_join(pool_ptr->worker_threads[i],NULL);
	}

	free(line);
	thpl_destroy(pool_ptr);
	return 0;
}

thread_pool* thpl_create(int thread_count){

	thread_pool* pool = (thread_pool*) malloc(sizeof (thread_pool)); 

	pthread_mutex_init(&(pool->lock),NULL);
	pool->task_queue = (task_node*) malloc(sizeof(task_node)*thread_count);
	pool->task_bar = (barrier_t*) malloc(sizeof(barrier_t));
	pool->word_info = (task_hash*) malloc(sizeof(task_hash));
	pool->worker_threads = (pthread_t*) malloc(sizeof(pthread_t)*thread_count);

	barrier_init(pool->task_bar,thread_count+1); // the extra 1 is the main thread

	pool->ifquit = false;
	pool->thread_count = thread_count;
	pool->num_hash=0;

	pool->password[0]='\0';	
	
	return pool;
}


void thpl_destroy(thread_pool* pool){

	pthread_mutex_destroy(&(pool->lock));	
	barrier_destroy(pool->task_bar);
	
	free(pool->task_queue);
	free(pool->worker_threads);
	free(pool->word_info);
	free(pool->task_bar);
	
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



void* thpl_thread(void* pool){

	int thread_number;
	thread_pool* taskpl = (thread_pool*) pool ; 

	pthread_t mythread = pthread_self();
	pthread_mutex_lock(&(taskpl->lock));
	for (int i=0; i < taskpl->thread_count; i++){
		if (mythread == taskpl->worker_threads[i])
			thread_number = i+1;
	}
	pthread_mutex_unlock(&(taskpl->lock));

	barrier_wait(taskpl->task_bar);

	task_node* tasknd_ptr = NULL;
	pthread_mutex_lock(&(taskpl->lock));
	while(!taskpl->ifquit){
		pthread_mutex_unlock(&(taskpl->lock));
 
		tasknd_ptr = &(taskpl->task_queue[thread_number-1]);
		crackPassword(taskpl->word_info->username,taskpl->word_info->hash,taskpl->word_info->password_prefix,thread_number,tasknd_ptr, (void*) taskpl);

		barrier_wait(taskpl->task_bar);
		barrier_wait(taskpl->task_bar);
		pthread_mutex_lock(&(taskpl->lock));
	}
	pthread_mutex_unlock(&(taskpl->lock));

	pthread_exit(0);
}

void thpl_create_parjobs(const char* username, const char* hash, const char* password_prefix, thread_pool* pool_ptr){

	strcpy(pool_ptr->word_info->username, username);
	strcpy(pool_ptr->word_info->hash, hash);
	strcpy(pool_ptr->word_info->password_prefix, password_prefix);

	int prefix_length = getPrefixLength(password_prefix);
	int length_unknown = strlen(password_prefix)-prefix_length;
	int total_loop=1;
	for (int i=0; i<length_unknown ; i++)
		total_loop = total_loop*26;

	int each_index = total_loop/(pool_ptr->thread_count);
	
	int j=0;
	for (; j<pool_ptr->thread_count-1;j++){
		pool_ptr->task_queue[j].start_num = j*each_index;
		pool_ptr->task_queue[j].num_iter = each_index;
	}

	pool_ptr->task_queue[j].start_num = j*each_index;
	pool_ptr->task_queue[j].num_iter = total_loop - j*each_index;
	
}

////////////////////////////////////////////////////////////////

void crackPassword(const char *username, const char *target_hash,
                   const char *partial_pw, int thread_number, task_node* tasknd_ptr, void* pool) {

  assert(strlen(username) <= 8);
  assert(strlen(target_hash) == 13);
  assert(strlen(partial_pw) <= 8);

  char test_pw[9];
  strcpy(test_pw, partial_pw);

  thread_pool* taskpl = (thread_pool*) pool;
  // unknown_chars will point to the part of the password that is unknown
  char *unknown_chars = test_pw + getPrefixLength(test_pw);
  setStringPosition(unknown_chars, tasknd_ptr->start_num);
  printf("Thread %d: Start  %s at %d (%s) \n", thread_number,username, tasknd_ptr->start_num,test_pw);
  int found = 0;
  int hash_count = 0;
  struct crypt_data cdata;
  cdata.initialized = 0;

  do {
	pthread_mutex_lock(&(taskpl->lock));
	if (taskpl->iffound){
		pthread_mutex_unlock(&(taskpl->lock));
		break;
  	}
	pthread_mutex_unlock(&(taskpl->lock));
    const char *hashed = crypt_r(test_pw, "xx", &cdata);

    // uncomment this if you want to see the hash function doing its thing
    // printf("%s -> %s\n", test_pw, hashed);

    hash_count++;
    found = !strcmp(hashed, target_hash);
    incrementString(unknown_chars);
  } while (!found && hash_count<tasknd_ptr->num_iter);

  pthread_mutex_lock(&(taskpl->lock));
  taskpl->num_hash += hash_count;
  pthread_mutex_unlock(&(taskpl->lock));

  if (found){
	pthread_mutex_lock(&(taskpl->lock));
	taskpl->iffound=true;
	strcpy(taskpl->password,test_pw);
	pthread_mutex_unlock(&(taskpl->lock));

	printf("Thread %d: Stop after %d iterations (found)\n", thread_number, hash_count);
  }else{
	pthread_mutex_lock(&(taskpl->lock));
	if(taskpl->iffound==true){
		pthread_mutex_unlock(&(taskpl->lock));
		printf("Thread %d: Stop after %d iterations (cancelled)\n", thread_number, hash_count);
	}else{
		pthread_mutex_unlock(&(taskpl->lock));
		printf("Thread %d: Stop after %d iterations (end)\n", thread_number, hash_count);
	}
  }

  
}

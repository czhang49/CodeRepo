// Parmake
// CS 241 Fall 2015
// University of Illinois at Urbana-Champaign
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include "parser.h"
#include "rule.h"
#include "queue.h"
/**
 * Entry point to parmake.
 */

typedef struct rules_satisfy{

	char* target;
	bool satisfy;
} rules_satisfy;

typedef struct thread_pool {
	queue_t* rules_queue;
	queue_t* satisfy_queue;
	pthread_mutex_t mt;
	pthread_cond_t cv;
	pthread_t* threads;
	int num_threads;
	bool goto_sleep;
	bool ifquit;
	int finished_num;
	int num_rules;
} thread_pool;

thread_pool* pool;

void rules_satisfy_init(rules_satisfy* satisfy_node);
void abort();
rules_satisfy* satisfy_node(char* target);
void notify_target(char* target);
void notify_dep(char* target, char* dep);
void notify_cmd(char* target, char* cmd);
void show_full_parse ();
void destroy_rule_node(rule_t* rule_node);
void destroy_everything();
bool work_on_rules(rule_t* rule_node);
void pool_init(thread_pool* pool, int num_thread);
void* thread_function (void* params);


int main(int argc, char **argv) { 

	extern char *optarg;
        extern int optind;
	int getopt_return;

	char makefile_name[64];
	makefile_name[0]='\0';
	int num_threads=1;
	num_threads = num_threads;
	bool whether_filename = false;
	
	while( (getopt_return = getopt(argc,argv,"f:j:")) != -1){

		//printf("The argument is %c, and command is %s, next variable is %s\n",getopt_return, optarg,argv[optind]);
		switch (getopt_return) {
			case 'f':
				strcpy(makefile_name,optarg);
				whether_filename=true;
				break;
			case 'j':
				num_threads=atoi(optarg);
				break;
			default:
				abort();
		}
	}

	if(!whether_filename){
		if(access("./Makefile",F_OK) == 0){
			strcpy(makefile_name,"Makefile");
			whether_filename=true;
		} else if(access("./makefile",F_OK)==0){
			strcpy(makefile_name,"makefile");
			whether_filename=true;
		} else {
			abort();
		}
	}
	char ** targets = (char**) malloc(sizeof(char*)*(argc-optind+1));
	int i=0;
	for (; i<argc-optind;i++){
		targets[i] = (char*) malloc(sizeof(char)*64);
		strcpy(targets[i], argv[optind+i]);
	}
	targets[i] = NULL;

 	pool = (thread_pool*) malloc (sizeof(thread_pool));
	pool_init(pool, num_threads);

	parser_parse_makefile(makefile_name,targets,notify_target,notify_dep,notify_cmd);
	pool->num_rules = queue_size(pool->rules_queue);

	notify_target("endofoneloop"); // put the end of one searching loop into the queue
	
	/*
	while(queue_size(pool->rules_queue)!=0){
		for (int i=0; i<queue_size(pool->rules_queue);i++){
			if(work_on_rules((rule_t*)queue_at(pool->rules_queue,i))){
				rule_t* removed_rule = queue_remove_at(pool->rules_queue,i);
				destroy_rule_node(removed_rule);
			}

		}
	}
	*/
	
	for (int i=0; i < num_threads; i++){

		pthread_create(&(pool->threads[i]),NULL,thread_function,NULL);
	}
	//show_full_parse();
	
//printf("I'm at line %d \n",__LINE__);
	for (int i=0; i < num_threads; i++){

		pthread_join(pool->threads[i],NULL);
	}
	
	for (int i=0; i<argc-optind;i++){
		free(targets[i]);
	}
	free(targets);
	destroy_everything();
	free(pool);
	return 0; 
}



void rules_satisfy_init(rules_satisfy* satisfy_node){

	satisfy_node->target = NULL;
	satisfy_node->satisfy = false;
}


void abort(){

	printf("You fucking dumbass the input is of wrong format. \n");
	exit(1);
}


rules_satisfy* satisfy_node(char* target){

	rules_satisfy *satisfy_node=NULL;
	// walk down the rules queue and find the corresponding target rules_t node. push the dep to the rules_t node of the target. 
	for (int i=0; i<queue_size(pool->satisfy_queue);i++){
		
		satisfy_node=queue_at(pool->satisfy_queue,i);
		if(!strcmp(satisfy_node->target,target)){
			break;
		}
	}

	if (satisfy_node==NULL){
		perror("Did not find target when looing for satisfy node\n");
		exit(1);
	}
	
	return satisfy_node;
}


void notify_target(char* target){

	// create a fresh rule_t node that contains the target, with the cmd and dep empty, push the rule_t node to the rules queue
	rule_t *rule_node = (rule_t*) malloc(sizeof(rule_node));
	rule_init(rule_node);
	rule_node->target = (char*) malloc(sizeof(char)*strlen(target)+1);
	strcpy(rule_node->target,target);

	queue_enqueue(pool->rules_queue,(void*) rule_node);

	
	rules_satisfy* satisfy_node = (rules_satisfy*) malloc(sizeof(rules_satisfy));
	rules_satisfy_init(satisfy_node);
	satisfy_node->target = (char*) malloc(sizeof(char)*strlen(target)+1);
	strcpy(satisfy_node->target,target);

	queue_enqueue(pool->satisfy_queue,(void*) satisfy_node);
	//printf("I'm at notify target and target is %s\n", target);
}


void notify_dep(char* target, char* dep){

	rule_t *rule_node=NULL;
	// walk down the rules queue and find the corresponding target rules_t node. push the dep to the rules_t node of the target. 
	for (int i=0; i<queue_size(pool->rules_queue);i++){
		
		rule_node=queue_at(pool->rules_queue,i);
		if(!strcmp(rule_node->target,target)){
			break;
		}
	}

	if (rule_node==NULL){
		perror("Did not find target when inserting depandancy\n");
		exit(1);
	}
//printf("I'm at line %d and depandancy is %s\n",__LINE__, dep);
	char* dep_new = (char*) malloc(sizeof(char)*strlen(dep)+1);
	strcpy(dep_new ,dep);
	queue_enqueue(rule_node->deps, (void*) dep_new);
	//printf("I'm at notify dependency, target is %s, and dependency is %s\n", target, dep);
}

void notify_cmd(char* target, char* cmd){

	//printf("I'm at notify command, target is %s, and command is %s\n", target, cmd);

	rule_t *rule_node=NULL;
	// walk down the rules queue and find the corresponding target rules_t node. push the dep to the rules_t node of the target. 
	for (int i=0; i<queue_size(pool->rules_queue);i++){
		
		rule_node=queue_at(pool->rules_queue,i);
		if(!strcmp(rule_node->target,target)){
			break;
		}
	}

	if (rule_node==NULL){
		perror("Did not find target when inserting depandancy\n");
		exit(1);
	}
//printf("I'm at line %d and command is %s\n",__LINE__, cmd);
	char* cmd_new = (char*) malloc(sizeof(char)*strlen(cmd)+1);
	strcpy(cmd_new ,cmd);
	queue_enqueue(rule_node->commands, (void*) cmd_new);
}

void show_full_parse (){

	rule_t *rule_node=NULL;
	for (int i=0; i<queue_size(pool->rules_queue);i++){
		
		rule_node=queue_at(pool->rules_queue,i);
		printf("Target is :%s\n", rule_node->target);
		printf("Depandancy size is :%d\n", queue_size(rule_node->deps));
		printf("Command size is :%d\n", queue_size(rule_node->commands));
		for (int j=0; j< queue_size(rule_node->deps);j++){
			printf("dependancy is :%s\n", (char*) queue_at(rule_node->deps,j));
		}
		for (int j=0; j< queue_size(rule_node->commands);j++){
			printf("command is :%s\n", (char*) queue_at(rule_node->commands,j));
		}
	}

}

void destroy_rule_node(rule_t* rule_node){

	for (int j=0; j< queue_size(rule_node->deps);j++){
		free(queue_at(rule_node->deps,j));
	}
	for (int j=0; j< queue_size(rule_node->commands);j++){
		free(queue_at(rule_node->commands,j));
	}
	free(rule_node->target);		

	queue_destroy(rule_node->deps);
	queue_destroy(rule_node->commands);
	rule_destroy(rule_node);
	free(rule_node);

}

void destroy_everything(){
	
	rule_t *rule_node=NULL;
	for (int i=0; i<queue_size(pool->rules_queue);i++){
		
		rule_node=queue_at(pool->rules_queue,i);
		
		for (int j=0; j< queue_size(rule_node->deps);j++){
			free(queue_at(rule_node->deps,j));
		}
		for (int j=0; j< queue_size(rule_node->commands);j++){
			free(queue_at(rule_node->commands,j));
		}
		free(rule_node->target);		

		queue_destroy(rule_node->deps);
		queue_destroy(rule_node->commands);
		rule_destroy(rule_node);
		free(rule_node);
	}

	queue_destroy(pool->rules_queue);

	
	for (int i=0; i<queue_size(pool->satisfy_queue);i++){
		
		free(((rules_satisfy*) queue_at(pool->satisfy_queue,i))->target);
		free(queue_at(pool->satisfy_queue,i));
	}

	queue_destroy(pool->satisfy_queue);

	free(pool->rules_queue);
	free(pool->satisfy_queue);

	pthread_mutex_destroy(&(pool->mt));
	pthread_cond_destroy(&(pool->cv));

	free(pool->threads);
}


bool work_on_rules(rule_t* rule_node){

	bool has_dep_n_file = false;
	bool has_dep_new = false;

	// no depandancy 
	if(queue_size(rule_node->deps) ==0 ){
		if (access(rule_node->target,F_OK) == -1){
			for (int i=0; i< queue_size(rule_node->commands);i++){
				//system((char*) queue_dequeue(rule_node->commands));
				if(system((char*) queue_at(rule_node->commands,i)) != 0){
					exit(2);
				}
			}
			satisfy_node(rule_node->target)->satisfy = true;
		} else{
			satisfy_node(rule_node->target)->satisfy = true;
		}
		return true;
	}
	
	// logically if first_cond is true, will not go into the following loop, since number of depandancy is zero.
	// has depandancy and none of depandancy is file on disk, and all depandancies are satisfied, whether or not target it file on disk
	for (int i=0; i< queue_size(rule_node->deps);i++){
		if (satisfy_node((char*) queue_at(rule_node->deps,i))->satisfy || access((char*) queue_at(rule_node->deps,i),F_OK) == 0){
			if (access((char*) queue_at(rule_node->deps,i),F_OK) == -1){
				has_dep_n_file = true;
			}			
		} else {
			return false;
		}
	}
	
	// up to here, the target has depandancy and all depandancies are met and all files exits
	if (has_dep_n_file){
		for (int i=0; i< queue_size(rule_node->commands);i++){
			//system((char*) queue_dequeue(rule_node->commands));
			if(system((char*) queue_at(rule_node->commands,i)) !=0){
				exit(2);
			}
		}
		satisfy_node(rule_node->target)->satisfy = true;
		return true;
	}

	// up to here, the target has depandancy and all depandancies are met, and all depandancies are files on disk
	struct stat target_buff;
	struct stat file_buff;
	//printf("I'm at line %d \n",__LINE__);

	if ( stat(rule_node->target, &file_buff) != 0 ){
		for (int i=0; i< queue_size(rule_node->commands);i++){
			//printf("command is %s\n",(char*) queue_dequeue(rule_node->commands));
			//system((char*) queue_dequeue(rule_node->commands));
			if(system((char*) queue_at(rule_node->commands,i)) != 0){
				exit(2);
			}
		}
		satisfy_node(rule_node->target)->satisfy = true;
		return true;
	}

	for (int i=0; i< queue_size(rule_node->deps);i++){
		if ( stat((char*)queue_at(rule_node->deps,i), &file_buff) != 0 ){
			perror("Error using stat() for depandancy\n");
			exit(1);
		}
		if (file_buff.st_mtime > target_buff.st_mtime){
			has_dep_new = true;
			break;
		}
	}

	if (has_dep_new){
		for (int i=0; i< queue_size(rule_node->commands);i++){
			//system((char*) queue_dequeue(rule_node->commands));
			if(system((char*) queue_at(rule_node->commands,i)) != 0){
				exit(2);
			}
		}
		satisfy_node(rule_node->target)->satisfy = true;
	} else {
		satisfy_node(rule_node->target)->satisfy = true;
	}

	return true;
}

libtsan
void pool_init(thread_pool* pool, int num_threads){

	pool->rules_queue = (queue_t*) malloc(sizeof(queue_t));
	pool->satisfy_queue = (queue_t*) malloc(sizeof(queue_t));
	queue_init(pool->rules_queue);
	queue_init(pool->satisfy_queue);

	pthread_mutex_init(&(pool->mt),NULL);
	pthread_cond_init(&(pool->cv),NULL);

	pool->threads = (pthread_t*) malloc(sizeof(pthread_t)*num_threads);
	pool->num_threads = num_threads;
	pool->ifquit = false;
	pool->finished_num = 0;
	pool->goto_sleep = false;
	pool->num_rules = 0;
}


void* thread_function (void* params){
	
	pthread_mutex_lock(&(pool->mt));
	while(!pool->ifquit){
		pthread_mutex_unlock(&(pool->mt));
		
//printf("I'm at line %d \n",__LINE__);
		
		pthread_mutex_lock(&(pool->mt));
		if (pool->num_threads !=1){
			while(pool->goto_sleep || queue_size(pool->rules_queue) <=1){
				if (pool->ifquit){
					pthread_mutex_unlock(&(pool->mt));
					pthread_exit(0);
				}
				pthread_cond_wait(&(pool->cv),&(pool->mt));
			}
		}
		rule_t* rule_node = (rule_t*) queue_dequeue(pool->rules_queue);

		if (!strcmp(rule_node->target,"endofoneloop")){
			pool->goto_sleep = true;
			queue_enqueue(pool->rules_queue,rule_node);
			pthread_mutex_unlock(&(pool->mt));
			continue;
		}
		pthread_mutex_unlock(&(pool->mt));
		

		if(work_on_rules(rule_node)){
			pthread_mutex_lock(&(pool->mt));
			pool->finished_num++;
			pool->goto_sleep = false;
			destroy_rule_node(rule_node);
//printf("I'm at line %d \n",__LINE__);
			if (pool->finished_num == pool->num_rules ){
//printf("I'm at line %d \n",__LINE__);
				pool->ifquit = true;
			}
			pthread_mutex_unlock(&(pool->mt));
			pthread_cond_broadcast(&(pool->cv));
//printf("I'm at line %d \n",__LINE__);	
		}else {
			pthread_mutex_lock(&(pool->mt));
			queue_enqueue(pool->rules_queue,rule_node);
			pthread_mutex_unlock(&(pool->mt));
		}
//printf("I'm at line %d \n",__LINE__);		
		pthread_mutex_lock(&(pool->mt));
	}	
	pthread_mutex_unlock(&(pool->mt));
//printf("I'm at line %d \n",__LINE__);	

	pthread_exit(0);
}


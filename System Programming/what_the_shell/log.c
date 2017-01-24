// Shell
// CS 241 Fall 2015
#define _GNU_SOURCE
#include "log.h"
#include "vector.h"
#include <string.h>
#include <sys/types.h>
#include <stdio.h>

Log *Log_create(const char *filename) { 

	Log* log = (Log*) malloc (sizeof(Log));
	log->vtr = Vector_create();

	FILE *fd = fopen(filename,"r");
	if(fd==NULL){
		// if fopen fail, cannot fclose anything.
		return log;
	}

	size_t size = 0;
	ssize_t size_read;
	char *buffer=NULL;
	while((size_read = getline(&buffer,&size,fd))!= -1){
		if (buffer[size_read-1]=='\n'){
			buffer[size_read-1]='\0';		// replace the newline character with \0, supposedly every command should end with a new line, from the save *** need to see whether shell input gives a newline character.
// So command in data structure does not have newline
		}
		Vector_append(log->vtr,buffer);
	}
	free(buffer);

	fclose(fd);
	return log; 
}

int Log_save(Log *log, const char *filename) { 

	FILE* fd = fopen(filename,"w");
	
	for(int i=0;i<Vector_size(log->vtr);i++){
		fprintf(fd,"%s\n",Vector_get(log->vtr,i)); // here give a \n to each command, need to look at create() when this part is changed
	}
	fclose(fd);

	return 1; 
}

void Log_destroy(Log *log) {

	Vector_destroy(log->vtr);
	free(log);

}

void Log_add_command(Log *log, const char *command) {

	Vector_append(log->vtr,command);
}

const char *Log_reverse_search(Log *log, const char *prefix) { 
	
	char* result=NULL;
	char buffer[100];

	for (int i = Vector_size(log->vtr); i >0;i--){
		strcpy(buffer,Vector_get(log->vtr,i-1));
		 
		result = strstr(buffer,prefix);
		if (result!=NULL && result == buffer){  // compare the same pointer.!!!
			return Vector_get(log->vtr,i-1);
		}
		
	}	
	

	return result;
}

const char *Log_get_command(Log *log, size_t index) {
		

	if ( (size_t)Vector_size(log->vtr)< index+1){
		perror("Log command index out of bound\n");		
		return NULL;
	}
	
	return Vector_get(log->vtr,index);

}

// this returned char* need to be freed by the caller. 
char *Log_get_printable_history(Log *log) {

	char* total_buffer = (char*)malloc(1000 * sizeof(char));
	total_buffer[0]='\0'; // to use strcat, have this is very important
	char buffer[100];
	for (int i=0;i<Vector_size(log->vtr);i++){
		sprintf(buffer,"%d\t%s\n",i+1,Vector_get(log->vtr,i));
		strcat(total_buffer,buffer);
	}

	return total_buffer;

}

// Shell
// CS 241 Fall 2015
#define _GNU_SOURCE
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>


void slash_h_mode ();
void slash_f_mode ();
void process_command (char*);
void execute_command(void (*)(char*),char*);
void cd_command (char*);
void exit_command (char*);
void history_command (char*);
void reuse_command (char*);
void query_command (char*);
void nonbuilt_command (char*);

char* currentwd;
pid_t parentpid;
Log* chenlog;

void ctrl_c_handler (){
	return;
}

int main(int argc, char *argv[]) { 

	signal(SIGINT,ctrl_c_handler);

	if (argc<2){
		perror("The number of input argument is not right\n");
		exit(1);
	}

	char* mode = argv[1];
	currentwd = get_current_dir_name();
	parentpid = getpid();
	chenlog = Log_create("czhang49ShellLog.txt");

	if(!strcmp(mode,"-h")){
		// use stderr to flush it right away, not using \n
		fprintf(stderr, "Shell by czhang49\n(pid=%d)%s$ ",parentpid,currentwd);
		slash_h_mode();
	}

	if(!strcmp(mode,"-f")){
		// use stderr to flush it right away, not using \n
		printf("Shell by czhang49\n");
		slash_f_mode(argv[2]);
	}
	
	return 0; 

}

void slash_h_mode (){

	size_t size=0;
	size_t size_read=0;
	char* buff=NULL;
	while(1){
			
		size_read = getline(&buff,&size,stdin);
		buff[size_read-1] = '\0'; // replace the newline \n in buff with \0
		
		process_command(buff);	// send command to process
		fprintf(stderr,"(pid=%d)%s$ ",parentpid,currentwd);
	}

	// note that in case of interrupt, the free is not performed and potential memory loss.	
}

void slash_f_mode(char* filename){

	FILE* fd = fopen(filename,"r");

	size_t size=0;
	size_t size_read=0;
	char* buff=NULL;

	size_read = getline(&buff,&size,fd);
	while(buff!=NULL){

		buff[size_read-1] = '\0'; // replace the newline \n in buff with \0
		fprintf(stderr,"(pid=%d)%s$ %s\n",parentpid,currentwd,buff);
		process_command(buff);	// send command to process
		size_read = getline(&buff,&size,fd);
	}
	
	free(buff);
	fclose(fd);

}

void process_command (char* command){

	// take command to local buffer
	char buff[256];
	char bufforiginal[256];
	buff[0]= '\0';
	bufforiginal[0]= '\0';
	strcpy(buff,command);
	strcpy(bufforiginal,command);
	
	char* pch = NULL;
	pch = strtok(buff," ");

	if (pch==NULL){
		return;
	}
	if (!strcmp(pch,"cd")){
		pch = strtok(NULL," ");
		execute_command(cd_command,pch);
		return;
	}
	if (!strcmp(pch,"exit")){
		execute_command(exit_command,pch);
		free(command);
		exit(0);
	}
	if (!strcmp(pch,"!history")){
		execute_command(history_command,pch);
		return;
	}
	if ((*pch)=='!' && isdigit(*(pch+1))){
		execute_command(reuse_command,pch);
		return;
	}
	else if ((*pch)=='!'){
		execute_command(query_command,pch);
		return;
	} else {
		execute_command(nonbuilt_command,bufforiginal);
		return;
	}

}

void execute_command(void (*command_function)(char*) ,char* pch){
	command_function(pch); // this function only executes, the command function it self is responsible for storing the command.
}

void cd_command(char* directory){

	char command[128]="cd ";
	strcat(command,directory);
	Log_add_command(chenlog,command);



	int cd_result;
	if ((cd_result=chdir(directory))==-1){
		
		fprintf(stderr,"%s ",directory);
		perror(" ");
		return;
	}
	free(currentwd);
	currentwd = get_current_dir_name();

}

void exit_command(char* command){

	Log_add_command(chenlog,command);
	Log_save(chenlog,"czhang49ShellLog.txt");
	Log_destroy(chenlog);
	free(currentwd);
}

void history_command(char* command){
	

	Log_add_command(chenlog,command);

	char* printable = Log_get_printable_history(chenlog);

	printf("%s",printable);

	free(printable);
}

void reuse_command(char* command){

	int number = atoi(command+1);
	char hist_command[128];
	const char* result = Log_get_command(chenlog, number);

	if (result == NULL){
		printf("Invalid Index\n");

	}else{
		strcpy(hist_command,result);
		printf("%s\n",hist_command);
		process_command(hist_command);
	}

}

void query_command(char* command){

	char* match = command+1;
	char query_command[128];
	const char* result = Log_reverse_search(chenlog,match);


	if (result == NULL){
		printf("No Match\n");

	}else{
		strcpy(query_command,result);
		printf("%s\n",query_command);
		process_command(query_command);
	}
}

void nonbuilt_command (char* command){

	Log_add_command(chenlog,command);
	char buffer[256];
	int counter=0;
	char* pch = NULL;
	strcpy(buffer,command);

	int flag=0;
	char* find_cmd = NULL;
	find_cmd = strchr(buffer,'&');
	if (find_cmd!=NULL){
		*find_cmd = '\0';
		flag=1;	
	}

	
	// find number of arguments
	pch = strchr(buffer,' ');
	while(pch!=NULL){
		counter++;
		// remember to move the pointer by increasing by 1 !
		pch = strchr(pch+1,' ');		
	}

	char* arg[counter+2];

	arg[0] = strtok(buffer," ");

	for(int i=1;i<=counter;i++){
		arg[i] = strtok(NULL," ");
	}
	// remember to use execvp the last string needs to be NULL
	arg[counter+1]=NULL;	

	pid_t pid = fork();
	if (pid == 0){
		pid_t mypid = getpid();
		printf("Command executed by pid=%d \n",mypid);
		execvp(arg[0],arg);		
		exit(2);
	}else{
		if (flag==1){
			return;
		}

		int status=0;
		waitpid(pid,&status,0);
		printf("Status of child is %d \n",WEXITSTATUS(status));
		if (status!=0){
			printf("%s : not found\n",arg[0]);
		}		
	}

}

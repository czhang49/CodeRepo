#define _POSIX_C_SOURCE 199309L
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
	pid_t child;
	char* pass_in[argc];
	int counter;
	for(counter=0;counter<argc-1;counter++){
		
		pass_in[counter]=argv[counter+1];
	}
	pass_in[argc-1]=NULL;

	struct timespec start_time;
	struct timespec end_time;
	memset(&start_time, 0, sizeof(struct timespec));
	memset(&end_time, 0, sizeof(struct timespec));

	clock_gettime(CLOCK_MONOTONIC,&start_time);
	child=fork();
		
	if (child==0){
		execvp(argv[1], pass_in);
		perror("execv failed");
		fprintf(stderr, "Child Process gets to here");
		exit(11);
  	} else {
		int status;
		waitpid(child,&status,0);
		clock_gettime(CLOCK_MONOTONIC,&end_time);
		fprintf(stderr, "Child Process Status:%d\n",status);
		fprintf(stderr, "The elapsed time in child process execution is:%f\n",(double)(end_time.tv_sec-start_time.tv_sec)+(double)(end_time.tv_nsec-start_time.tv_nsec)/1000000000);
	}
		
	return 0;
}

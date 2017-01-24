#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "common.h"

int main(int argc, char* argv[]) {
	
	if (argc !=5){
		perror("You dumbass idiot the input format is wrong\n");
		exit(1);
	}

    	// Open the input file.
	FILE* inputfd = fopen(argv[1],"r");

    	// Create a pipe to connect the mapper to the reducer.
	int pipefd[2];
	pipe(pipefd);

	descriptors_add(pipefd[0]);
	descriptors_add(pipefd[1]);
    	// Open the output file.
	FILE* outputfd = fopen(argv[2],"w"); 
	
    	// Start the mapper.
	pid_t mapperpid = fork();
	if (mapperpid==0){
	
		dup2(fileno(inputfd),STDIN_FILENO);
		dup2(pipefd[1],STDOUT_FILENO);
		
		// close the read part is necessary for the other end to finish
		//close(pipefd[0]);
		// close the write part and the inputfd is optional, since they are on stack, no much need to delte, also they are already used in the redirection, so ok to close.
		//close(pipefd[1]);
		//fclose(inputfd);		

		descriptors_closeall(); // this actually closes all the passed-in file descriptors, but since the needed is copied to stdout, so it's ok to do this
		execl(argv[3],argv[3],NULL);

		perror("The mapper execution has a problem\n");
		exit(123);
	}

    	// Start the reducer.
	pid_t reducerpid = fork();
	if (reducerpid==0){
		
		dup2(fileno(outputfd),STDOUT_FILENO);
		dup2(pipefd[0],STDIN_FILENO);

		// close the write part is necessary for the other end to finish
		//close(pipefd[1]);
		// close the read part and the output is optional. since they are on stack, no much need to delte, also they are already used in the redirection, so ok to close.
		//close(pipefd[0]);
		//fclose(outputfd);
		
		descriptors_closeall(); // this actually closes all the passed-in file descriptors, but since the needed is already copied to stdin, it's ok to do this.
		execl(argv[4],argv[4],NULL);

		perror("The reducer execution has a problem\n");
		exit(123);
	}

	// the main process also has the pipe descriptors, remember to close them
	//close(pipefd[0]);
	//close(pipefd[1]);
	descriptors_closeall(); // this actually closes all the passed-in file descriptors, but since none of the descriptors will be used in the main process, it's ok to do this.

    	// Wait for the reducer to finish.
	int mapper_exitstat;
	int reducer_exitstat;

	waitpid(mapperpid,&mapper_exitstat,0);
	waitpid(reducerpid,&reducer_exitstat,0);
	

    	// Print nonzero subprocess exit codes.
	printf("The exit status of mapper process is %d\n",WEXITSTATUS(mapper_exitstat));
	printf("The exit status of reducer process is %d\n",WEXITSTATUS(reducer_exitstat));

    	// Count the number of lines in the output file.
	int num_lines_output=0;
	char* line = NULL;
	size_t size = 0; 
	FILE* output_readfd = fopen(argv[2],"r");
	while(getline(&line,&size,output_readfd) != -1){
		
		num_lines_output++;
	}
	free(line);
	printf("The total number of lines in the output file is %d\n", num_lines_output);

	fclose(inputfd);
	fclose(outputfd);
	fclose(output_readfd);
	descriptors_destroy(); 
    	return 0;
}

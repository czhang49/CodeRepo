#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "common.h"


int main(int argc, char* argv[]) {

	if (argc != 6){
		perror("Wrong number of input parameters you dumbass. \n");
		exit(1);
	}

	int num_mapper = atoi(argv[5]);
    	// Create an input pipe for each mapper.
	int mapper_pipefd[num_mapper][2];
	for (int i=0; i <num_mapper;i++){
		pipe(mapper_pipefd[i]);
		descriptors_add(mapper_pipefd[i][0]);
		descriptors_add(mapper_pipefd[i][1]);	
	}    

    	// Create one input pipe for the reducer.
	int reducer_pipefd[2];
	pipe(reducer_pipefd);
	descriptors_add(reducer_pipefd[0]);
	descriptors_add(reducer_pipefd[1]);

    	// Open the output file.
    	FILE* outputfd = fopen(argv[2],"w");

    	// Start a splitter process for each mapper.
	pid_t splitter_pid[num_mapper];
	for (int i=0; i<num_mapper; i++){
		
		splitter_pid[i] = fork();
		if (splitter_pid[i]>0){
			continue;
		} else{
			dup2(mapper_pipefd[i][1],STDOUT_FILENO);
	
			descriptors_closeall();
			fclose(outputfd);
			
			char i_string [5];
			sprintf(i_string,"%d",i);
			execl("splitter","./splitter",argv[1],argv[5],i_string,NULL);
			
			perror("The splitter executable has a problem.\n");
			exit(123);
		}
	}	

    	// Start all the mapper processes.
	pid_t mapper_pid[num_mapper];
	for (int i=0; i<num_mapper; i++){

		mapper_pid[i] = fork();
		if (mapper_pid[i] >0){
			continue;
		}else {
			dup2(mapper_pipefd[i][0], STDIN_FILENO);
			dup2(reducer_pipefd[1], STDOUT_FILENO);

			descriptors_closeall();
			fclose(outputfd);

			execl(argv[3],argv[3],NULL);

			perror("The mapper executable has a problem\n");
			exit(123);	
		}

	}
	
	

    	// Start the reducer process.
	pid_t reducer_pid =  fork();
	if (reducer_pid ==0){
		dup2(reducer_pipefd[0],STDIN_FILENO);
		dup2(fileno(outputfd),STDOUT_FILENO);

		descriptors_closeall();
		fclose(outputfd);

		execl(argv[4],argv[4],NULL);
		
		perror("The reducer executable has a problem\n");
		exit(123);
	}

    	// Wait for the reducer to finish.
	descriptors_closeall();


	int splitter_exitstat;
	int mapper_exitstat;
	int reducer_exitstat;

	for (int i=0; i<num_mapper; i++){
		waitpid(splitter_pid[i],&splitter_exitstat,0);
		if (splitter_exitstat!=0){
			printf("Number %d splitter exit with code %d\n",i,WEXITSTATUS(splitter_exitstat));
		}
	}
	
	for (int i=0; i<num_mapper; i++){
		waitpid(mapper_pid[i],&mapper_exitstat,0);
		if (mapper_exitstat!=0){
			printf("Number %d mapper exit with code %d\n",i,WEXITSTATUS(mapper_exitstat));
		}
	}
	
	waitpid(reducer_pid,&reducer_exitstat,0);
	if (reducer_exitstat!=0){
		printf("The exit status of reducer process is %d\n",WEXITSTATUS(reducer_exitstat));
	}

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



	fclose(outputfd);
	fclose(output_readfd);
	descriptors_destroy(); 

    	return 0;
}

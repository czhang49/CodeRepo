#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include "common.h"


int main(int argc, char* argv[]) {

	if (argc != 7){
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


    	// Start a splitter process for each mapper.
	pid_t splitter_pid[num_mapper];
	for (int i=0; i<num_mapper; i++){
		
		splitter_pid[i] = fork();
		if (splitter_pid[i]>0){
			continue;
		} else{
			dup2(mapper_pipefd[i][1],STDOUT_FILENO);
			// need to close all the descriptors because of the copy, the problem is that all the process have all the file descriptors in all the process, because of the forking.
			descriptors_closeall();
			
			char i_string [5];
			sprintf(i_string,"%d",i);
			execl("splitter","./splitter",argv[1],argv[5],i_string,NULL);
			
			perror("The splitter executable has a problem.\n");
			exit(123);
		}
	}	

	// Create one input pipe for the shuffler.
	int shuffler_pipefd[2];
	pipe(shuffler_pipefd);
	descriptors_add(shuffler_pipefd[0]);
	descriptors_add(shuffler_pipefd[1]);


    	// Start all the mapper processes.
	pid_t mapper_pid[num_mapper];
	for (int i=0; i<num_mapper; i++){

		mapper_pid[i] = fork();
		if (mapper_pid[i] >0){
			continue;
		}else {
			dup2(mapper_pipefd[i][0], STDIN_FILENO);
			dup2(shuffler_pipefd[1], STDOUT_FILENO);

			// better use close all, because otherwise need to loop over all the processes
			descriptors_closeall();

			execl(argv[3],argv[3],NULL);

			perror("The mapper executable has a problem\n");
			exit(123);	
		}

	}


    	// create the names of the fifo file to be mififofile_%d
	int num_reducer = atoi(argv[6]);

	char* param[num_reducer+2];
	param[0] = malloc (sizeof(char)*128);
	strcpy(param[0],"./shuffler");
	for (int i=1; i<num_reducer+1;i++){
		param[i] = malloc (sizeof(char)*128);
		sprintf(param[i],"./mkfifofile_%d",i);
	}
	param[num_reducer+1]=NULL;

	// create the FIFO files
	int fifostat;	
	for (int i=0; i<num_reducer; i++){
		int removestat;
		removestat = remove(param[i+1]);

		fifostat=mkfifo(param[i+1],S_IRWXU);
		if (fifostat!=0){
			perror("There is a problem creating the mkfifo files");
		}
	}

	// Start the shuffler.
	pid_t shuffler_pid = fork();
	if (shuffler_pid ==0){

		dup2(shuffler_pipefd[0],STDIN_FILENO);

		descriptors_closeall();
		execv("./shuffler",param);

		perror("The shuffler execution has a problem\n");
		exit(123);
	}	

	// close all to let the previous processes to be able to finish, this is critical
	descriptors_closeall();
	
	// Open the output file.

	FILE* outputfd = fopen(argv[2],"a");
    	// Start the reducers.
	int reducer_pid[num_reducer];

	for (int i=0;i<num_reducer;i++){
		reducer_pid[i]=fork();
		if (reducer_pid[i]>0){
			continue;
		}else{

//printf("I'm at mr2 line %d, the file to be opened is %s\n",__LINE__,param[i+1]);
			int filedes = open(param[i+1],O_RDONLY);
			FILE* inputfd = fdopen(filedes,"r");
			dup2(fileno(inputfd),STDIN_FILENO);
			dup2(fileno(outputfd),STDOUT_FILENO);

			descriptors_closeall();
			execl(argv[4],argv[4],NULL);

			perror("The reducer execution has a problem\n");
			exit(123);
		}
	}

    	// Wait for all the reducers to finish.
	
	int shuffler_exitstat;
	waitpid(shuffler_pid,&shuffler_exitstat,0);
	if (shuffler_exitstat!=0){
		printf("Number %d shuffler exit forkwith code lower 8 tobe %d and full tobe%d\n",shuffler_pid,WEXITSTATUS(shuffler_exitstat),shuffler_exitstat);
	}
    	

	int reducer_exitstat;
	for (int i=0; i<num_reducer; i++){
		waitpid(reducer_pid[i],&reducer_exitstat,0);
		if (reducer_exitstat!=0){
			printf("Number %d reducer exit with code %d\n",i,WEXITSTATUS(reducer_exitstat));
		}
	}
    	
	// Remove the fifo files.
	for (int i=0; i<num_reducer; i++){
		int removestat;
		removestat = remove(param[i+1]);

	}
    	// Print nonzero subprocess exit codes.

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


	for (int i=0; i<num_reducer+1;i++){
		free(param[i]);
	}

	fclose(outputfd);
	fclose(output_readfd);
	descriptors_destroy(); 
    	return 0;
}

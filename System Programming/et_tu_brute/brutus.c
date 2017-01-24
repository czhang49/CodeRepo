#define _GNU_SOURCE
#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char *argv[]) {

	if (argc !=3){
		perror("The number of argument should be 3\n");
		exit(1);
	}

	int number_lines=0;
	char* cipher_line=NULL;
	size_t size_limit = 0;
	ssize_t line_length= 0;	

	FILE* fd = fopen(argv[1],"r");
	while ((line_length=getline(&cipher_line,&size_limit,fd))!=-1){
		number_lines++;
	}
	//free(cipher_line);

	int pipefd[number_lines][2];
	pid_t childPID[number_lines];
	rewind(fd);
	
	int counter=0;
	while ((line_length=getline(&cipher_line,&size_limit,fd))!=-1){
		
		pipe(pipefd[counter]);

		pid_t p = fork();
		if (p>0){
			childPID[counter]=p;
			counter++;
			continue;
		}else{
			char* plain_line;
			close(pipefd[counter][0]);
			// note here I've tried wrapping stuff in a descriptor, but it seems that it is not working as expected, werid problems occur, e.g. the fputs only put the first word and then stopped.
			plain_line = get_most_likely_print_out (cipher_line);
			free(cipher_line);
			write(pipefd[counter][1], plain_line, strlen(plain_line)+1);
			free(plain_line);
			exit(0);
		}	
	}
	fclose(fd);

	FILE* fd2=fopen(argv[2],"w");
	char result[1000];
	for (int i=0;i<counter;i++){
		close(pipefd[i][1]);
		waitpid(childPID[i],NULL,0);	
		read(pipefd[i][0],result,sizeof(result));
		fprintf(fd2,"%s",result);
	}
	fclose(fd2);

	return 0;
}

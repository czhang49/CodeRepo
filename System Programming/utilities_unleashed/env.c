#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char** environ;

int main(int argc, char *argv[])
{
	char ** ptr = environ;	
	// if no additional input, list all the environement variables
	if (argc==1){
		while(*ptr){
			printf("%s\n",*ptr);
			ptr++;
		}
		exit(0);
	}
	// if two input then it is wrong
	if (argc ==2){
		perror("Wrong number of input parameters");
		exit(0);
	}
	// get the command and associated arguments for the command
	char *commands[argc-2+1];
	int counter;
	for (counter=0;counter<argc-2;counter++){
		commands[counter]=argv[counter+2];
	}
	commands[argc-2]=NULL;

	// get the changed variables
	char* variable_string = argv[1];
	char* find_comma;
	int number_changes=1;
	find_comma=strchr(variable_string,',');
	while(find_comma!=NULL){
		number_changes++;
		find_comma=strchr(find_comma+1,',');
	}
	char* variable_array[number_changes+1];
	variable_array[number_changes]=NULL;

	char* pch = strtok(variable_string,",");
	
	for (counter=0;counter<number_changes;counter++){
		variable_array[counter] = (char*) malloc (256*sizeof(char));
		strcpy(variable_array[counter],pch);
		pch = strtok(NULL,",");
	}
	// substitute the %variable name to the value of the reference
	char check_env_variable[1024];
	check_env_variable[0]='\0';
	char substituted[1024];
	substituted[0]='\0';
	for (counter=0;counter<number_changes;counter++){
		strcpy(check_env_variable,variable_array[counter]);
		pch = strtok(check_env_variable,"%");
		if (pch==NULL){
			strcat(substituted,check_env_variable);
		}
		while(pch!=NULL){
			strcat(substituted,pch);
			pch = strtok(NULL,"/");
			if (pch!=NULL){
				char * value = getenv(pch);

				if (value == NULL){
					strcat(substituted,"");
				} else{
					strcat(substituted,value);
				}
			}
			pch = strtok(NULL,"%");
			if (pch!=NULL){
				strcat(substituted,"/");
			}
		}
		strcpy(variable_array[counter],substituted);
		printf("The list of input env variables: %s\n",substituted);
		substituted[0]='\0';		
	}
	
	// fork , execvpe and waitpid
	pid_t child;
	child=fork();
	if (child == 0){
		execvpe(commands[0],commands,variable_array);
		perror("execvpe error");
		exit(11);	
	} else{
		int status;
		waitpid(child,&status,0);
		printf("The child process is finished\n");
	}

	for (counter=0;counter<number_changes;counter++){
		free(variable_array[counter]);
	}

  	return 0;
}

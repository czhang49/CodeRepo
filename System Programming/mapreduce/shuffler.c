#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include "common.h"


int main(int argc, char* argv[]) {

    	// open all the files for output
	int num_files = argc-1;

    	// read lines from stdin, hash them, send them to the correct output
	char* line=NULL;
	size_t size=0;

	char key[256];
	char value[256];
	char* pch;
//printf("I'm at shuffler line %d\n",__LINE__);
	while(getline(&line,&size,stdin) != -1){
		
		key[0]='\0';
		value[0]='\0';
		pch = strtok(line,":");
		strcpy(key,pch);
		pch = strtok(NULL,"\n");
		strcpy(value,pch);
		int index = hashKey(key) % num_files+1;		
		int filedes = open(argv[index],O_WRONLY);
		FILE* outf = fdopen(filedes,"w");
		fprintf(outf,"%s: %s\n",key,value);
	}
	free(line);
    	// each line is expected to be in "<key>: <value>" form


    	return 0;
}

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "editor.h"


int size_ofcontainer = 1;	// this is the total size of the container
int size_ofline=0;	// this is the already used number of lines

int main(int argc, char *argv[]) {

	char* file_name = NULL;
	file_name=get_filename(argc,argv);	


	data* data_ptr = (data*) malloc (size_ofcontainer*(sizeof(data)));	
	init (&data_ptr,file_name);	

	char* buffer = NULL;
	size_t size=0;
	int num_chars = 0;
	char* pch;
	int line_num;
	while(1){
		printf("Please input your command: ");
		if ((num_chars=getline(&buffer,&size,stdin))>1 && buffer[num_chars-1] == '\n'){
			buffer[num_chars-1]='\0';
		}else {
			printf("Invalid command, do it again\n");
			continue;
		}
		// from here the newline character is replaced by \0, so no need to consider newline at the end of string
		// everything before the ending \0 is a valid string
		if (buffer[0]=='/'){
			find(data_ptr,buffer+1);
			continue;
		}
	
		pch = strtok(buffer," ");

		if (*pch=='p'){
			pch = strtok(NULL," ");
			line_num = atoi(pch);
			display(data_ptr,line_num);
			continue;
		}
		if (*pch=='w'){
			pch = strtok(NULL," ");
			line_num = atoi(pch);
			pch = strtok(NULL,"\0");
			overwrite(&data_ptr,line_num, pch);
			continue;
		}
		/*if (*pch=='a'){
			pch = strtok(NULL," ");
			line_num = atoi(pch);
			pch = strtok(NULL,"\0");
			append(data_ptr,line_num, pch);
			continue;
		}*/
		if (*pch=='s'){
			save(data_ptr,file_name);
			continue;
		}
		if (*pch == 'q'){
			destroy(data_ptr);
			free(file_name);
			free(buffer);  // the buffer for ead need to be freed upon destroy
			buffer=NULL;
			break;
		}
		free(buffer);	// this is annoying, the buffer to take the argument needs to be freed for each round
		buffer=NULL;
	}

	printf("You successfully closed the text-editor\n");
	return 0;
}

char *get_filename(int argc, char *argv[]) {

	char* file_name_temp = (char*) malloc(100*sizeof(char));
	char junk[1];
	if (argc>=3){
		perror("Wrong Number of input parameters");
	}
	if (argc==2){
		strncpy(file_name_temp,argv[1],100);		
	}else{
		printf("Please input the name of your text file :\n");
		scanf("%99s",file_name_temp);
		scanf("%c",junk);	// this is shit, scanf leaves a \n at the input stream. scanf stops at any whitespace character
	}

	printf("The name of the file is %s\n", file_name_temp);
	return file_name_temp;	
}

void init(data** data_ptr_ptr, char *filename) {
	
	FILE* pFile = fopen(filename,"r");
	if (pFile == NULL){
		perror("The file is not found, if you edit you need to save.\n");
		return;
	}
	
	char* buffer=NULL;
	size_t size=0;
	int num_chars;
	
	while ((num_chars=getline(&buffer,&size,pFile))>0 && buffer[num_chars-1] == '\n'){
		buffer[num_chars-1] = '\0';
		(*data_ptr_ptr)[size_ofline].sentence = buffer;
		buffer = NULL;
		size_ofline += 1;
		(*data_ptr_ptr)[size_ofline-1].line_num = size_ofline; // note the line index and array index have 1 difference

		if (size_ofline == size_ofcontainer){
			size_ofcontainer += size_ofcontainer;
			(*data_ptr_ptr) = realloc((*data_ptr_ptr),size_ofcontainer*sizeof(data));
		}
	}
	free(buffer); // this is annoying, the final invalid buffer is still assigned some space, so need to free although the final buffer is not valid for use.
	fclose(pFile); // note that you need to close the file for each file open.
}


void display(data *data_ptr, int line) {
	if (line>size_ofline){
		perror("The line number exceeds the maximum number of lines in this file");
		return;
	}
	if (line==0){
		int i;
		for (i=1;i<=size_ofline;i++){
			printf("%d\t%s\n",data_ptr[i-1].line_num,data_ptr[i-1].sentence);
		}
		return;
	}

	printf("%d\t%s\n",data_ptr[line-1].line_num,data_ptr[line-1].sentence);
}

void overwrite(data** data_ptr_ptr, int line, char *string) {
	if (line==0){
		perror("The line number to write cannot be 0.\n");
	}

	char * pch = strstr(string,"\\n");
	if (pch!=NULL){
		*pch = '\0';	
	} 
	if (line<=size_ofline){
		free((*data_ptr_ptr)[line-1].sentence);
		(*data_ptr_ptr)[line-1].sentence = (char*) malloc((strlen(string)+1)*sizeof(char));
		strcpy((*data_ptr_ptr)[line-1].sentence,string);

		if (pch!=NULL){
			overwrite(data_ptr_ptr,line+1,pch+2);
		}
		return;
	}
	if (line > size_ofcontainer){
		size_ofcontainer = nextpowtwo(line);
		(*data_ptr_ptr) = realloc((*data_ptr_ptr),size_ofcontainer*sizeof(data));
	}


	(*data_ptr_ptr)[line-1].sentence = (char*) malloc((strlen(string)+1)*sizeof(char));
	strcpy((*data_ptr_ptr)[line-1].sentence,string);
	(*data_ptr_ptr)[line-1].line_num = line;
	int i;
	for (i=size_ofline+1;i<line;i++){
		(*data_ptr_ptr)[i-1].sentence = (char*) malloc(1*sizeof(char));
		(*data_ptr_ptr)[i-1].sentence[0] = '\0';
		(*data_ptr_ptr)[i-1].line_num = i;
	} 
	size_ofline = line;
	if (pch!=NULL){
		overwrite(data_ptr_ptr,line+1,pch+2);
	}
}

/*
void append(data* data_ptr, int line, char *string) {
}
*/
void find(data *data_ptr, char *search_term) {
	int i;
	char* pch;
	for (i=1;i<=size_ofline;i++){
		pch = strstr(data_ptr[i-1].sentence,search_term);
		if (pch!=NULL){
			char sentence[strlen(data_ptr[i-1].sentence)+1];
			strcpy(sentence,data_ptr[i-1].sentence);
			pch = strstr(sentence,search_term);
			*pch = '\0';
			char secondhalf[strlen(sentence)+1];
			char firsthalf[strlen(pch+strlen(search_term))+1];
			strcpy(firsthalf,sentence);
			strcpy(secondhalf,pch+strlen(search_term));
			
			printf("%d\t%s[%s]%s\n",data_ptr[i-1].line_num,firsthalf,search_term,secondhalf);
		}
	}

}

void save(data *data_ptr, char *filename) {
	FILE* pFile = fopen(filename,"w");
	int i;
	for (i=1;i<=size_ofline;i++){
		fprintf(pFile,"%s\n",data_ptr[i-1].sentence);
	}	

	fclose(pFile);
}

void destroy(data *data_ptr) {
	int i;
	for (i=1;i<=size_ofline;i++){
		free(data_ptr[i-1].sentence);
	}
	free(data_ptr);
}

int nextpowtwo(int line){

	int nextpow =0;
	int i;
	for (i=0;i<20;i++){
		if (pow(2,i)>line){
			nextpow = pow(2,i);			
			break;
		}
	}
	if (nextpow==0){
		perror("The next power of 2 function is not right.\n");
	}
	return nextpow;
}


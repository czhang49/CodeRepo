#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

uint32_t find_word(char* word, char* data);

int main (int argc, char* argv[]){

	if(argc <3){
		perror ("The number of input should be larger than 3");
		exit(1);
	}

	int fd;
	char* data;
	struct stat sbuf;
	char* file_name = argv[1];
	char btre[5];
	char buffer[1000];

	if((fd = open(file_name,O_RDONLY))==-1){
		perror("the name of the file is wrong\n");
		exit(1);
	}
	
	if (stat(file_name, &sbuf) == -1) {
	        perror("stat has a problem\n");
        	exit(1);
    	}
	
	data = mmap(0,sbuf.st_size,PROT_READ,MAP_SHARED,fd,0);
	if ((void*) data == (void*)-1){
		perror("MMAP has a problem\n");
		exit(1);
	}
	strncpy(btre,data,4);
	btre[4]='\0';

	if (strcmp(btre,"BTRE")){
		perror("The first 4 bytes of the file is not BTRE, program exit\n");
		exit(1);
	}


	for (int i=2;i<argc;i++){
		char* word = argv[i];
		uint32_t result = find_word(word,data);
		if (result==0){
			printf("%s not found\n",word);
		}else{
			uint32_t count;
			float value;
			count = *(uint32_t *)(data+result+8); // seems that dereference by int may not work because maybe the implementation for int in this system or complier is not 4 bytes
			value = *(float*)(data+result+12);
			strcpy(buffer,data+result+16);
			printf("%s: %u at $%f \n",buffer,count,value);
		}
	}

	return 0;
}

uint32_t find_word(char* word, char* data){

	uint32_t block_offset=4;
	uint32_t leftchild_offset;
	uint32_t rightchild_offset;
	char buffer[1000];
	uint32_t result=0;

	int strcmp_result;

	do{
		leftchild_offset = *((uint32_t*)(data+block_offset));
		rightchild_offset = *((uint32_t*)(data+block_offset+4)); 

		strcpy(buffer,data+block_offset+16);
		strcmp_result=strcmp(buffer,word);
		
		if(!strcmp_result){
			result=block_offset;
			break;
		}
		block_offset = strcmp_result<0 ? rightchild_offset: leftchild_offset;			

	}while(block_offset!=0);


	return result;

}


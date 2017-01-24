#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int find_word(char*, FILE* pFile);

int main (int argc, char* argv[]){

	if(argc <3){
		perror ("The number of input should be larger than 3");
	}
	
	char* file_name = argv[1];
	FILE* pFile = fopen(file_name,"r");
	char btre[5];
	char buffer[1000];
	int read_size;

	
	read_size=fread(btre,sizeof(char),4,pFile);
	btre[read_size]='\0';

	if (strcmp(btre,"BTRE")){
		perror("The first 4 bytes of the file is not BTRE, program exit\n");
		exit(1);
	}
	
	for (int i=2;i<argc;i++){
		char* word = argv[i];
		int result = find_word(word,pFile);
		if (result==0){
			printf("%s not found\n",word);
		}else{
			int seek_flag;
			int count;
			float value;
			seek_flag = fseek(pFile,result+8,SEEK_SET);
			read_size = fread(&count,4,1,pFile);
			read_size = fread(&value,4,1,pFile);
			fgets(buffer,sizeof(buffer),pFile);
			printf("%s: %d at $%f \n",buffer,count,value);
		}
	}
	
	/*
	int seek_flag;
	void* result;
	char left_child[100];
	int offset=20;
	seek_flag = fseek(pFile,offset,SEEK_SET);
	result=fgets(left_child,100,pFile);
	
	printf("The read string is %s\n",(char*)result+24);
	*/

	fclose(pFile);
	return 0;
}


int find_word(char* word, FILE* pFile){

	int seek_flag;
	int block_offset=4;
	int leftchild_offset;
	int rightchild_offset;
	char buffer[1000];
	//void* result=NULL;
	int result=0;
	void* garbage;
	int strcmp_result;
	int size_fread;

	do{

		seek_flag = fseek(pFile,block_offset,SEEK_SET);
		size_fread = fread(&leftchild_offset,4,1,pFile);
		size_fread = fread(&rightchild_offset,4,1,pFile);

		seek_flag = fseek(pFile,8,SEEK_CUR);
		garbage=fgets(buffer,sizeof(buffer),pFile);
		strcmp_result=strcmp(buffer,word);
		
		if(!strcmp_result){
			result=block_offset;
			break;
		}
		block_offset = strcmp_result<0 ? rightchild_offset: leftchild_offset;			

	}while(block_offset!=0);


	return result;
}


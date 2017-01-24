#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct Sentence
{
	char ** array;
	int length;
}Sentence;

void parseString(char * string, Sentence* sen_ptr)
{
	if (string == NULL)
	{
		perror("The string to parse is NULL");
		return;
	}
	int length = 4;
	char ** result = malloc(length*sizeof(char*));
	//int number = 0;

	char * token;
	char * temp; 

	// find number of sentences
	int number_sentences=0;
	char* pch_ch = strchr(string,'.');
	while (pch_ch!=NULL){
		number_sentences++;
		pch_ch = strchr(pch_ch+1,'.');
	}
	// put sentences to mytemp
	char* mytemp[number_sentences];
	char * mytoken;
 	mytoken = strtok(string, ".");
	int counter=0;
	for (;counter<number_sentences;counter++){
		mytemp[counter]= (char*) malloc (sizeof(char)*(strlen(mytoken))+1);
		strcpy(mytemp[counter],mytoken);
		mytoken = strtok(NULL,".");
	}	
	// condense each sentences by getting rid of the white space
	for (counter=0;counter<number_sentences;counter++){
		temp = malloc(strlen(mytemp[counter])+1);
		strcpy(temp,mytemp[counter]);
		result[counter] = temp;	

		if (counter == length)
		{
			length += length;
			result = realloc(result,length*sizeof(char*));
		}

		char * replace = calloc(1,strlen(result[counter])+1); 
		if ((token = strtok(result[counter]," ")) != NULL )
			replace = strcat(replace,token);
		while( (token = strtok(NULL," ")) != NULL)
			replace = strcat(replace,token);
		free(result[counter]);
		free(mytemp[counter]);
		result[counter] = replace;
	}
	//second bug is in here
	/*if ( (token = strtok(string, ".")) != NULL)
	{
		temp = malloc(strlen(token)+1);
		strcpy(temp,token);
		result[number] = temp;	
		

		char * replace = calloc(1,strlen(result[number])+1); 
		if ((token = strtok(result[number]," ")) != NULL )
			replace = strcat(replace,token);
		while( (token = strtok(NULL," ")) != NULL)
			replace = strcat(replace,token);
		free(result[number]);
		result[number] = replace;
		number++;
	}

	while( (token = strtok(NULL, ".")) != NULL ){
		//copy the string from buffer 
		temp = malloc(strlen(token)+1);
		strcpy(temp,token);
		result[number] = temp;

		//Expand the array if necessary 
		
		if (number == length)
		{
			length += length;
			result = realloc(result,length*sizeof(char*));
		}

		char * replace = calloc(1,strlen(result[number])+1); 
		if ((token = strtok(result[number]," ")) != NULL )
			replace = strcat(replace,token);
		while( (token = strtok(NULL," ")) != NULL)
			replace = strcat(replace,token);
		free(result[number]);
		result[number] = replace;
		number++;
	}
	*/
	sen_ptr->array = result;
	sen_ptr->length = counter;
}



int main()
{

	FILE * fptr = fopen("./getline.txt","r");

	//parameters for getline 
	ssize_t read;
	char* lineptr = NULL;
	size_t num = 0;

	//allocate an array of struct sentence
	int sentence_length = 1;
	Sentence ** sentences = malloc( sentence_length*sizeof(Sentence *) );
	int sentence_read = 0;
	char* temp;
	while( (read = getline(&lineptr, &num,fptr)) != -1){
		
		//copy the string from buffer 
		temp = malloc(strlen(lineptr)+1);
		strcpy(temp,lineptr);
		sentences[sentence_read] = malloc(sizeof(Sentence));
		parseString(temp,sentences[sentence_read]);
		free(temp);

		//Expand the array if necessary 
		sentence_read++;
		if (sentence_read == sentence_length)
		{
			sentence_length += sentence_length;
			sentences = realloc(sentences,sentence_length*sizeof(Sentence*));
		}

	}

	//Free the memory in here
	for (int i = 0; i < sentence_read; ++i)
	{
		printf("%d\n",i );
		for (int j = 0; j < sentences[i]->length; ++j)
		{
			printf("%s\n",sentences[i]->array[j]);
			free(sentences[i]->array[j]);	
		}
		free(sentences[i]->array);
		free(sentences[i]);
	}
	free(sentences);

	return 0;
}

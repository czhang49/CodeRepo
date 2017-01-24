#include "camelCaser.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
/*
 * Converts a each sentence in a string of multiple sentences to camelCase.
 *
 * @param   string  A string adhering to the above description.
 * @return          An array of strings, each element of which is a sentence in camelCase.
 *                  Caller is expected to free the returned array of strings.
 *                  Returns NULL if parameter is NULL.
 */
extern uint32_t Num_string =256;
extern uint32_t Size_string = 1024;
char ** camel_caser(char * string) {

    uint32_t i,j,k;      

    char ** String_array= (char**) malloc(Num_string*sizeof(char*));
    char* pch_sentence;
    char sentence[Size_string]; 
    char* pch_word; 
    char word[Size_string];
    char conti_sentence[Size_string];// Because conti_sentence is used in strcat, so there needs to be an initial \0.
    conti_sentence[0]='\0';

    // allocate string
    for (i=0;i<Num_string;i++){

    	String_array[i] = (char*) malloc (Size_string*sizeof(char));

    }
    
    // word processing
    i=0;
    pch_sentence = strtok(string,".");

    while(pch_sentence!=NULL){
  	//printf("This is line %d\n",__LINE__);
	if (strlen(pch_sentence)>=Size_string)
	    perror("This sentence is too long");
	if (i>=Num_string)
	    perror("There are too many sentences");
	// get each sentence
	
	strcpy(String_array[i], pch_sentence);
	pch_sentence = strtok (NULL,".");
	
	i=i+1;
    }

    for (k=0;k<i;k++){
	// get each word
	pch_word = strtok(String_array[k]," ");
	while(pch_word!=NULL){
	    // assign pch_word to interim word
	    strcpy(word,pch_word);
	    // do word case transform
	    if isupper(word[0])
		word[0]=tolower(word[0]);
	    else 
		word[0]=toupper(word[0]);

	    for(j=1;j<strlen(word);j++){

	    	word[j]=tolower(word[j]);
	    }
	    // append the word to conti_sentence
	    strcat(conti_sentence,word);// not sure for now if strcat stops at \0.
 	    //printf("%s\n",conti_sentence);
	    pch_word = strtok(NULL," ");
	}
	
	strcpy(String_array[k],conti_sentence);
	conti_sentence[0]='\0';
	
	printf("%s\n",String_array[k]);

    }

    return String_array;
}

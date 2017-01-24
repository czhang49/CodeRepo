// Shell
// CS 241 Fall 2015
#define _GNU_SOURCE
#include "vector.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


Vector *Vector_create(){ 

	// can allocate some capacity at the beginning
	Vector* new_vec = (Vector*) malloc(sizeof(Vector));
	new_vec->array = (char**) malloc (2*sizeof(char*)) ;
	new_vec->size = 0;
	new_vec->capacity = 2;


	return new_vec; 
}

void Vector_destroy(Vector *vtr){
	
	// note this three levels of free
	for(size_t i=0;i<vtr->size;i++){
		free(vtr->array[i]);
	}
	free(vtr->array);
	free(vtr);
}

int Vector_size(Vector *vtr) { 

	return vtr->size; 
}

void Vector_resize(Vector *vtr, size_t new_size) {
	
	if(new_size<vtr->size){
		
		for( size_t i = new_size;i<vtr->size;i++){
			free(vtr->array[i]); // starting from the index = newsize, all freed
		}
		vtr->size=new_size;

	}else if(vtr->size < new_size && new_size<=vtr->capacity){

		for (size_t i=vtr->size;i<new_size;i++){
			vtr->array[i] = NULL; // starting from index = vtr->size to new_size -1 , all NULL;
		}
		vtr->size = new_size;

	}else if( vtr->capacity < new_size){
		
		vtr->capacity = nextpowtwo(new_size);// not the size of the realloc here
		vtr->array = (char**) realloc (vtr->array,(vtr->capacity)*sizeof(char*));
		
		for (size_t i=vtr->size;i<new_size;i++){
			vtr->array[i] = NULL;	// starting from index = vtr->size to new_size -1 , all NULL;
		}
		vtr->size = new_size;		

	}

	return;	
}

void Vector_set(Vector *vtr, size_t index, const char *str){

	if (index+1<=vtr->size){
		free(vtr->array[index]);	// if index<= vtr->size -1, then first free and then allocate new string;
		vtr->array[index] = (char*) malloc(strlen(str)+1);
		strcpy(vtr->array[index],str);
	}else{
		Vector_resize(vtr,index+1); // the size and capacity of the vector is set in the resize function
		// since array[index] currently has nothing in there, no need to free array[index]
		vtr->array[index] = (char*) malloc(strlen(str)+1);
		strcpy(vtr->array[index],str);
	}
}

const char *Vector_get(Vector *vtr, size_t index) { 

	if (vtr->size< index+1){
		perror("The index is out of bound\n");
		return NULL;
	}
	
	return vtr->array[index];
}

void Vector_append(Vector *vtr, const char *str) {
	// Call vector set, index  vtr->size, string is str;
	Vector_set(vtr,vtr->size,str);
}

size_t nextpowtwo(size_t val){
	
	size_t count=0;
	while (val!=0){
		val>>=1;
		count++;
	}
	
	return pow(2,count);

}

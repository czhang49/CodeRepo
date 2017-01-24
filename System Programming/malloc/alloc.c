// Malloc
// CS 241 Fall 2015
// University of Illinois at Urbana-Champaign
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

typedef struct meta_data_t {
	
	void* address;
	int free;	
	size_t size_this;
	size_t size_prev;
	struct meta_data_t *next;
} meta_data_t ;

static meta_data_t* head = NULL;
static meta_data_t* tail = NULL;
static meta_data_t* last_found_pt=NULL;
static size_t free_size=0;
static size_t free_counter=0;

void* alloc_newmeta_and_size(size_t,size_t);
void divide_chosen(meta_data_t*, size_t);
void aggregate_next(meta_data_t*);
void aggregate_prev(meta_data_t*);

/**
 * Allocate space for array in memory
 *
 * Allocates a block of memory for an array of num elements, each of them size
 * bytes long, and initializes all its bits to zero. The effective result is
 * the allocation of an zero-initialized memory block of (num * size) bytes.
 *
 * @param num
 *    Number of elements to be allocated.
 * @param size
 *    Size of elements.
 *
 * @return
 *    A pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory, a
 *    NULL pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/calloc/
 */
void *calloc(size_t num, size_t size) { 

	void* ptr = malloc(num*size);

	return memset(ptr,0,num*size); 
}

/**
 * Allocate memory block
 *
 * Allocates a block of size bytes of memory, returning a pointer to the
 * beginning of the block.  The content of the newly allocated block of
 * memory is not initialized, remaining with indeterminate values.
 *
 * @param size
 *    Size of the memory block, in bytes.
 *
 * @return
 *    On success, a pointer to the memory block allocated by the function.
 *
 *    The type of this pointer is always void*, which can be cast to the
 *    desired type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a null pointer is returned.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/malloc/
 */
void *malloc(size_t size) { 

	meta_data_t* chosen = NULL;
	//printf("I'm at alloc.c line %d, before allocation, need size is %lu, free size is :%lu, free counter is :%lu \n", __LINE__, size,free_size,free_counter);

	// this deal with the first allocation
	if (head == NULL){
		head = alloc_newmeta_and_size(0,size);
		if (head == NULL){
			perror("head allocation unsuccessful\n");
			return NULL;
		}
		//printf("I'm at line %d, first pointer address is %p\n",__LINE__, head);
		chosen = head;
		tail = head;
		return chosen->address;
	}

	meta_data_t* p = head; 
	//printf("I'm at alloc.c line %d\n",__LINE__);
	//wall through existing list  (free_size/free_counter)>= 1
	if (free_counter!=0 && 1){
		//printf("I'm at alloc.c line %d, about to look for reusable block\n",__LINE__);
		/*meta_data_t* temp = head;
		while(temp!=NULL){
		printf("I'm at alloc.c line %d, block size is :%lu, block free flag is :%d \n", __LINE__, temp->size_this,temp->free);
		temp = temp->next;
		}*/
		int counter=0;
		while(p){
			// this counter reduced running time of test 9  by 10 sec !!! counter>1000 break;
			counter+=1;
			if (counter>1000)
				p = last_found_pt;
			if (counter>3000)
				break;
			if (p->free==1 && size <= p->size_this){
				chosen = p;
				last_found_pt = p;
				break;
				//printf("I'm at line %d, the found reuse ptr address is %p, free flag is %d\n", __LINE__, chosen, chosen->free);
			}
			p = p->next;
		}
	}
	//printf("I'm at alloc.c line %d, after finding reusable block \n",__LINE__);
	// if no good is found, allocate new and return address.
	if (!chosen){
		//printf("I'm at alloc.c line %d, about to allocate new block\n",__LINE__);
		
		chosen = alloc_newmeta_and_size(tail->size_this,size);
		//printf("I'm at alloc.c line %d\n",__LINE__);
		tail->next = chosen;
		tail = chosen;
		return chosen->address;
	}
	//printf("I'm at alloc.c line %d, now the chosen is from reusable block \n",__LINE__);
	// if found, then change free flag and see if can divide the memory junk		
	chosen->free=0;
	free_counter--;
	//printf("I'm at alloc.c line %d, before dividing chosen reusable block,  chosen size is %lu, need size is :%lu\n", __LINE__, chosen->size_this,size);
	if ((chosen->size_this) > (size+sizeof(struct meta_data_t))){
		free_counter++;
		divide_chosen(chosen,size);
		//printf("I'm at alloc.c line %d, after dividing reusalbe block, need size is %lu, free size is :%lu, free counter is :%lu \n", __LINE__, size,free_size,free_counter);
	}	
	free_size = free_size - chosen->size_this ;
	
	//printf("I'm at alloc.c line %d, after all the malloc operations\n",__LINE__);
	return chosen->address; 
}

void* alloc_newmeta_and_size(size_t size_prev,size_t size_this){
	// can use a tail optimization to aggregate

	void* localptr = sbrk(0);
	if (sbrk(sizeof(struct meta_data_t)+size_this) == (void*) -1){
		return NULL;
	}

	((meta_data_t*) localptr)-> address = (meta_data_t*) ((char*) localptr + sizeof(struct meta_data_t));
	((meta_data_t*) localptr)-> size_this = size_this;
	((meta_data_t*) localptr)-> size_prev = size_prev;
	((meta_data_t*) localptr)-> next = NULL;
	((meta_data_t*) localptr)-> free = 0; // new newly allocated stuff is used right away, so the free flag is set to 0.

	//printf("I'm at line %d, the new allocated ptr address is %p\n", __LINE__, localptr);
	return localptr;
}


void divide_chosen(meta_data_t* chosen, size_t chosen_size){
	//chosen_size is the needed size for chosen, chosen->size_this is the fragmentation size of chosen that needs to be divided.

	meta_data_t* splitted = (meta_data_t*) ((char*) chosen + sizeof(struct meta_data_t) + chosen_size) ;

	splitted->next = chosen->next;
	splitted->address = (meta_data_t*) ((char*)splitted + sizeof(struct meta_data_t));
	splitted->size_prev = chosen_size;
	splitted->size_this = chosen->size_this - chosen_size - sizeof(struct meta_data_t);
	splitted->free = 1;
	if (splitted->next !=NULL){
		splitted->next->size_prev = splitted->size_this;
	}	

	chosen-> next = splitted;
	chosen-> size_this = chosen_size;

	// update the ptr for tail
	if (chosen == tail){
		tail = splitted;
	}
}


/**
 * Deallocate space in memory
 *
 * A block of memory previously allocated using a call to malloc(),
 * calloc() or realloc() is deallocated, making it available again for
 * further allocations.
 *
 * Notice that this function leaves the value of ptr unchanged, hence
 * it still points to the same (now invalid) location, and not to the
 * null pointer.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(),
 *    calloc() or realloc() to be deallocated.  If a null pointer is
 *    passed as argument, no action occurs.
 */
void free(void *ptr) {
  // "If a null pointer is passed as argument, no action occurs."
	if (!ptr)
		return;


	meta_data_t *freeptr =(meta_data_t*) ((char*) ptr - sizeof(struct meta_data_t));
	free_counter++;
	free_size = free_size + freeptr->size_this + sizeof(struct meta_data_t);

	//printf("I'm at alloc.c line %d, after simple free, free size is :%lu, free counter is :%lu \n", __LINE__, free_size,free_counter);
	//printf("I'm at alloc.c line %d\n",__LINE__);
	freeptr->free = 1;
	//printf("I'm at alloc.c line %d\n",__LINE__);
	// if next junk is free, aggregate
	if (freeptr->next !=NULL && freeptr->next->free ==1){
		free_counter--;
		aggregate_next(freeptr); // note for the tail ptr.
		//printf("I'm at alloc.c line %d, after aggregate next free size is :%lu, free counter is :%lu \n", __LINE__, free_size,free_counter);
	}
	//printf("I'm at alloc.c line %d\n",__LINE__);
	// if previous junk is free, aggregate.
	if(freeptr->size_prev!=0 ){
		//printf("I'm at alloc.c line %d, the prev size is %lu, this size is %lu, my address is %p\n",__LINE__, freeptr->size_prev, freeptr->size_this, freeptr);
		// note the ptr arithmic needs to be cast into the correct type.
		if ( ((meta_data_t*)((((char*) freeptr- (freeptr->size_prev)) - sizeof(struct meta_data_t) )))->free ==1){
			//printf("I'm at alloc.c line %d\n",__LINE__);
			free_counter--;
			aggregate_prev(freeptr); // note for the head ptr
			//printf("I'm at alloc.c line %d, after aggregate previous, free size is :%lu, free counter is :%lu \n", __LINE__, free_size,free_counter);
		}
	}

	//printf("I'm at alloc.c line %d, after all the free operations, free size is :%lu, free counter is :%lu \n", __LINE__, free_size,free_counter);
	
	/*meta_data_t* temp = head;
	while(temp!=NULL){
		printf("I'm at alloc.c line %d, block size is :%lu, block free flag is :%d \n", __LINE__, temp->size_this,temp->free);
		temp = temp->next;
	}*/
	return;
}

void aggregate_next(meta_data_t* ptr){

	/*meta_data_t* temp = head;
	while(temp!=NULL){
		//printf("I'm at alloc.c line %d, block size is :%lu, block free flag is :%d \n", __LINE__, temp->size_this,temp->free);
		temp = temp->next;
	}*/

	if (tail == ptr->next){
		tail = ptr;
	}
	ptr->size_this = ptr->size_this + ptr->next->size_this + sizeof(struct meta_data_t);
	if (ptr->next->next !=NULL){
		ptr->next->next->size_prev = ptr->size_this;
	}
	ptr->next = ptr->next->next;

	/*temp = head;
	while(temp!=NULL){
		//printf("I'm at alloc.c line %d, block size is :%lu, block free flag is :%d \n", __LINE__, temp->size_this,temp->free);
		temp = temp->next;
	}*/
}

void aggregate_prev(meta_data_t* ptr){

	/*meta_data_t* temp = head;
	while(temp!=NULL){
		printf("I'm at alloc.c line %d, block size is :%lu, block free flag is :%d \n", __LINE__, temp->size_this,temp->free);
		temp = temp->next;
	}*/

	//printf("I'm at alloc.c line %d\n",__LINE__);
	meta_data_t *prev_ptr = (meta_data_t*)((char*)ptr - (ptr->size_prev) - sizeof(struct meta_data_t));
	//printf("I'm at alloc.c line %d\n",__LINE__);
	aggregate_next(prev_ptr);

	/*temp = head;
	while(temp!=NULL){
		printf("I'm at alloc.c line %d, block size is :%lu, block free flag is :%d \n", __LINE__, temp->size_this,temp->free);
		temp = temp->next;
	}*/

}
/**
 * Reallocate memory block
 *
 * The size of the memory block pointed to by the ptr parameter is changed
 * to the size bytes, expanding or reducing the amount of memory available
 * in the block.
 *
 * The function may move the memory block to a new location, in which case
 * the new location is returned. The content of the memory block is preserved
 * up to the lesser of the new and old sizes, even if the block is moved. If
 * the new size is larger, the value of the newly allocated portion is
 * indeterminate.
 *
 * In case that ptr is NULL, the function behaves exactly as malloc, assigning
 * a new block of size bytes and returning a pointer to the beginning of it.
 *
 * In case that the size is 0, the memory previously allocated in ptr is
 * deallocated as if a call to free was made, and a NULL pointer is returned.
 *
 * @param ptr
 *    Pointer to a memory block previously allocated with malloc(), calloc()
 *    or realloc() to be reallocated.
 *
 *    If this is NULL, a new block is allocated and a pointer to it is
 *    returned by the function.
 *
 * @param size
 *    New size for the memory block, in bytes.
 *
 *    If it is 0 and ptr points to an existing block of memory, the memory
 *    block pointed by ptr is deallocated and a NULL pointer is returned.
 *
 * @return
 *    A pointer to the reallocated memory block, which may be either the
 *    same as the ptr argument or a new location.
 *
 *    The type of this pointer is void*, which can be cast to the desired
 *    type of data pointer in order to be dereferenceable.
 *
 *    If the function failed to allocate the requested block of memory,
 *    a NULL pointer is returned, and the memory block pointed to by
 *    argument ptr is left unchanged.
 *
 * @see http://www.cplusplus.com/reference/clibrary/cstdlib/realloc/
 */
void *realloc(void *ptr, size_t size) {
  // "In case that ptr is NULL, the function behaves exactly as malloc()"
	if (!ptr)
		return malloc(size);

  // "In case that the size is 0, the memory previously allocated in ptr
  //  is deallocated as if a call to free() was made, and a NULL pointer
  //  is returned."
	if (!size) {
		free(ptr);
		return NULL;
	}

	meta_data_t *ptr_meta = (meta_data_t*) ((char*) ptr - sizeof(struct meta_data_t));
/*	if (ptr_meta->free==1){
		perror("Trying to realloc a freed pointer\n");
		return NULL;
	}
*/
	size_t copy_size = ((ptr_meta -> size_this) > size) ? size : (ptr_meta -> size_this) ;

	if (ptr_meta ->size_this >= size){
		if (ptr_meta ->size_this > size + sizeof(struct meta_data_t)){
			free_counter++;
			free_size = free_size + ptr_meta->size_this - size;
			divide_chosen(ptr_meta,size);
			free_counter++;
		}
		return ptr;
	}

	if (ptr==tail){
		void* extra_tail_ptr = sbrk(size-(ptr_meta->size_this));
		if (extra_tail_ptr == (void*) -1){
			perror("Realloc New boundary failded\n");
			return NULL;
		}

		ptr_meta-> size_this = size;
		//printf("I'm at line %d, the new allocated ptr address is %p\n", __LINE__, localptr);
		return ptr;
	}

	bool next_avi=0;
	bool prev_avi=0;
	if (ptr_meta->next !=NULL && ptr_meta->next->free ==1){
		next_avi=1;
		if ((ptr_meta->size_this + ptr_meta->next->size_this + sizeof(struct meta_data_t)) >= size){
			free_size = free_size - ptr_meta->next->size_this;
			free_counter--;			
			aggregate_next(ptr_meta);
					
			if ((ptr_meta->size_this) > (size+sizeof(struct meta_data_t))){
				free_counter++;	
				free_size = free_size + ptr_meta->size_this - size;
				divide_chosen(ptr_meta,size);
				
				//printf("I'm at alloc.c line %d, after dividing reusalbe block, need size is %lu, free size is :%lu, free counter is :%lu \n", __LINE__, size,free_size,free_counter);
			}
			return ptr;
		}
	}

	meta_data_t* ptr_prev = NULL;
	if (ptr_meta->size_prev!=0 && ((meta_data_t*)((((char*) ptr_meta- (ptr_meta->size_prev)) - sizeof(struct meta_data_t) )))->free ==1){
		prev_avi=1;
		ptr_prev =  (meta_data_t*)((((char*) ptr_meta- (ptr_meta->size_prev)) - sizeof(struct meta_data_t) ));
		if ((size<= ptr_prev->size_this + ptr_meta->size_this + sizeof(struct meta_data_t))){
			//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
			free_counter--;
			free_size = free_size - ptr_prev->size_this;
			aggregate_prev(ptr_meta);
			ptr_prev->free =0;
			size_t address_diff = ptr_meta->address - ptr_prev->address;
			//printf("I'm at line %d, realloc and aggregate prev is called, address diff %lu is and copy size is %lu, size after aggregation is %lu\n",__LINE__, address_diff, copy_size, ptr_prev->size_this);
			if (address_diff < copy_size){
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
				void* ptr_meta_address = ptr_meta->address;
				memcpy(ptr_prev->address , ptr_meta->address, address_diff );
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
				memcpy((void*)((char*)ptr_prev->address + address_diff) , (void*)((char*)ptr_meta_address + address_diff), copy_size-address_diff);
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
			}else{
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
				memcpy(ptr_prev->address , ptr_meta->address, copy_size );
			}
			if ((ptr_prev->size_this) > (size+sizeof(struct meta_data_t))){
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
				free_counter++;	
				free_size = free_size + ptr_prev->size_this - size;
				divide_chosen(ptr_prev,size);
				//printf("I'm at alloc.c line %d, after dividing reusalbe block, need size is %lu, free size is :%lu, free counter is :%lu \n", __LINE__, size,free_size,free_counter);
			}
			//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
			return ptr_prev->address;
		}
		
	} 

	if (next_avi && prev_avi){
		if (ptr_prev->size_this+ ptr_meta->next->size_this + ptr_meta->size_this + 2* sizeof(struct meta_data_t)>=size){
			free_size = free_size - ptr_meta->next->size_this;
			free_counter--;	
			aggregate_next(ptr_meta);
			//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
			free_counter--;
			free_size = free_size - ptr_prev->size_this;
			aggregate_prev(ptr_meta);
			ptr_prev->free =0;
			free_counter--;
			size_t address_diff = ptr_meta->address - ptr_prev->address;
			//printf("I'm at line %d, realloc and aggregate prev is called, address diff %lu is and copy size is %lu, size after aggregation is %lu\n",__LINE__, address_diff, copy_size, ptr_prev->size_this);
			if (address_diff < copy_size){
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
				void* ptr_meta_address = ptr_meta->address;
				memcpy(ptr_prev->address , ptr_meta->address, address_diff );
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
				memcpy((void*)((char*)ptr_prev->address + address_diff) , (void*)((char*)ptr_meta_address + address_diff), copy_size-address_diff);
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
			}else{
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
				memcpy(ptr_prev->address , ptr_meta->address, copy_size );
			}
			if ((ptr_prev->size_this) > (size+sizeof(struct meta_data_t))){
				//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
				free_counter++;	
				free_size = free_size + ptr_prev->size_this - size;	
				divide_chosen(ptr_prev,size);
				//printf("I'm at alloc.c line %d, after dividing reusalbe block, need size is %lu, free size is :%lu, free counter is :%lu \n", __LINE__, size,free_size,free_counter);
			}
			//printf("I'm at line %d, realloc and aggregate prev is called\n",__LINE__);
			return ptr_prev->address;
			
		}
	}

	
	if (tail->free==1){
		void* extra_tail_ptr = sbrk(size-(tail->size_this));
		if (extra_tail_ptr == (void*) -1){
			perror("Realloc New boundary failded\n");
			return NULL;
		}

		tail->free=0;
		tail-> size_this = size;
		memcpy(tail->address, ptr, copy_size);
		//printf("I'm at line %d, the new allocated ptr address is %p\n", __LINE__, localptr);
		free(ptr);
		return tail->address;
	}


	void *localptr = malloc (size);
	meta_data_t *localptr_meta = (meta_data_t*) ((char*) localptr - sizeof(struct meta_data_t));

	//printf("I'm at alloc.c line %d, new ptr is %p, new size is %lu, needed size is %lu, prev size is %lu\n", __LINE__, localptr, localptr_meta->size_this, size, ptr_meta->size_this);
	memcpy(localptr , ptr, copy_size );

	//printf("I'm at alloc.c line %d\n", __LINE__);

	free (ptr);

	return localptr;
}

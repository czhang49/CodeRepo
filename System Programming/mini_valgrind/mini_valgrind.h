#ifndef MINI_VALGRIND_H
#define MINI_VALGRIND_H

#define MAX_FILENAME_LENGTH 128
#define malloc(size) mini_malloc(size, __FILE__, __LINE__)
#define free(ptr) mini_free(ptr)

typedef struct _meta_data
{
    // address of the memory allocated by malloc
    void *address;
    // size of the memory allocated by malloc
    size_t size;
    size_t line_num;
    char file_name[MAX_FILENAME_LENGTH];
    struct _meta_data *next;
    struct _meta_data *prev;
    // Make this a doubly linked list if you want :)
    // 
} meta_data;

void destroy();

void *mini_malloc(size_t size, const char *file, size_t line);
void mini_free(void *ptr);

void insert_meta_data(meta_data *md, size_t size, const char *file, size_t line);
void remove_meta_data(void *ptr);
void print_report();

#endif

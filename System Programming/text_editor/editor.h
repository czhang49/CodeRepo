#ifndef EDITOR_H
#define EDITOR_H

/**
 * The following is an example structure for your program. However, you do not
 * have to follow this structure as long as you have a main() that starts your
 * editor and does as the lab docs specify.
 */

typedef struct  {
  // Put any variables your data structure here
	int line_num;
	char* sentence;
} data;



/**
 * This function gets the filename from argc & argv (it's a one liner).
 * @return NULL if there is no filename
 */
char *get_filename(int argc, char *argv[]);

/**
 * Mallocs your data structure and loads the file content if the file exists.
 * @param data_ptr is the pointer to your data struct
 * @param filename is the name of the file to load (if the filename is NULL, then
 *        there is no file to load)
 */
void init(data** data_ptr_ptr, char *filename);

/**
 * Prints our the content of data_ptr.
 * If line is 0, then print all the lines.
 * @param data_ptr is the pointer to your data struct
 * @param line is line number you should print out
 */
void display(data *data_ptr, int line);

/**
 * Overwrites a line in your data structure with a string.
 * @param data_ptr is the pointer to your data struct
 * @param line is line number you should overwrite
 * @param string is the content you should use to overwrite the line
 */
void overwrite(data** data_ptr_ptr, int line, char *string);

/**
 * Appends a line in your data structure with a string.
 * @param data_ptr is the pointer to your data struct
 * @param line is line number you should append
 * @param string is the content you should use to append the line
 */
//void append(data *data_ptr, int line, char *string);

/**
 * Finds all the lines in your data structure containing the search term.
 * @param data_ptr is the pointer to your data struct
 * @param search_term is the string to search for
 */
void find(data *data_ptr, char *search_term);

/**
 * Saves your data structure to the file named filename.
 * Only save the raw text (no line numbers).
 * @param data_ptr is the pointer to your data struct
 * @param filename is the name of the file to save to
 */
void save(data *data_ptr, char *filename);

/**
 * Frees your data structure.
 * @param data_ptr is the pointer to your data struct
 */
void destroy(data *data_ptr);

int nextpowtwo(int line);

#endif // #ifndef EDITOR_H

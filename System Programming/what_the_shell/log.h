// Shell
// CS 241 Fall 2015
#ifndef __LOG_H_
#define __LOG_H_
#include "vector.h"
#include <stdio.h>

/* All the Log functions should not rely on the passed in strings existing after
 * the function returns. */
typedef struct {
  Vector *vtr;
} Log;

/** Creates and returns a Log
 *  If the filename is not null then it reads
 *  all the commands from the file into the log.
 *  Otherwise attempt to open the file and load it into your log.
 *  If you can not read from the file for whatever reason, then create an empty
 *  log and move on.
 *  We guarantee that if the file exists and is readable then it is either empty
 *  or made by your Log_save().
 */
Log *Log_create(const char *filename);

/** Serializes all the contents of log to a file.
 *  If you can not write to the file then return 1.
 *  Otherwise return 0.
 */
int Log_save(Log *log, const char *filename);

/* Frees all the memory used by log and the log itself. */
void Log_destroy(Log *log);

/* Adds a command to the log at the end of its history. */
void Log_add_command(Log *log, const char *command);

/* Returns the most recently added command
 * that begins with the given prefix.
 */
const char *Log_reverse_search(Log *log, const char *prefix);

/* Gets the command at index.
 * Note that an index higher than the latest command
 * is not valid and you should return NULL.
 * Commands are zero indexed.
 */
const char *Log_get_command(Log *log, size_t index);

/* Returns a printable version of the history.
 * For each command append the line number, then a tab, then the command and
 * finally a new line
 * to the return string in the order they were added in.
 * (this includes the last command).
 * The caller is responsible for freeing the return string.
 */
char *Log_get_printable_history(Log *log);

#endif

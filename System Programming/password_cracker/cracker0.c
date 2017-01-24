/*
  Password Cracker MP

  Version 0 - single threaded
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

void crackPassword(const char *username, const char *target_hash,
                   const char *partial_pw);

int main(int argc, char **argv) {

  if (argc != 1) {
    fprintf(stderr, "\n  cracker0 < password_file.txt\n\n");
    return 1;
  }
	
  // this is very nice, use the standard in for file processing.
  FILE *inf = stdin;

  size_t buf_len = 0;
  char *line = NULL;
  char username[9], hash[14], password_prefix[9];
  double start_time = getTime();

  while (getline(&line, &buf_len, inf) != -1) {
    sscanf(line, "%8s %13s %8s", username, hash, password_prefix);
    crackPassword(username, hash, password_prefix);
  }

  double elapsed = getTime() - start_time;
  printf("Total time: %.2f seconds.\n", elapsed);

  free(line);

  return 0;
}

/* partial_pw will be a a string like "xyz....." where the first part
   is lowercase letters, then some number of periods. The letters
   are part of the password that is known, and the periods represent
   the unknown letters.
*/
void crackPassword(const char *username, const char *target_hash,
                   const char *partial_pw) {

  assert(strlen(username) <= 8);
  assert(strlen(target_hash) == 13);
  assert(strlen(partial_pw) <= 8);

  double start_time = getTime();

  char test_pw[9];
  strcpy(test_pw, partial_pw);

  // unknown_chars will point to the part of the password that is unknown
  char *unknown_chars = test_pw + getPrefixLength(test_pw);
  setStringPosition(unknown_chars, 0);

  int found = 0;
  int hash_count = 0;
  struct crypt_data cdata;
  cdata.initialized = 0;

  do {
    const char *hashed = crypt_r(test_pw, "xx", &cdata);

    // uncomment this if you want to see the hash function doing its thing
    // printf("%s -> %s\n", test_pw, hashed);

    hash_count++;
    found = !strcmp(hashed, target_hash);
  } while (!found && incrementString(unknown_chars));

  double elapsed = getTime() - start_time;

  if (found) {
    printf("Password for %s is %s (%d hashes in %.2f seconds)\n", username,
           test_pw, hash_count, elapsed);
  } else {
    printf("Password for %s not found (%d hashes in %.2f seconds)\n", username,
           hash_count, elapsed);
  }
}

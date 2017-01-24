#include "cracker2.h"

#define DEFAULT_THREAD_COUNT 4


void printHelp() {
  fprintf(stderr,
          "\n  cracker2 [thread_count] < <password_file>\n\n");
  exit(1);
}

int main(int argc, char **argv) {
  int thread_count = DEFAULT_THREAD_COUNT;

  if (argc > 2)
    printHelp();

  if (argc > 1) {
    if (1 != sscanf(argv[1], "%d", &thread_count) || thread_count < 1)
      printHelp();
  }

  // capture ctrl-c
  signal(SIGINT, threadStatusPrint);

  int ret = start(thread_count);

  return ret;
}

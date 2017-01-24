#include "cracker1.h"

#define DEFAULT_THREAD_COUNT 4

void printHelp() {
  fprintf(stderr, "\n  cracker1 [thread_count] < <password_file>\n\n");
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

  double start_time = getTime();
  double start_cpu_time = getCPUTime();

  int ret = start(thread_count);

  double elapsed = getTime() - start_time;
  double total_cpu_time = getCPUTime() - start_cpu_time;

  printf("Total time: %.2f seconds.\n", elapsed);
  printf("Total CPU time: %.2f seconds.\n", total_cpu_time);
  printf("CPU usage: %.2fx\n", total_cpu_time / elapsed);

  return ret;
}

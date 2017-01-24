#include <stdio.h>
#include <unistd.h>
#include "common.h"

/*
  Demonstrate the difference between CPU and 'wall clock' time.
*/

int main(int argc, char **argv) {
  double start_wall_time = getTime();
  double start_cpu_time = getThreadCPUTime();
  sleep(1);
  double elapsed_wall = getTime() - start_wall_time;
  double elapsed_cpu = getThreadCPUTime() - start_cpu_time;
  printf("sleep(1): %.2f seconds wall time, %.2f seconds CPU time\n",
         elapsed_wall, elapsed_cpu);

  start_wall_time = getTime();
  start_cpu_time = getThreadCPUTime();

  // busy work
  int i;
  double x = argc < 0 ? 1.9 : 2.0;
  for (i = 0; i < 50000000; i++)
    x = (x + 6) * .25;
  
  // convince the compiler not to optimize out the loop
  if (x != 2.0)
    printf("Shouldn't happen.\n");

  elapsed_wall = getTime() - start_wall_time;
  elapsed_cpu = getThreadCPUTime() - start_cpu_time;
  printf("cpu work: %.2f seconds wall time, %.2f seconds CPU time\n",
         elapsed_wall, elapsed_cpu);

  return 0;
}

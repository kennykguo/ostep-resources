#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>

int main(int argc, char *argv[]) {

  // Pin the CPU
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(0, &cpuset);
  if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) != 0) {
      perror("sched_setaffinity failed");
      return 1;
  }

  // First argument will be the # of pages, second is the number of trials
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <page size> <number of trials>\n", argv[0]);
    return 1;
  }
  int PAGESIZE = atoi(argv[1]);
  int num_trials = atoi(argv[2]);
  int TOTAL_MEMORY = 10000; // Some randomly set amount of random memory

  int NUMPAGES = TOTAL_MEMORY / PAGESIZE;

  // Initialize array
  int a[TOTAL_MEMORY]; 
  for (int i = 0; i < TOTAL_MEMORY / sizeof(int); i++) {
    a[i] = 0;
  }

  clock_t start = clock();
  // Prevent optimization
  volatile int result = 0; 
  for (int i = 0; i < num_trials; ++i) {
    int jump = PAGESIZE / sizeof(int);
    for (int j = 0; j < NUMPAGES * jump; j += jump) {
      a[j] += 1;
      result += a[j]; // Use the result to prevent optimization
    }
  }

  clock_t end = clock();
  double time_elapsed_in_seconds = (end - start) / (double)CLOCKS_PER_SEC;
  
  // Output the time to stdout in a format the bash script can parse
  printf("Time elapsed: %f\n", time_elapsed_in_seconds);
  return 0;
}

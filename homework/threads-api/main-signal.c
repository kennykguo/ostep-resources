#include <stdio.h>
#include <pthread.h>
#include "common_threads.h"
pthread_mutex_t lock; // Declare mutex

int done = 0;

void* worker(void* arg) {
    printf("this should print first\n");
     // Initialize the mutex
    pthread_mutex_lock(&lock);
    done = 1;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&lock, NULL);
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    while (done == 0);  // No lock needed here
    printf("this should print last\n");
    return 0;
}

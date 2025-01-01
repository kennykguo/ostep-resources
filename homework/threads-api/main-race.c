#include <stdio.h>
#include <pthread.h>
#include "common_threads.h"

int balance = 0; // Global variable
pthread_mutex_t lock; // Declare mutex


void* worker(void* arg) {
    pthread_mutex_lock(&lock);  // Lock before accessing shared resource
    balance++;                 // Protected access
    pthread_mutex_unlock(&lock); // Unlock after access
    return NULL;
}


int main(int argc, char *argv[]) {
    pthread_t p;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    Pthread_create(&p, NULL, worker, NULL);

    pthread_mutex_lock(&lock);
    balance++; // unprotected access
    pthread_mutex_unlock(&lock);

    Pthread_join(p, NULL);

     // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}

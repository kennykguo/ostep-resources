#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // Required for getpid() and usleep()

int main() {
    int ok[100000];
    printf("Process ID: %d\n", getpid());

    while (true) {
        for (int i = 0; i < 1000; i++) {
            ok[i] = 1;  // Simulate some operation
        }
        usleep(100000);  // Pause for 100ms to reduce CPU usage
    }

    return 0;
}

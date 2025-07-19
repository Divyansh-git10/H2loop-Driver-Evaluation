#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    const char *input = "Simulated user write!";
    char output[BUFFER_SIZE];

    // Simulate writing to device
    strncpy(buffer, input, BUFFER_SIZE);
    printf("Written to buffer: %s\n", buffer);

    // Simulate reading from device
    strncpy(output, buffer, BUFFER_SIZE);
    printf("Read from buffer: %s\n", output);

    return 0;
}

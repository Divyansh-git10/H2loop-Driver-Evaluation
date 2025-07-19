#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024
static char device_buffer[BUFFER_SIZE];

int main() {
    printf("Writing to device buffer...\n");
    strncpy(device_buffer, "Hello Device!", BUFFER_SIZE);

    printf("Reading from device buffer...\n");
    printf("%s\n", device_buffer);

    return 0;
}

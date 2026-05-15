#include <stdio.h>
#include "server.h"

int main(void) {
    printf("Selfmade Redis server starting on port %d...\n", DEFAULT_PORT);

    if (start_server(DEFAULT_PORT) != 0) {
        printf("Failed to start server.\n");
        return 1;
    }

    return 0;
}
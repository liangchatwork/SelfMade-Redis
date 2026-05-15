#include <stdio.h>
#include "server.h"
#include "storage.h"

int main(void) {
    storage_init();

    printf("Selfmade Redis server starting on port %d...\n", DEFAULT_PORT);

    if (start_server(DEFAULT_PORT) != 0) {
        printf("Failed to start server.\n");
        return 1;
    }

    return 0;
}
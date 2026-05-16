#include <stdio.h>
#include "server.h"
#include "storage.h"
#include "syscalls.h"

int main(void) {
    storage_init();

    jm_write("Selfmade Redis server starting...\n");

    if (start_server(DEFAULT_PORT) != 0) {
        printf("Failed to start server.\n");
        return 1;
    }

    return 0;
}
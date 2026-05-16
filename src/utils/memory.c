#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "memory.h"

typedef struct MemoryHeader {
    size_t size;
} MemoryHeader;

static size_t total_allocated = 0;
static size_t total_freed = 0;
static size_t current_used = 0;

void *jm_malloc(size_t size) {
    MemoryHeader *header;

    header = (MemoryHeader *)malloc(sizeof(MemoryHeader) + size);

    if (header == NULL) {
        return NULL;
    }

    header->size = size;

    total_allocated += size;
    current_used += size;

    printf("[jm_malloc] allocated %zu bytes | current = %zu | total = %zu\n",
           size,
           current_used,
           total_allocated);

    // 回傳 header 後面的 usable memory
    return (void *)(header + 1);
}

void jm_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // ptr 往前退一格，拿回我們藏的 metadata
    MemoryHeader *header = ((MemoryHeader *)ptr) - 1;

    size_t size = header->size;

    total_freed += size;
    current_used -= size;

    printf("[jm_free] freed %zu bytes | current = %zu | total_freed = %zu\n",
           size,
           current_used,
           total_freed);

    free(header);
}

char *jm_strdup(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = strlen(src) + 1;

    char *copy = (char *)jm_malloc(len);

    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len);

    return copy;
}

size_t memory_get_total_allocated(void) {
    return total_allocated;
}

size_t memory_get_total_freed(void) {
    return total_freed;
}

size_t memory_get_current_used(void) {
    return current_used;
}

void memory_print_stats(void) {
    printf("----- MEMORY STATS -----\n");
    printf("Total allocated: %zu bytes\n", total_allocated);
    printf("Total freed:     %zu bytes\n", total_freed);
    printf("Current used:    %zu bytes\n", current_used);
    printf("------------------------\n");
}
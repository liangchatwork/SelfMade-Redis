#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void *jm_malloc(size_t size);
void jm_free(void *ptr);
char *jm_strdup(const char *src);

size_t memory_get_total_allocated(void);
size_t memory_get_total_freed(void);
size_t memory_get_current_used(void);

void memory_print_stats(void);

#endif
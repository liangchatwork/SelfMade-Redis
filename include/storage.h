#ifndef STORAGE_H
#define STORAGE_H

#define MAX_KEY_SIZE 64
#define MAX_VALUE_SIZE 256
#define MAX_STORE_SIZE 100

void storage_init(void);
int storage_set(const char *key, const char *value);
const char *storage_get(const char *key);
int storage_del(const char *key);
int storage_exists(const char *key);

#endif
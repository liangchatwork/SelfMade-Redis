#include <stdio.h>
#include <string.h>

#include "storage.h"

typedef struct {
    char key[MAX_KEY_SIZE];
    char value[MAX_VALUE_SIZE];
    int used;
} KVPair;

static KVPair store[MAX_STORE_SIZE];

void storage_init(void) {
    for (int i = 0; i < MAX_STORE_SIZE; i++) {
        store[i].used = 0;
    }
}

int storage_set(const char *key, const char *value) {
    // 如果 key 已存在，直接更新 value
    for (int i = 0; i < MAX_STORE_SIZE; i++) {
        if (store[i].used && strcmp(store[i].key, key) == 0) {
            strncpy(store[i].value, value, MAX_VALUE_SIZE - 1);
            store[i].value[MAX_VALUE_SIZE - 1] = '\0';
            return 1;
        }
    }

    // 找空位存新的 key-value
    for (int i = 0; i < MAX_STORE_SIZE; i++) {
        if (!store[i].used) {
            strncpy(store[i].key, key, MAX_KEY_SIZE - 1);
            store[i].key[MAX_KEY_SIZE - 1] = '\0';

            strncpy(store[i].value, value, MAX_VALUE_SIZE - 1);
            store[i].value[MAX_VALUE_SIZE - 1] = '\0';

            store[i].used = 1;
            return 1;
        }
    }

    return 0;
}

const char *storage_get(const char *key) {
    for (int i = 0; i < MAX_STORE_SIZE; i++) {
        if (store[i].used && strcmp(store[i].key, key) == 0) {
            return store[i].value;
        }
    }

    return NULL;
}

int storage_del(const char *key) {
    for (int i = 0; i < MAX_STORE_SIZE; i++) {
        if (store[i].used && strcmp(store[i].key, key) == 0) {
            store[i].used = 0;
            return 1;
        }
    }

    return 0;
}

int storage_exists(const char *key) {
    for (int i = 0; i < MAX_STORE_SIZE; i++) {
        if (store[i].used && strcmp(store[i].key, key) == 0) {
            return 1;
        }
    }

    return 0;
}
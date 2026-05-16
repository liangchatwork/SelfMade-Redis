#ifndef STORAGE_H
#define STORAGE_H

#define HASH_TABLE_SIZE 101

typedef enum {
    TYPE_STRING,
    TYPE_LIST

} ValueType;

// linked list list node
typedef struct ListNode {

    char *value;

    struct ListNode *next;

} ListNode;

// database key-value node
typedef struct KVNode {

    char *key;

    ValueType type;

    void *value;

    struct KVNode *next;

} KVNode;

void storage_init(void);

// string commands
int storage_set(const char *key, const char *value);

const char *storage_get(const char *key);

int storage_del(const char *key);

int storage_exists(const char *key);

int storage_strlen(const char *key);

int storage_append(const char *key, const char *append_value);

int storage_incr(const char *key);

int storage_decr(const char *key);

// list commands
int storage_lpush(const char *key, const char *value);

int storage_rpush(const char *key, const char *value);

char *storage_lpop(const char *key);

char *storage_rpop(const char *key);

void storage_lrange(
    const char *key,
    char *response,
    int response_size
);

void storage_debug_print(void);

void storage_flushall(void);

void storage_keys(char *response, int response_size);

unsigned int hash_function(const char *key);

#endif
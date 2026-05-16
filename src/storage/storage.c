#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "storage.h"
#include "memory.h"

static KVNode *hash_table[HASH_TABLE_SIZE];

unsigned int hash_function(const char *key) {
    unsigned int hash = 0;

    while (*key) {
        hash = (hash * 31) + *key;
        key++;
    }

    return hash % HASH_TABLE_SIZE;
}

void storage_init(void) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

static KVNode *find_node(const char *key) {
    unsigned int index = hash_function(key);
    KVNode *current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

static void free_list(ListNode *head) {
    ListNode *current = head;

    while (current != NULL) {
        ListNode *next = current->next;

        jm_free(current->value);
        jm_free(current);

        current = next;
    }
}

/* =========================
   String Commands
   ========================= */

int storage_set(const char *key, const char *value) {
    unsigned int index = hash_function(key);
    KVNode *current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (current->type != TYPE_STRING) {
                return 0;
            }

            jm_free(current->value);
            current->value = jm_strdup(value);

            return current->value != NULL;
        }

        current = current->next;
    }

    KVNode *new_node = (KVNode *)jm_malloc(sizeof(KVNode));

    if (new_node == NULL) {
        return 0;
    }

    new_node->key = jm_strdup(key);
    new_node->type = TYPE_STRING;
    new_node->value = jm_strdup(value);

    if (new_node->key == NULL || new_node->value == NULL) {
        jm_free(new_node->key);
        jm_free(new_node->value);
        jm_free(new_node);
        return 0;
    }

    new_node->next = hash_table[index];
    hash_table[index] = new_node;

    return 1;
}

const char *storage_get(const char *key) {
    KVNode *node = find_node(key);

    if (node == NULL || node->type != TYPE_STRING) {
        return NULL;
    }

    return (const char *)node->value;
}

int storage_strlen(const char *key) {
    const char *value = storage_get(key);

    if (value == NULL) {
        return -1;
    }

    return (int)strlen(value);
}

int storage_append(const char *key, const char *append_value) {
    KVNode *node = find_node(key);

    if (node == NULL || node->type != TYPE_STRING) {
        return 0;
    }

    char *old_value = (char *)node->value;

    size_t old_len = strlen(old_value);
    size_t append_len = strlen(append_value);
    size_t new_size = old_len + append_len + 1;

    // 不用 realloc，因為目前 jm_malloc 有自己的 metadata header
    char *new_value = (char *)jm_malloc(new_size);

    if (new_value == NULL) {
        return 0;
    }

    memcpy(new_value, old_value, old_len);
    memcpy(new_value + old_len, append_value, append_len + 1);

    jm_free(old_value);
    node->value = new_value;

    return 1;
}

int storage_incr(const char *key) {
    KVNode *node = find_node(key);

    if (node == NULL || node->type != TYPE_STRING) {
        return -1;
    }

    int value = atoi((char *)node->value);
    value++;

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%d", value);

    jm_free(node->value);
    node->value = jm_strdup(buffer);

    if (node->value == NULL) {
        return -1;
    }

    return value;
}

int storage_decr(const char *key) {
    KVNode *node = find_node(key);

    if (node == NULL || node->type != TYPE_STRING) {
        return -1;
    }

    int value = atoi((char *)node->value);
    value--;

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%d", value);

    jm_free(node->value);
    node->value = jm_strdup(buffer);

    if (node->value == NULL) {
        return -1;
    }

    return value;
}

/* =========================
   List Commands
   ========================= */

int storage_lpush(const char *key, const char *value) {
    unsigned int index = hash_function(key);
    KVNode *node = find_node(key);

    ListNode *new_list_node = (ListNode *)jm_malloc(sizeof(ListNode));

    if (new_list_node == NULL) {
        return 0;
    }

    new_list_node->value = jm_strdup(value);

    if (new_list_node->value == NULL) {
        jm_free(new_list_node);
        return 0;
    }

    if (node != NULL) {
        if (node->type != TYPE_LIST) {
            jm_free(new_list_node->value);
            jm_free(new_list_node);
            return 0;
        }

        // 插到 list 頭部
        new_list_node->next = (ListNode *)node->value;
        node->value = new_list_node;

        return 1;
    }

    KVNode *new_kv_node = (KVNode *)jm_malloc(sizeof(KVNode));

    if (new_kv_node == NULL) {
        jm_free(new_list_node->value);
        jm_free(new_list_node);
        return 0;
    }

    new_list_node->next = NULL;

    new_kv_node->key = jm_strdup(key);
    new_kv_node->type = TYPE_LIST;
    new_kv_node->value = new_list_node;

    if (new_kv_node->key == NULL) {
        jm_free(new_list_node->value);
        jm_free(new_list_node);
        jm_free(new_kv_node);
        return 0;
    }

    new_kv_node->next = hash_table[index];
    hash_table[index] = new_kv_node;

    return 1;
}

int storage_rpush(const char *key, const char *value) {
    unsigned int index = hash_function(key);
    KVNode *node = find_node(key);

    ListNode *new_list_node = (ListNode *)jm_malloc(sizeof(ListNode));

    if (new_list_node == NULL) {
        return 0;
    }

    new_list_node->value = jm_strdup(value);
    new_list_node->next = NULL;

    if (new_list_node->value == NULL) {
        jm_free(new_list_node);
        return 0;
    }

    if (node != NULL) {
        if (node->type != TYPE_LIST) {
            jm_free(new_list_node->value);
            jm_free(new_list_node);
            return 0;
        }

        ListNode *current = (ListNode *)node->value;

        if (current == NULL) {
            node->value = new_list_node;
            return 1;
        }

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new_list_node;
        return 1;
    }

    KVNode *new_kv_node = (KVNode *)jm_malloc(sizeof(KVNode));

    if (new_kv_node == NULL) {
        jm_free(new_list_node->value);
        jm_free(new_list_node);
        return 0;
    }

    new_kv_node->key = jm_strdup(key);
    new_kv_node->type = TYPE_LIST;
    new_kv_node->value = new_list_node;

    if (new_kv_node->key == NULL) {
        jm_free(new_list_node->value);
        jm_free(new_list_node);
        jm_free(new_kv_node);
        return 0;
    }

    new_kv_node->next = hash_table[index];
    hash_table[index] = new_kv_node;

    return 1;
}

char *storage_lpop(const char *key) {
    KVNode *node = find_node(key);

    if (node == NULL || node->type != TYPE_LIST) {
        return NULL;
    }

    ListNode *head = (ListNode *)node->value;

    if (head == NULL) {
        return NULL;
    }

    node->value = head->next;

    char *result = jm_strdup(head->value);

    jm_free(head->value);
    jm_free(head);

    return result;
}

char *storage_rpop(const char *key) {
    KVNode *node = find_node(key);

    if (node == NULL || node->type != TYPE_LIST) {
        return NULL;
    }

    ListNode *current = (ListNode *)node->value;
    ListNode *prev = NULL;

    if (current == NULL) {
        return NULL;
    }

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    char *result = jm_strdup(current->value);

    if (prev == NULL) {
        node->value = NULL;
    } else {
        prev->next = NULL;
    }

    jm_free(current->value);
    jm_free(current);

    return result;
}

void storage_lrange(const char *key, char *response, int response_size) {
    KVNode *node = find_node(key);

    if (node == NULL || node->type != TYPE_LIST) {
        snprintf(response, response_size, "(nil)\r\n");
        return;
    }

    ListNode *current = (ListNode *)node->value;
    int offset = 0;

    while (current != NULL) {
        offset += snprintf(
            response + offset,
            response_size - offset,
            "%s ",
            current->value
        );

        if (offset >= response_size - 4) {
            break;
        }

        current = current->next;
    }

    snprintf(response + offset, response_size - offset, "\r\n");
}

/* =========================
   Common Commands
   ========================= */

int storage_exists(const char *key) {
    return find_node(key) != NULL;
}

int storage_del(const char *key) {
    unsigned int index = hash_function(key);
    KVNode *current = hash_table[index];
    KVNode *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hash_table[index] = current->next;
            } else {
                prev->next = current->next;
            }

            jm_free(current->key);

            if (current->type == TYPE_STRING) {
                jm_free(current->value);
            } else if (current->type == TYPE_LIST) {
                free_list((ListNode *)current->value);
            }

            jm_free(current);

            return 1;
        }

        prev = current;
        current = current->next;
    }

    return 0;
}

void storage_flushall(void) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        KVNode *current = hash_table[i];

        while (current != NULL) {
            KVNode *next = current->next;

            jm_free(current->key);

            if (current->type == TYPE_STRING) {
                jm_free(current->value);
            } else if (current->type == TYPE_LIST) {
                free_list((ListNode *)current->value);
            }

            jm_free(current);

            current = next;
        }

        hash_table[i] = NULL;
    }
}

void storage_keys(char *response, int response_size) {
    int offset = 0;
    int count = 0;

    offset += snprintf(response + offset, response_size - offset, "KEYS:");

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        KVNode *current = hash_table[i];

        while (current != NULL) {
            offset += snprintf(
                response + offset,
                response_size - offset,
                " %s",
                current->key
            );

            count++;
            current = current->next;

            if (offset >= response_size - 4) {
                break;
            }
        }
    }

    if (count == 0) {
        snprintf(response, response_size, "(empty)\r\n");
    } else {
        snprintf(response + offset, response_size - offset, "\r\n");
    }
}

void storage_debug_print(void) {
    printf("----- HASH TABLE DEBUG -----\n");

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        KVNode *current = hash_table[i];

        if (current != NULL) {
            printf("Bucket[%d]: ", i);

            while (current != NULL) {
                if (current->type == TYPE_STRING) {
                    printf("(%s => STRING:%s) -> ",
                           current->key,
                           (char *)current->value);
                } else if (current->type == TYPE_LIST) {
                    printf("(%s => LIST) -> ", current->key);
                }

                current = current->next;
            }

            printf("NULL\n");
        }
    }

    printf("----------------------------\n");
}
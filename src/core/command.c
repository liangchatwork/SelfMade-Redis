#include <stdio.h>
#include <string.h>

#include "command.h"
#include "storage.h"
#include "memory.h"

int handle_command(char *input, char *response, int response_size) {
    char *command;
    char *arg1;
    char *arg2;

    input[strcspn(input, "\r\n")] = 0;

    command = strtok(input, " ");

    if (command == NULL) {
        snprintf(response, response_size, "INVALID COMMAND\r\n");
        return 0;
    }

    if (strcmp(command, "PING") == 0) {
        snprintf(response, response_size, "PONG\r\n");
        return 0;
    }

    if (strcmp(command, "QUIT") == 0) {
        snprintf(response, response_size, "BYE\r\n");
        return 1;
    }

    if (strcmp(command, "SET") == 0) {
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");

        if (arg1 == NULL || arg2 == NULL) {
            snprintf(response, response_size, "USAGE: SET key value\r\n");
            return 0;
        }

        storage_set(arg1, arg2);
        snprintf(response, response_size, "OK\r\n");
        return 0;
    }

    if (strcmp(command, "GET") == 0) {
        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {
            snprintf(response, response_size, "USAGE: GET key\r\n");
            return 0;
        }

        const char *value = storage_get(arg1);

        if (value == NULL) {
            snprintf(response, response_size, "(nil)\r\n");
        } else {
            snprintf(response, response_size, "%s\r\n", value);
        }

        return 0;
    }

    if (strcmp(command, "DEL") == 0) {
        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {
            snprintf(response, response_size, "USAGE: DEL key\r\n");
            return 0;
        }

        int result = storage_del(arg1);

        if (result) {
            snprintf(response, response_size, "OK\r\n");
        } else {
            snprintf(response, response_size, "(nil)\r\n");
        }

        return 0;
    }

    if (strcmp(command, "EXISTS") == 0) {
        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {
            snprintf(response, response_size, "USAGE: EXISTS key\r\n");
            return 0;
        }

        int result = storage_exists(arg1);
        snprintf(response, response_size, "%d\r\n", result);

        return 0;
    }

    if (strcmp(command, "STRLEN") == 0) {
        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {
            snprintf(response, response_size, "USAGE: STRLEN key\r\n");
            return 0;
        }

        int len = storage_strlen(arg1);

        if (len < 0) {
            snprintf(response, response_size, "(nil)\r\n");
        } else {
            snprintf(response, response_size, "%d\r\n", len);
        }

        return 0;
    }

    if (strcmp(command, "APPEND") == 0) {

        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");

        if (arg1 == NULL || arg2 == NULL) {

            snprintf(response, response_size,
                    "USAGE: APPEND key value\r\n");

            return 0;
        }

        int result = storage_append(arg1, arg2);

        if (result) {

            snprintf(response, response_size, "OK\r\n");

        } else {

            snprintf(response, response_size, "(nil)\r\n");
        }

        return 0;
    }

    if (strcmp(command, "INCR") == 0) {

        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {

            snprintf(response, response_size,
                    "USAGE: INCR key\r\n");

            return 0;
        }

        int result = storage_incr(arg1);

        if (result < 0) {

            snprintf(response, response_size, "(nil)\r\n");

        } else {

            snprintf(response, response_size,
                    "%d\r\n",
                    result);
        }

        return 0;
    }

    if (strcmp(command, "DECR") == 0) {

        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {

            snprintf(response, response_size,
                    "USAGE: DECR key\r\n");

            return 0;
        }

        int result = storage_decr(arg1);

        if (result < 0) {

            snprintf(response, response_size, "(nil)\r\n");

        } else {

            snprintf(response, response_size,
                    "%d\r\n",
                    result);
        }

        return 0;
    }

    if (strcmp(command, "KEYS") == 0) {
        storage_keys(response, response_size);
        return 0;
    }

    if (strcmp(command, "FLUSHALL") == 0) {
        storage_flushall();
        snprintf(response, response_size, "OK\r\n");
        return 0;
    }

    if (strcmp(command, "LPUSH") == 0) {
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");

        if (arg1 == NULL || arg2 == NULL) {
            snprintf(response, response_size, "USAGE: LPUSH key value\r\n");
            return 0;
        }

        int result = storage_lpush(arg1, arg2);

        if (result) {
            snprintf(response, response_size, "OK\r\n");
        } else {
            snprintf(response, response_size, "WRONGTYPE or LPUSH failed\r\n");
        }

        return 0;
    }

    if (strcmp(command, "RPUSH") == 0) {
        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");

        if (arg1 == NULL || arg2 == NULL) {
            snprintf(response, response_size, "USAGE: RPUSH key value\r\n");
            return 0;
        }

        int result = storage_rpush(arg1, arg2);

        if (result) {
            snprintf(response, response_size, "OK\r\n");
        } else {
            snprintf(response, response_size, "WRONGTYPE or RPUSH failed\r\n");
        }

        return 0;
    }

    if (strcmp(command, "LPOP") == 0) {
        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {
            snprintf(response, response_size, "USAGE: LPOP key\r\n");
            return 0;
        }

        char *value = storage_lpop(arg1);

        if (value == NULL) {
            snprintf(response, response_size, "(nil)\r\n");
        } else {
            snprintf(response, response_size, "%s\r\n", value);
            jm_free(value);
        }

        return 0;
    }

    if (strcmp(command, "RPOP") == 0) {
        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {
            snprintf(response, response_size, "USAGE: RPOP key\r\n");
            return 0;
        }

        char *value = storage_rpop(arg1);

        if (value == NULL) {
            snprintf(response, response_size, "(nil)\r\n");
        } else {
            snprintf(response, response_size, "%s\r\n", value);
            jm_free(value);
        }

        return 0;
    }

    if (strcmp(command, "LRANGE") == 0) {

        arg1 = strtok(NULL, " ");

        if (arg1 == NULL) {

            snprintf(response,
                    response_size,
                    "USAGE: LRANGE key\r\n");

            return 0;
        }

        storage_lrange(arg1,
                    response,
                    response_size);

        return 0;
    }

    snprintf(response, response_size, "UNKNOWN COMMAND\r\n");
    return 0;
}
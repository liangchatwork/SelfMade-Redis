#include <stdio.h>
#include <string.h>

#include "command.h"
#include "storage.h"

int handle_command(char *input, char *response, int response_size) {
    char *command;
    char *arg1;
    char *arg2;

    // 移除換行符號，避免 PING\r\n 比對失敗
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

    snprintf(response, response_size, "UNKNOWN COMMAND\r\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#include "server.h"
#include "command.h"

#define BUFFER_SIZE 1024

int start_server(int port) {
    WSADATA wsa_data;
    SOCKET server_fd;
    SOCKET client_fd;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    int client_addr_len;
    char buffer[BUFFER_SIZE];

    // Windows socket 使用前必須初始化 Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // 建立 TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // 綁定 port，例如 6379
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // 開始監聽 client
    if (listen(server_fd, 10) == SOCKET_ERROR) {
        printf("listen failed: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Server is listening on port %d...\n", port);

    while (1) {
        client_addr_len = sizeof(client_addr);

        // accept() 會卡在這裡，直到有 client 連進來
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_fd == INVALID_SOCKET) {
            printf("accept failed: %d\n", WSAGetLastError());
            continue;
        }

        printf("Client connected.\n");

        while (1) {
            memset(buffer, 0, BUFFER_SIZE);

            // 接收 client 傳來的資料
            int bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);

            if (bytes_received == SOCKET_ERROR) {
                printf("recv failed: %d\n", WSAGetLastError());
                break;
            }

            if (bytes_received == 0) {
                printf("Client disconnected.\n");
                break;
            }

            buffer[bytes_received] = '\0';

            printf("Received from client: %s\n", buffer);

            char response[BUFFER_SIZE];

            int should_close = handle_command(buffer, response, BUFFER_SIZE);

            send(client_fd, response, strlen(response), 0);

            if (should_close) {
                break;
            }
        }

        closesocket(client_fd);
    }

    closesocket(server_fd);
    WSACleanup();

    return 0;
}
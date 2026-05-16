#include <windows.h>
#include <string.h>

#include "syscalls.h"

void jm_write(const char *message) {

    HANDLE stdout_handle;

    DWORD bytes_written;

    // 取得 stdout handle
    stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // 使用 Windows API 輸出文字
    WriteFile(
        stdout_handle,
        message,
        strlen(message),
        &bytes_written,
        NULL
    );
}
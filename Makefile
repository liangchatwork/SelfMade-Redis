CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = selfmade-redis.exe

SRC = src/main.c \
      src/network/server.c \
      src/storage/storage.c \
      src/core/command.c \
      src/utils/memory.c \
      src/sys/syscalls.c

LIBS = -lws2_32

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
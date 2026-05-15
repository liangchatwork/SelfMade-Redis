CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

TARGET = selfmade-redis.exe

SRC = src/main.c \
      src/network/server.c

LIBS = -lws2_32

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
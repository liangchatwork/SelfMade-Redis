# Selfmade Redis

## Introduction

Selfmade Redis is a systems-heavy Redis-inspired in-memory database server built from scratch in C, focused on low-level systems programming, networking, memory management, and database internals.

Rather than fully replicating Redis, the goal of this project is to gradually design and implement a lightweight Redis-like database while exploring how real database systems work internally.

The project combines:

* Systems Programming
* Data Structures
* Memory Management
* Networking
* Database Internals
* Event-driven Architecture

---

## Project Status

🚧 Currently under development.

### Implemented Features

#### Networking
* TCP socket server
* Winsock initialization
* Client connection handling
* Continuous command loop

#### String Commands
* `PING`
* `QUIT`
* `SET`
* `GET`
* `DEL`
* `EXISTS`
* `STRLEN`
* `APPEND`
* `INCR`
* `DECR`
* `KEYS`
* `FLUSHALL`

#### List Commands
* `LPUSH`
* `RPUSH`
* `LPOP`
* `RPOP`
* `LRANGE`

#### Systems & Memory
* Custom hash table
* Linked-list storage
* Collision handling
* Dynamic heap allocation
* `jm_malloc`
* `jm_free`
* `jm_strdup`
* Memory tracking
* Leak detection basics

---

## Tech Stack

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Winsock2](https://img.shields.io/badge/Winsock2-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![TCP/IP](https://img.shields.io/badge/TCP/IP-323330?style=for-the-badge)
![GCC](https://img.shields.io/badge/GCC-FF6C37?style=for-the-badge&logo=gnu&logoColor=white)
![Makefile](https://img.shields.io/badge/Makefile-064F8C?style=for-the-badge)

---

## Environments

* Windows 11
* MinGW64
* GCC
* Git Bash

---

## Repository Structure

```bash
selfmade-redis/
├── src/
│   ├── core/
│   ├── network/
│   ├── storage/
│   ├── protocol/
│   ├── persistence/
│   └── utils/
├── include/
├── tests/
├── docs/
├── examples/
└── Makefile
````

---

## Current Commands

### String Commands

```bash
PING
QUIT

SET key value
GET key
DEL key
EXISTS key

STRLEN key
APPEND key value

INCR key
DECR key

KEYS
FLUSHALL
```

### List Commands

```bash
LPUSH key value
RPUSH key value

LPOP key
RPOP key

LRANGE key
```

---

## Example Usage

### String Example

```bash
SET name Jerry
GET name
APPEND name Chen
GET name
```

Expected Output:

```bash
OK
Jerry
OK
JerryChen
```

---

### List Example

```bash
LPUSH nums 1
LPUSH nums 2
RPUSH nums 3

LRANGE nums
```

Expected Output:

```bash
2 1 3
```

---

## Build & Run

### Compile

```bash
make
```

### Run

```bash
./selfmade-redis.exe
```

### Connect to Server

Using `ncat`:

```bash
ncat 127.0.0.1 6379
```

---

## Internal Architecture

The project is separated into modular layers to simulate a real database architecture.

### `server.c`

Responsible for:

* TCP socket setup
* Client connections
* Sending and receiving data
* Network loop

---

### `command.c`

Responsible for:

* Command parsing
* Command dispatching
* Request handling
* Response generation

Example:

```c
if (strcmp(command, "PING") == 0) {
    snprintf(response, response_size, "PONG\r\n");
}
```

---

### `storage.c`

Responsible for:

* In-memory storage
* Hash table management
* Linked-list operations
* Key lookup
* Dynamic memory handling

Example:

```c
typedef struct KVNode {

    char *key;

    ValueType type;

    void *value;

    struct KVNode *next;

} KVNode;
```

---

### `memory.c`

Responsible for:

* Custom memory tracking
* Heap allocation monitoring
* Allocation metadata
* Leak detection basics

Example:

```c
typedef struct MemoryHeader {
    size_t size;
} MemoryHeader;
```

---

## Data Structure Design

### Hash Table

The database internally uses a custom hash table:

```txt
key
 ↓
hash_function()
 ↓
bucket index
 ↓
linked list traversal
```

Collision handling currently uses:

* Separate Chaining
* Linked List Buckets

---

### Redis-like Object System

Each key stores a type-aware object:

```c
typedef enum {
    TYPE_STRING,
    TYPE_LIST
} ValueType;
```

This allows future expansion toward:

* Sets
* Hashes
* Sorted Sets

---

## Roadmap

### Phase 1 — TCP Server ✅

* [x] TCP socket server
* [x] Client connection
* [x] `PING`
* [x] `QUIT`
* [x] Continuous command loop

---

### Phase 2 — Key-Value Database ✅

* [x] `SET`
* [x] `GET`
* [x] `DEL`
* [x] `EXISTS`
* [x] Command parser layer
* [x] Storage layer

---

### Phase 3 — Dynamic Memory & Data Structures 🚧

* [x] Linked-list storage
* [x] Pointer-based storage
* [x] Custom hash table
* [x] Collision handling
* [x] Redis-like object system
* [x] `TYPE_STRING`
* [x] `TYPE_LIST`
* [x] List commands
* [ ] Rehashing
* [ ] Dynamic resize
* [ ] Doubly linked list

---

### Phase 4 — Systems Memory Layer 🚧

* [x] `jm_malloc`
* [x] `jm_free`
* [x] `jm_strdup`
* [x] Allocation metadata
* [x] Memory tracking
* [x] Leak detection basics
* [ ] `jm_realloc`
* [ ] Memory pool allocator

---

### Phase 5 — Event-driven Server

* [ ] `select()`
* [ ] Multiple clients
* [ ] Event loop
* [ ] Non-blocking architecture

---

### Phase 6 — Persistence System

* [ ] Binary snapshot format
* [ ] Save / Load
* [ ] Serialization

---

### Phase 7 — RESP Protocol

* [ ] RESP parser
* [ ] Byte stream parsing
* [ ] Protocol validation

---

### Phase 8 — OS / Syscall Layer 🚧

* [x] Basic OS abstraction layer
* [ ] Syscall experimentation
* [ ] Platform-specific wrappers
* [ ] `VirtualAlloc`
* [ ] `mmap`
* [ ] `epoll`

---

## Disclaimer

This project is intended for educational and learning purposes.

The project intentionally focuses on systems programming concepts, database internals, memory management, and low-level architecture rather than production-ready Redis compatibility.




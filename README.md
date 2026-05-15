# Selfmade Redis

## Introduction

Selfmade Redis is a systems-heavy Redis-inspired in-memory database server built from scratch in C, focused on low-level systems programming, networking, memory management, and database internals.

This project explores core computer science and backend system concepts including:

* TCP socket programming
* Client-server architecture
* Command parsing
* Dynamic memory management
* Data structures
* Event-driven systems
* Persistence mechanisms
* OS interaction and low-level programming

Rather than fully replicating Redis, the goal of this project is to gradually design and implement a lightweight Redis-like database while gaining hands-on experience with systems-level development, memory allocation, networking internals, and database architecture.

---

## Project Goals

This project is designed to go beyond a simple socket programming demo.

The long-term objective is to build a Redis-inspired system that combines:

* Systems Programming
* Data Structures
* Memory Management
* Networking
* Database Internals
* Event-driven Architecture

The project will gradually evolve from a basic TCP server into a more advanced educational systems project featuring:

* Custom hash table implementation
* Dynamic memory allocation
* Event loop architecture
* Binary persistence
* RESP protocol parsing
* Custom memory allocator
* OS abstraction layer
* Syscall-level experimentation

---

## Project Status

🚧 Currently under development.

### Implemented Features

* TCP socket server
* Winsock initialization
* Client connection handling
* Continuous command loop
* Basic command parsing
* `PING -> PONG`
* `QUIT`
* `SET`
* `GET`
* `DEL`
* `EXISTS`
* In-memory key-value storage
* Modular project architecture

### Planned Features

* Custom linked-list storage nodes
* Dynamic heap allocation
* Custom hash table
* Collision handling
* TTL expiration
* Event loop (`select`)
* Multiple client support
* Binary persistence system
* RESP protocol parser
* Memory usage statistics
* Custom allocator (`jm_malloc`)
* OS abstraction layer
* Syscall-level modules

---

## Tech Stack

### Language

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge\&logo=c\&logoColor=white)

---

### Networking & Systems

![Winsock2](https://img.shields.io/badge/Winsock2-0078D6?style=for-the-badge\&logo=windows\&logoColor=white)
![TCP/IP](https://img.shields.io/badge/TCP/IP-323330?style=for-the-badge)
![Socket Programming](https://img.shields.io/badge/Socket_Programming-1E1E1E?style=for-the-badge)
![Systems Programming](https://img.shields.io/badge/Systems_Programming-222222?style=for-the-badge)

---

### Data Structures

![Hash Table](https://img.shields.io/badge/Hash_Table-00599C?style=for-the-badge)
![Linked List](https://img.shields.io/badge/Linked_List-444444?style=for-the-badge)
![Memory Management](https://img.shields.io/badge/Memory_Management-8A2BE2?style=for-the-badge)

---

### Development Tools

![GCC](https://img.shields.io/badge/GCC-FF6C37?style=for-the-badge\&logo=gnu\&logoColor=white)
![MinGW](https://img.shields.io/badge/MinGW-000000?style=for-the-badge)
![Makefile](https://img.shields.io/badge/Makefile-064F8C?style=for-the-badge)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge\&logo=git\&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge\&logo=github\&logoColor=white)

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
```

---

## Current Commands

```bash
PING
QUIT
SET key value
GET key
DEL key
EXISTS key
```

Example:

```bash
SET name Jerry
GET name
EXISTS name
DEL name
```

Expected Output:

```bash
OK
Jerry
1
OK
```

---

## Usage

### Compile

```bash
make
```

### Run

```bash
./selfmade-redis.exe
```

### Connect to Server

Example using `ncat`:

```bash
ncat 127.0.0.1 6379
```

---

## Current Architecture

The project is currently separated into modular layers:

### `server.c`

Responsible for:

* TCP server setup
* Socket handling
* Client connections
* Receiving and sending data

### `command.c`

Responsible for:

* Command parsing
* Command dispatching
* Response generation

### `storage.c`

Responsible for:

* In-memory key-value storage
* Data lookup
* Data insertion and deletion

This architecture is intentionally designed to support future expansion toward more advanced systems-level components.

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
* [x] In-memory storage
* [x] Command parser layer
* [x] Storage layer

---

### Phase 3 — Dynamic Memory & Data Structures

* [ ] Linked list nodes
* [ ] Dynamic heap allocation
* [ ] Pointer-based storage
* [ ] Custom hash table
* [ ] Collision handling
* [ ] Rehashing

---

### Phase 4 — Systems Memory Layer

* [ ] `jm_malloc`
* [ ] `jm_free`
* [ ] Memory tracking
* [ ] Memory statistics
* [ ] Leak detection

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

### Phase 8 — OS / Syscall Layer

* [ ] OS abstraction layer
* [ ] Syscall experimentation
* [ ] Platform-specific wrappers

---

## Disclaimer

This project is intended for educational and learning purposes.

The project intentionally focuses on systems programming concepts, internal database mechanisms, and low-level software architecture rather than production-ready performance or full Redis compatibility.

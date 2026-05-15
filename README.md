# Selfmade Redis

## Introduction

Selfmade Redis is a Redis-inspired in-memory database server built from scratch in C, focused on low-level systems programming, networking, and database internals.

This project explores core computer science and backend system concepts including:

* TCP socket programming
* Client-server architecture
* Command parsing
* Memory management
* Data structures
* Event loops
* Persistence systems

Rather than fully replicating Redis, the goal of this project is to gradually design and implement a lightweight Redis-like database while gaining hands-on experience with systems-level development and internal database mechanisms.


---

## Project Status

🚧 Currently under development.

Implemented features:

* TCP socket server
* Client connection handling
* Basic command parsing
* `PING -> PONG`
* `QUIT`
* Continuous command loop

Planned features:

* `SET / GET / DEL`
* In-memory key-value storage
* Custom hash table
* TTL expiration
* Multi-client support
* Event loop (`select`)
* Persistence system
* RESP protocol parser

---

## Tech Stack

### Language

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge\&logo=c\&logoColor=white)

---

### Networking & Systems

![Winsock2](https://img.shields.io/badge/Winsock2-0078D6?style=for-the-badge\&logo=windows\&logoColor=white)
![TCP/IP](https://img.shields.io/badge/TCP/IP-323330?style=for-the-badge)
![Socket Programming](https://img.shields.io/badge/Socket_Programming-1E1E1E?style=for-the-badge)

---

### Development Tools

![GCC](https://img.shields.io/badge/GCC-FF6C37?style=for-the-badge\&logo=gnu\&logoColor=white)
![MinGW](https://img.shields.io/badge/MinGW-000000?style=for-the-badge)
![Makefile](https://img.shields.io/badge/Makefile-064F8C?style=for-the-badge)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge\&logo=git\&logoColor=white)


---

## Repository Structure

```bash
selfmade-redis/
├── src/
├── include/
├── tests/
├── docs/
├── examples/
└── Makefile
```

---

## Commands

```bash
PING
QUIT
```

Example:

```bash
PING
PONG
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

## Roadmap

### Phase 1

* [x] TCP Server
* [x] Client Connection
* [x] `PING`
* [x] `QUIT`

### Phase 2

* [ ] `SET`
* [ ] `GET`
* [ ] `DEL`
* [ ] Key-Value Storage

### Phase 3

* [ ] Hash Table
* [ ] Collision Handling
* [ ] Dynamic Memory Allocation

### Phase 4

* [ ] TTL Expiration
* [ ] Background Cleanup

### Phase 5

* [ ] Event Loop (`select`)
* [ ] Multiple Clients

### Phase 6

* [ ] Persistence System

### Phase 7

* [ ] RESP Protocol Support

---

## Disclaimer

This project is intended for educational and learning purposes.

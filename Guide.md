Guide will cover:

* 🔧 **Every command & function** used in the project (`gcc`, `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `read()`, `send()`, etc.)
* 📚 **Concept explanations** (like what `AF_INET`, `htons`, `pthread_mutex`, etc. mean)
* 🎯 **Full scope and purpose of the project** (why it was built, what learners gain).


# Networking in C — Concepts & Glossary

This guide explains **all the commands, functions, and concepts** used in this project, so new learners can fully understand the code.

---

## ⚙️ Compilation & Commands

### `gcc`
The GNU Compiler Collection. Used to compile C programs.

Example:
```bash
gcc server.c -o server
./server
````

* `gcc` → the compiler
* `server.c` → input source file
* `-o server` → output executable file named `server`

### `./server`

Runs the compiled binary in the current directory (`./` means “this folder”).

---

## 🌐 Networking Functions (Sockets API)

### `socket()`

Creates an endpoint for communication.

```c
int sock = socket(AF_INET, SOCK_STREAM, 0);
```

* `AF_INET` → Address family (IPv4)
* `SOCK_STREAM` → TCP (reliable, connection-based)
* `0` → Protocol (default TCP for stream sockets)

Returns a **file descriptor** (like a handle) for the socket.

---

### `bind()`

Assigns (binds) a socket to an IP address and port.

```c
bind(sock, (struct sockaddr *)&address, sizeof(address));
```

* Connects the socket to `address.sin_addr` (IP) and `address.sin_port` (Port).
* Without bind, the OS wouldn’t know which port the server is listening on.

---

### `listen()`

Marks the socket as **passive** (ready to accept connections).

```c
listen(sock, backlog);
```

* `backlog` = max number of pending connections in the queue.
* Example: `listen(server_fd, 3)` → allow 3 clients to wait in line.

---

### `accept()`

Accepts a new client connection from the queue.

```c
int new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
```

* Creates a **new socket** just for that client.
* The original `server_fd` keeps listening for more clients.

---

### `connect()`

Used on the client side to connect to a server.

```c
connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
```

* Requires server IP and port.
* If successful, the client and server can now exchange data.

---

### `read()`

Reads data from a socket into a buffer.

```c
read(sock, buffer, sizeof(buffer));
```

* Blocks until data arrives.
* Returns number of bytes read (0 means disconnect).

---

### `send()`

Sends data to a socket.

```c
send(sock, message, strlen(message), 0);
```

* Fourth argument is usually `0` (flags).
* Returns number of bytes sent.

---

### `close()`

Closes a socket (frees the resource).

```c
close(sock);
```

* Always close sockets when finished to avoid resource leaks.

---

## 📚 Networking Data Structures & Helpers

### `struct sockaddr_in`

Represents an IPv4 address.

```c
struct sockaddr_in address;
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
```

* `sin_family` → Address family (always `AF_INET` for IPv4).
* `sin_addr.s_addr` → IP (here `INADDR_ANY` = bind to all interfaces).
* `sin_port` → Port (must use `htons()`).

---

### `AF_INET`

Specifies **IPv4** (Internet Protocol v4).
For IPv6, you’d use `AF_INET6`.

---

### `htons()`

“Host TO Network Short.” Converts port numbers to **network byte order** (big-endian).
Different machines store numbers differently; networking requires consistency.

---

### `inet_pton()`

Converts an IP string (like `"127.0.0.1"`) to binary form for `sockaddr_in`.

```c
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
```

---

## 🧵 Threads & Concurrency

### `pthread_create()`

Creates a new thread.

```c
pthread_create(&thread_id, NULL, handle_client, (void *)new_sock);
```

* `thread_id` → ID of the new thread
* `handle_client` → function the thread will run
* `new_sock` → argument passed to the thread

---

### `pthread_detach()`

Marks a thread as **detached** (auto-cleans when finished).
Without this, threads become “zombies” and leak resources.

---

### `pthread_mutex_t`

A **mutex** (mutual exclusion) lock for protecting shared data.

```c
pthread_mutex_lock(&clients_mutex);
// modify clients[]
pthread_mutex_unlock(&clients_mutex);
```

* Prevents **race conditions** when multiple threads update the same resource.

---

## 🎯 Scope & Purpose of This Project

This project was built as a **teaching repo** for learning networking in C step by step.

1. **Step 1 — Hello World**

   * Learn `gcc` compilation basics.

2. **Step 2 — TCP Server & Client**

   * Learn socket basics: `socket()`, `bind()`, `listen()`, `accept()`, `connect()`.

3. **Step 3 — Persistent Chat**

   * Continuous message exchange with loops.

4. **Step 4 — Threaded Server**

   * Support multiple clients using threads.

5. **Step 5 — Group Chat Server**

   * Broadcast messages to multiple clients.
   * Introduce mutexes and concurrency management.

---

## 📖 Learning Goals

By the end of this repo, a learner will:

* Understand **how TCP networking works at a low level**.
* Be able to **write their own client/server apps in C**.
* Gain experience with **threads, mutexes, and concurrency**.
* Develop **debugging and troubleshooting skills** in networking code.
* Have a solid foundation for **advanced networking topics** (UDP, file transfer, encryption, etc.).

---

💡 This guide can be used as a **reference manual** while working through the project, so learners not only run the code but **understand every piece of it**.

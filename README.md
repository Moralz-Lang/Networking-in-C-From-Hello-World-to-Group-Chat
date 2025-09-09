# Networking in C — From Hello World to Group Chat

This repository is a **step-by-step learning journey** in C programming with networking.  
It begins with a simple “Hello World” and gradually builds up to a **multi-client group chat server**.

Each step includes:
- ✅ Source code
- ✅ Compile & run instructions
- ✅ Troubleshooting notes
- ✅ Checkpoint Q&A for reflection

---

## 📂 Steps
1. [Hello World](./step1_hello_world)  
2. [Simple TCP Server & Client](./step2_simple_server_client)  
3. [Persistent Chat (one client)](./step3_persistent_chat)  
4. [Threaded Multi-Client Server](./step4_threaded_server)  
5. [Group Chat Server](./step5_group_chat)  

---

## ⚙️ Compilation

### Using Makefile
From the repo root:
```bash
make step1
make step2
make step3
make step4
make step5
Or compile manually:

bash
Copy code
gcc filename.c -o output_binary
./output_binary
🚀 Final Outcome
By completing this repo, you will:

Understand C compilation with gcc

Learn how TCP sockets work (socket, bind, listen, accept, connect)

Handle message sending/receiving

Use threads and mutexes for concurrency

Build a multi-client group chat system

🎯 Outcome for Learners

This repo now serves as:

A guided course for C networking

With working code at each milestone

Reflective checkpoint questions + answers

Troubleshooting notes (realistic issues a beginner will hit)

Easy compilation with Makefile

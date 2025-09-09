# Step 5: Group Chat Server

We built a **multi-client group chat system**. Each message is broadcast to all other connected clients.

---

## 🔨 What We Built
- **Server**: Accepts multiple clients, tracks them in an array, and broadcasts messages.
- **Client**: Reused from Step 3.

---

## ⚙️ How to Compile & Run
Terminal 1 (Server):
```bash
gcc group_chat_server.c -o group_chat_server -lpthread
./group_chat_server
Terminal 2+ (Clients):

bash
Copy code
gcc chat_client.c -o chat_client
./chat_client

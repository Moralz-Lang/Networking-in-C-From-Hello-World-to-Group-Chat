🚧 Troubleshooting

Issue: Server crashes when many clients connect/disconnect
✅ Fix: Protect clients[] with pthread_mutex_t.

Issue: Messages go to dead sockets
✅ Fix: Remove client from clients[] on disconnect.

Issue: “Zombie” threads
✅ Fix: Always pthread_detach() created threads.

❓ Checkpoint Questions

Q1: Why do we need a mutex (pthread_mutex_t)?
A1: To prevent race conditions when multiple threads modify clients[].

Q2: Why do we remove disconnected clients from the list?
A2: Otherwise the server keeps sending to invalid sockets → errors.

Q3: What would happen if we didn’t pthread_detach(thread_id)?
A3: Threads would remain in memory after finishing, causing resource leaks.

Q4: What if we forget both pthread_detach and pthread_join?
A4: Finished threads pile up as zombies until system resources run out and the server crashes.

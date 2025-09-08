#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Function for handling a client
void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg); // free the allocated memory for client socket
    char buffer[BUFFER_SIZE];

    printf("New client connected!\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        // Read message
        int valread = read(client_socket, buffer, BUFFER_SIZE);
        if (valread <= 0) {
            printf("Client disconnected.\n");
            break;
        }
        printf("Client: %s", buffer);

        // Check exit
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client ended chat.\n");
            break;
        }

        // Respond
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(client_socket, buffer, strlen(buffer), 0);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Server ended chat.\n");
            break;
        }
    }

    close(client_socket);
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // 1. Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 3. Listen
    if (listen(server_fd, 10) < 0) { // bigger backlog
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Threaded chat server listening on port %d...\n", PORT);

    while (1) {
        int *new_socket = malloc(sizeof(int));
        if ((*new_socket = accept(server_fd, (struct sockaddr *)&address,
                                  (socklen_t *)&addrlen)) < 0) {
            perror("accept failed");
            free(new_socket);
            continue;
        }

        // 4. Spawn a thread
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, new_socket) != 0) {
            perror("pthread_create failed");
            free(new_socket);
            continue;
        }

        pthread_detach(thread_id); // auto cleanup when thread ends
    }

    close(server_fd);
    return 0;
}

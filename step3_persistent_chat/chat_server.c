
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

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
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Chat server listening on port %d...\n", PORT);

    while (1) { // Server keeps running
        // 4. Accept client
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address,
                                    (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }
        printf("Client connected!\n");

        while (1) {
            memset(buffer, 0, BUFFER_SIZE);

            // 5. Read message from client
            int valread = read(client_socket, buffer, BUFFER_SIZE);
            if (valread <= 0) { // client disconnected
                printf("Client disconnected.\n");
                break;
            }
            printf("Client: %s", buffer);

            // Check if client wants to exit
            if (strncmp(buffer, "exit", 4) == 0) {
                printf("Client ended the chat.\n");
                break;
            }

            // 6. Send response
            printf("Server: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            send(client_socket, buffer, strlen(buffer), 0);

            // Check if server wants to exit
            if (strncmp(buffer, "exit", 4) == 0) {
                printf("Server ended the chat.\n");
                break;
            }
        }
        close(client_socket);
    }

    close(server_fd);
    return 0;
}

#include "blockchain.h"
#include <arpa/inet.h>
#include <unistd.h>

// Function to start a server
void start_blockchain_server(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Blockchain server listening on port %d...\n", port);

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = {0};
    read(new_socket, buffer, 1024);
    printf("Received blockchain data:\n%s\n", buffer);

    close(new_socket);
    close(server_fd);
}

// Function to send blockchain data to a peer
void send_blockchain_to_peer(const Blockchain *blockchain, const char *hostname, int port) {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, hostname, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return;
    }

    char buffer[4096] = {0};
    Block *current = blockchain->head;

    while (current != NULL) {
        char block_data[512];
        snprintf(block_data, sizeof(block_data), "%d|%s|%s|%s|%s|%u\n", current->index, current->previous_hash,
                 current->timestamp, current->data, current->hash, current->nonce);
        strcat(buffer, block_data);
        current = current->next;
    }

    send(sock, buffer, strlen(buffer), 0);
    printf("Blockchain data sent to %s:%d\n", hostname, port);

    close(sock);
}


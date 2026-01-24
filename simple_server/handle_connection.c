#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "handle_connection.h"
#include "hacking.h"

void handle_connection(int sockfd, struct sockaddr_in* client_addr) {
    printf("Server: Got connection\n from %s port %d\n", inet_ntoa(client_addr->sin_addr), client_addr->sin_port);
    char* request;
    int length = recv_line(sockfd, request);
    printf("Received request: %s", request);
}
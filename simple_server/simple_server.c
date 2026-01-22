#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "hacking.h"

#define PORT 80

int main(void) {
    printf("process start\n");
    printf("------------------------------------------");
    int sockfd, new_sockfd;
    struct sockaddr_in host_addr, client_addr;
    socklen_t sin_size;
    int recv_length=1, yes=1;
    char buffer[1024];
    // Prepare the sockaddr_in structure
    host_addr.sin_family = AF_INET;         // Use IPv4
    host_addr.sin_port = htons(PORT);       // Port 7890 (converted to Network Byte Order)
    host_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all available network interfaces
    memset(&(host_addr.sin_zero), '\0', 8); // Zero the rest of the struct
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        fatal("in socket");
    printf("in socket\n");

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        fatal("setting socket option SO_REUSEADDR");
    printf("setting socket option SO_REUSEADDR\n");
    
    if((bind(sockfd, (struct sockaddr*)&host_addr, sizeof(host_addr))) == -1)
        fatal("in bind");
    printf("in bind\n");

    if((listen(sockfd, 1024) == -1))
        fatal("in listen");

    printf("in listen\n");
    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        if((new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &sin_size)) == -1)
            fatal("in accept");
        printf("Server: Got connection\n");// from %s port %d\n", client_addr.sin_addr, client_addr.sin_port);
        send(new_sockfd, "Hello, world!\n", 13, 0);
    }
}

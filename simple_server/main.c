#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "hacking.h"
#include "handle_connection.h"

#define PORT 80

int main(void) {
    printf("process start\n");
    printf("------------------------------------------\n");
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

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        fatal("setting socket option SO_REUSEADDR");
    
    if((bind(sockfd, (struct sockaddr*)&host_addr, sizeof(host_addr))) == -1)
        fatal("in bind");

    if((listen(sockfd, 1024) == -1))
        fatal("in listen");

    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        if((new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &sin_size)) == -1)
            fatal("in accept");
        handle_connection(new_sockfd, &client_addr);
        close(new_sockfd);  // Close the connection after handling
    }
}

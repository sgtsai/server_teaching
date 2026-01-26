#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "handle_connection.h"
#include "hacking.h"

void handle_connection(int sockfd, struct sockaddr_in* client_addr) {
    printf("Server: Got connection\n from %s port %d\n", inet_ntoa(client_addr->sin_addr), client_addr->sin_port);
    char request[1024], buffer[1024];
    int length = recv_line(sockfd, request);
    char* ptr = strstr(request, " HTTP/");
    if(ptr == NULL) {
        fatal("Invalid HTTP request");
    }
    if(strncmp(request, "GET ", 4) == 0) {
        ptr = request + 4;
    }
    else if(strncmp(request, "HEAD ", 5) == 0) {
        ptr = request + 5;
    }
    else {
        fatal("Unsupported HTTP method, only GET and HEAD are supported");
    }
    //find first space after the file name
    char* space_ptr = strchr(ptr, ' ');
    if(space_ptr != NULL) {
        *space_ptr = '\0';
    }
    FILE *file;
    //if no file name specified, use index.html
    if(strcmp(ptr, "/") == 0) {
        file = fopen("index.html", "rb");
    }
    else {
        ptr = ptr + 1; //skip the leading '/'
        file = fopen(ptr, "rb");
    }

    if(file == NULL) {
        char* msg = "No file found\r\n";
        send(sockfd, msg, strlen(msg), 0);
    }
    else {
        int bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            if (send(sockfd, buffer, bytes_read, 0) == -1) {
                fatal("Error sending file");
                break;
            }
        }
    }
    printf("handle_connection finished\n");
}
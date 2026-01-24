#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "hacking.h"

void fatal(char* err_msg) {
    printf("fatal error: %s", err_msg);
    exit(-1);
}

int recv_line(int sockfd, char* dest_buffer) {
    int eol_match = 0;
    char* ptr = dest_buffer;
    while(recv(sockfd, ptr, 1, 0) == 1) {
        if(*ptr = EOL[eol_match]) {
            eol_match++;
            if(eol_match == 4) return strlen(dest_buffer);
        }
        ptr++;
    }
    fatal("recv_line");
}
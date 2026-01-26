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
    printf("in recv_line\n");
    int eol_match = 0;
    char* ptr = dest_buffer;
    //int loop_enter_count = 0;  for debug
    while(recv(sockfd, ptr, 1, 0) == 1) {
        /*loop_enter_count++;
        printf("loop_enter_count: %d\n", loop_enter_count);
        if(loop_enter_count > 10) {
            printf("infinite loop!!!\n");
            break;
        }*/
        printf("recv char: %c\n", *ptr);
        if((*ptr) == EOL[eol_match]) {
            eol_match++;
            if(eol_match == 2) {
                ptr--;
                *ptr = '\0';
                printf("dest_buffer in recv_line: %s\n", dest_buffer);
                return strlen(dest_buffer);
            }
        }
        ptr++;
    }
    fatal("recv_line");
}
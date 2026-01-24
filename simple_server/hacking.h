#ifndef HACKING
#define HACKING

#define EOL "\r\n"
void fatal(char* err_msg);

int recv_line(int sockfd, char* dest_buffer);
#endif
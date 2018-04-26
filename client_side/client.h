#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#define SOCK_IN_USE

#define BUF_SIZE 2048

#define UNUSED(x) (void)(x)

void error(const char * msg);

int sock_write(int sockfd, char * string);

int sock_read(int sockfd, char * type, char * value);

